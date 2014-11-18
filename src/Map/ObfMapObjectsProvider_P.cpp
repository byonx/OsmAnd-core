#include "ObfMapObjectsProvider_P.h"
#include "ObfMapObjectsProvider.h"

//#define OSMAND_PERFORMANCE_METRICS 2
#if !defined(OSMAND_PERFORMANCE_METRICS)
#   define OSMAND_PERFORMANCE_METRICS 0
#endif // !defined(OSMAND_PERFORMANCE_METRICS)

#include "ObfsCollection.h"
#include "ObfDataInterface.h"
#include "ObfMapSectionInfo.h"
#include "ObfMapSectionReader_Metrics.h"
#include "BinaryMapObject.h"
#include "ObfRoutingSectionInfo.h"
#include "ObfRoutingSectionReader_Metrics.h"
#include "Road.h"
#include "Stopwatch.h"
#include "Utilities.h"
#include "Logging.h"

OsmAnd::ObfMapObjectsProvider_P::ObfMapObjectsProvider_P(ObfMapObjectsProvider* owner_)
    : _binaryMapObjectsDataBlocksCache(new BinaryMapObjectsDataBlocksCache(false))
    , _roadsDataBlocksCache(new RoadsDataBlocksCache(false))
    , _link(new Link(this))
    , owner(owner_)
{
}

OsmAnd::ObfMapObjectsProvider_P::~ObfMapObjectsProvider_P()
{
    _link->release();
}

bool OsmAnd::ObfMapObjectsProvider_P::obtainData(
    const TileId tileId,
    const ZoomLevel zoom,
    std::shared_ptr<ObfMapObjectsProvider::Data>& outTiledData,
    ObfMapObjectsProvider_Metrics::Metric_obtainData* const metric_,
    const IQueryController* const queryController)
{
#if OSMAND_PERFORMANCE_METRICS
    ObfMapObjectsProvider_Metrics::Metric_obtainData localMetric;
    const auto metric = metric_ ? metric_ : &localMetric;
#else
    const auto metric = metric_;
#endif

    std::shared_ptr<TileEntry> tileEntry;

    for (;;)
    {
        // Try to obtain previous instance of tile
        _tileReferences.obtainOrAllocateEntry(tileEntry, tileId, zoom,
            []
            (const TiledEntriesCollection<TileEntry>& collection, const TileId tileId, const ZoomLevel zoom) -> TileEntry*
            {
                return new TileEntry(collection, tileId, zoom);
            });

        // If state is "Undefined", change it to "Loading" and proceed with loading
        if (tileEntry->setStateIf(TileState::Undefined, TileState::Loading))
            break;

        // In case tile entry is being loaded, wait until it will finish loading
        if (tileEntry->getState() == TileState::Loading)
        {
            QReadLocker scopedLcoker(&tileEntry->loadedConditionLock);

            // If tile is in 'Loading' state, wait until it will become 'Loaded'
            while (tileEntry->getState() != TileState::Loaded)
                REPEAT_UNTIL(tileEntry->loadedCondition.wait(&tileEntry->loadedConditionLock));
        }

        // Try to lock tile reference
        outTiledData = tileEntry->dataWeakRef.lock();

        // If successfully locked, just return it
        if (outTiledData)
            return true;

        // Otherwise consider this tile entry as expired, remove it from collection (it's safe to do that right now)
        // This will enable creation of new entry on next loop cycle
        _tileReferences.removeEntry(tileId, zoom);
        tileEntry.reset();
    }

    const Stopwatch totalTimeStopwatch(
#if OSMAND_PERFORMANCE_METRICS
        true
#else
        metric != nullptr
#endif // OSMAND_PERFORMANCE_METRICS
        );

    // Obtain OBF data interface
    const Stopwatch obtainObfInterfaceStopwatch(metric != nullptr);
    const auto& dataInterface = owner->obfsCollection->obtainDataInterface();
    if (metric)
        metric->elapsedTimeForObtainingObfInterface += obtainObfInterfaceStopwatch.elapsed();

    // Get bounding box that covers this tile
    const auto tileBBox31 = Utilities::tileBoundingBox31(tileId, zoom);

    // Perform read-out
    const Stopwatch totalReadTimeStopwatch(metric != nullptr);

    // BinaryMapObjects:
    QList< std::shared_ptr< const ObfMapSectionReader::DataBlock > > referencedBinaryMapObjectsDataBlocks;
    QList< std::shared_ptr<const BinaryMapObject> > referencedBinaryMapObjects;
    QList< proper::shared_future< std::shared_ptr<const BinaryMapObject> > > futureReferencedBinaryMapObjects;
    QList< std::shared_ptr<const BinaryMapObject> > loadedBinaryMapObjects;
    QList< std::shared_ptr<const BinaryMapObject> > loadedSharedBinaryMapObjects;
    QHash< ObfObjectId, SmartPOD<unsigned int, 0u> > allLoadedBinaryMapObjectsCounters;
    QHash< ObfObjectId, SmartPOD<unsigned int, 0u> > loadedSharedBinaryMapObjectsCounters;
    QHash< ObfObjectId, SmartPOD<unsigned int, 0u> > loadedNonSharedBinaryMapObjectsCounters;

    // Roads:
    QList< std::shared_ptr< const ObfRoutingSectionReader::DataBlock > > referencedRoadsDataBlocks;
    QList< std::shared_ptr<const Road> > referencedRoads;
    //QList< proper::shared_future< std::shared_ptr<const BinaryMapObject> > > futureReferencedBinaryMapObjects;
    //QList< std::shared_ptr<const BinaryMapObject> > loadedBinaryMapObjects;
    QList< std::shared_ptr<const Road> > loadedSharedRoads;
    //QHash< ObfObjectId, SmartPOD<unsigned int, 0u> > allLoadedBinaryMapObjectsCounters;
    //QHash< ObfObjectId, SmartPOD<unsigned int, 0u> > loadedSharedBinaryMapObjectsCounters;
    //QHash< ObfObjectId, SmartPOD<unsigned int, 0u> > loadedNonSharedBinaryMapObjectsCounters;

    auto tileSurfaceType = MapSurfaceType::Undefined;
    Ref<ObfMapSectionReader_Metrics::Metric_loadMapObjects> loadMapObjectsMetric;
    if (metric)
    {
        loadMapObjectsMetric = new ObfMapSectionReader_Metrics::Metric_loadMapObjects();
        metric->submetrics.push_back(loadMapObjectsMetric);
    }
    dataInterface->loadBinaryMapObjects(
        &loadedBinaryMapObjects,
        &tileSurfaceType,
        zoom,
        &tileBBox31,
        [this, zoom, &referencedBinaryMapObjects, &futureReferencedBinaryMapObjects, &loadedSharedBinaryMapObjectsCounters, &loadedNonSharedBinaryMapObjectsCounters, &allLoadedBinaryMapObjectsCounters, tileBBox31, metric]
        (const std::shared_ptr<const ObfMapSectionInfo>& section, const ObfObjectId id, const AreaI& bbox, const ZoomLevel firstZoomLevel, const ZoomLevel lastZoomLevel) -> bool
        {
            const Stopwatch objectsFilteringStopwatch(metric != nullptr);

            // Check if this object was not loaded before
            unsigned int& totalLoadCount = allLoadedBinaryMapObjectsCounters[id];
            if (totalLoadCount > 0u)
                return false;
            totalLoadCount++;

            // This map object may be shared only in case it crosses bounds of a tile
            const auto canNotBeShared = tileBBox31.contains(bbox);

            // If map object can not be shared, just read it
            if (canNotBeShared)
            {
                if (metric)
                    metric->elapsedTimeForObjectsFiltering += objectsFilteringStopwatch.elapsed();

                unsigned int& loadCount = loadedNonSharedBinaryMapObjectsCounters[id];
                if (loadCount > 0u)
                    return false;
                loadCount++;
                totalLoadCount++;

                return true;
            }

            // Otherwise, this map object can be shared, so it should be checked for
            // being present in shared mapObjects storage, or be reserved there
            std::shared_ptr<const BinaryMapObject> sharedMapObjectReference;
            proper::shared_future< std::shared_ptr<const BinaryMapObject> > futureSharedMapObjectReference;
            const auto existsOrWillBeInFuture = _sharedBinaryMapObjects.obtainReferenceOrFutureReferenceOrMakePromise(
                id,
                zoom,
                Utilities::enumerateZoomLevels(firstZoomLevel, lastZoomLevel),
                sharedMapObjectReference,
                futureSharedMapObjectReference);
            if (existsOrWillBeInFuture)
            {
                if (sharedMapObjectReference)
                {
                    // If map object is already in shared objects cache and is available, use that one
                    referencedBinaryMapObjects.push_back(qMove(sharedMapObjectReference));
                }
                else
                {
                    futureReferencedBinaryMapObjects.push_back(qMove(futureSharedMapObjectReference));
                }

                if (metric)
                    metric->elapsedTimeForObjectsFiltering += objectsFilteringStopwatch.elapsed();

                return false;
            }

            // This map object was reserved, and is going to be shared, but needs to be loaded (and it was promised)
            unsigned int& loadCount = loadedSharedBinaryMapObjectsCounters[id];
            if (loadCount > 0u)
                return false;
            loadCount += 1;
            totalLoadCount++;

            return true;
        },
        _binaryMapObjectsDataBlocksCache.get(),
        &referencedBinaryMapObjectsDataBlocks,
        nullptr,// query controller
        loadMapObjectsMetric.get());

    // Process loaded-and-shared map objects
    for (auto& mapObject : loadedBinaryMapObjects)
    {
        const auto id = mapObject->id;

        // Check if this map object is shared (since only shared produce promises)
        if (!loadedSharedBinaryMapObjectsCounters.contains(id))
            continue;

        // Add unique map object under lock to all zoom levels, for which this map object is valid
        assert(mapObject->level);
        _sharedBinaryMapObjects.fulfilPromiseAndReference(
            id,
            Utilities::enumerateZoomLevels(mapObject->level->minZoom, mapObject->level->maxZoom),
            mapObject);
        loadedSharedBinaryMapObjects.push_back(mapObject);
    }

    for (auto& futureMapObject : futureReferencedBinaryMapObjects)
    {
        auto mapObject = futureMapObject.get();

        referencedBinaryMapObjects.push_back(qMove(mapObject));
    }

    if (metric)
        metric->elapsedTimeForRead += totalReadTimeStopwatch.elapsed();

    // Prepare data for the tile
    const auto sharedMapObjectsCount = referencedBinaryMapObjects.size() + loadedSharedBinaryMapObjectsCounters.size();
    const auto allMapObjects = loadedBinaryMapObjects + referencedBinaryMapObjects;

    // Create tile
    const std::shared_ptr<IMapObjectsProvider::Data> newTile(new IMapObjectsProvider::Data(
        tileId,
        zoom,
        tileSurfaceType,
        copyAs< QList< std::shared_ptr<const MapObject> > >(allMapObjects),
        new RetainableCacheMetadata(
            zoom,
            _link,
            tileEntry,
            _binaryMapObjectsDataBlocksCache,
            referencedBinaryMapObjectsDataBlocks,
            referencedBinaryMapObjects + loadedSharedBinaryMapObjects,
            _roadsDataBlocksCache,
            referencedRoadsDataBlocks,
            referencedRoads + loadedSharedRoads)));

    // Publish new tile
    outTiledData = newTile;

    // Store weak reference to new tile and mark it as 'Loaded'
    tileEntry->dataWeakRef = newTile;
    tileEntry->setState(TileState::Loaded);

    // Notify that tile has been loaded
    {
        QWriteLocker scopedLcoker(&tileEntry->loadedConditionLock);
        tileEntry->loadedCondition.wakeAll();
    }

    if (metric)
    {
        metric->elapsedTime += totalTimeStopwatch.elapsed();
        metric->objectsCount += allMapObjects.size();
        metric->uniqueObjectsCount += allMapObjects.size() - sharedMapObjectsCount;
        metric->sharedObjectsCount += sharedMapObjectsCount;
    }

#if OSMAND_PERFORMANCE_METRICS
#if OSMAND_PERFORMANCE_METRICS <= 1
    LogPrintf(LogSeverityLevel::Info,
        "%d map objects (%d unique, %d shared) read from %dx%d@%d in %fs",
        allMapObjects.size(),
        allMapObjects.size() - sharedMapObjectsCount,
        sharedMapObjectsCount,
        tileId.x,
        tileId.y,
        zoom,
        totalTimeStopwatch.elapsed());
#else
    LogPrintf(LogSeverityLevel::Info,
        "%d map objects (%d unique, %d shared) read from %dx%d@%d in %fs:\n%s",
        allMapObjects.size(),
        allMapObjects.size() - sharedMapObjectsCount,
        sharedMapObjectsCount,
        tileId.x,
        tileId.y,
        zoom,
        totalTimeStopwatch.elapsed(),
        qPrintable(metric ? metric->toString(QLatin1String("\t - ")) : QLatin1String("(null)")));
#endif // OSMAND_PERFORMANCE_METRICS <= 1
#endif // OSMAND_PERFORMANCE_METRICS

    return true;
}

OsmAnd::ObfMapObjectsProvider_P::BinaryMapObjectsDataBlocksCache::BinaryMapObjectsDataBlocksCache(
    const bool cacheTileInnerDataBlocks_)
    : cacheTileInnerDataBlocks(cacheTileInnerDataBlocks_)
{
}

OsmAnd::ObfMapObjectsProvider_P::BinaryMapObjectsDataBlocksCache::~BinaryMapObjectsDataBlocksCache()
{
}

bool OsmAnd::ObfMapObjectsProvider_P::BinaryMapObjectsDataBlocksCache::shouldCacheBlock(
    const DataBlockId id,
    const AreaI blockBBox31,
    const AreaI* const queryArea31 /*= nullptr*/) const
{
    if (!queryArea31)
        return ObfMapSectionReader::DataBlocksCache::shouldCacheBlock(id, blockBBox31, queryArea31);

    if (queryArea31->contains(blockBBox31))
        return cacheTileInnerDataBlocks;
    return true;
}

OsmAnd::ObfMapObjectsProvider_P::RoadsDataBlocksCache::RoadsDataBlocksCache(
    const bool cacheTileInnerDataBlocks_)
    : cacheTileInnerDataBlocks(cacheTileInnerDataBlocks_)
{
}

OsmAnd::ObfMapObjectsProvider_P::RoadsDataBlocksCache::~RoadsDataBlocksCache()
{
}

bool OsmAnd::ObfMapObjectsProvider_P::RoadsDataBlocksCache::shouldCacheBlock(
    const DataBlockId id,
    const RoutingDataLevel dataLevel,
    const AreaI blockBBox31,
    const AreaI* const queryArea31 /*= nullptr*/) const
{
    if (!queryArea31)
        return ObfRoutingSectionReader::DataBlocksCache::shouldCacheBlock(id, dataLevel, blockBBox31, queryArea31);

    if (queryArea31->contains(blockBBox31))
        return cacheTileInnerDataBlocks;
    return true;
}

OsmAnd::ObfMapObjectsProvider_P::RetainableCacheMetadata::RetainableCacheMetadata(
    const ZoomLevel zoom_,
    const std::shared_ptr<Link>& link,
    const std::shared_ptr<TileEntry>& tileEntry,
    const std::shared_ptr<ObfMapSectionReader::DataBlocksCache>& binaryMapObjectsDataBlocksCache,
    const QList< std::shared_ptr<const ObfMapSectionReader::DataBlock> >& referencedBinaryMapObjectsDataBlocks_,
    const QList< std::shared_ptr<const BinaryMapObject> >& referencedBinaryMapObjects_,
    const std::shared_ptr<ObfRoutingSectionReader::DataBlocksCache>& roadsDataBlocksCache,
    const QList< std::shared_ptr<const ObfRoutingSectionReader::DataBlock> >& referencedRoadsDataBlocks_,
    const QList< std::shared_ptr<const Road> >& referencedRoads_)
    : zoom(zoom_)
    , weakLink(link->getWeak())
    , tileEntryWeakRef(tileEntry)
    , binaryMapObjectsDataBlocksCacheWeakRef(binaryMapObjectsDataBlocksCache)
    , referencedBinaryMapObjectsDataBlocks(referencedBinaryMapObjectsDataBlocks_)
    , referencedBinaryMapObjects(referencedBinaryMapObjects_)
    , roadsDataBlocksCacheWeakRef(roadsDataBlocksCache)
    , referencedRoadsDataBlocks(referencedRoadsDataBlocks_)
    , referencedRoads(referencedRoads_)
{
}

OsmAnd::ObfMapObjectsProvider_P::RetainableCacheMetadata::~RetainableCacheMetadata()
{
    // Dereference DataBlocks from cache
    if (const auto dataBlocksCache = binaryMapObjectsDataBlocksCacheWeakRef.lock())
    {
        for (auto& referencedDataBlock : referencedBinaryMapObjectsDataBlocks)
            dataBlocksCache->releaseReference(referencedDataBlock->id, zoom, referencedDataBlock);
        referencedBinaryMapObjectsDataBlocks.clear();
    }
    if (const auto dataBlocksCache = roadsDataBlocksCacheWeakRef.lock())
    {
        for (auto& referencedDataBlock : referencedRoadsDataBlocks)
            dataBlocksCache->releaseReference(referencedDataBlock->id, referencedDataBlock);
        referencedBinaryMapObjectsDataBlocks.clear();
    }

    // Remove tile reference from collection. All checks here does not matter,
    // since entry->tile reference is already expired (execution is already in destructor of OfflineMapDataTile!)
    if (const auto tileEntry = tileEntryWeakRef.lock())
    {
        if (const auto link = tileEntry->link.lock())
            link->collection.removeEntry(tileEntry->tileId, tileEntry->zoom);
    }

    // Dereference shared map objects
    if (const auto link = weakLink.lock())
    {
        for (auto& referencedRoad : referencedBinaryMapObjects)
            link->_sharedBinaryMapObjects.releaseReference(referencedRoad->id, zoom, referencedRoad);

        for (auto& referencedRoad : referencedRoads)
            link->_sharedRoads.releaseReference(referencedRoad->id, referencedRoad);
    }
    referencedBinaryMapObjects.clear();
    referencedRoads.clear();
}
