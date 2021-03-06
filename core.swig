%module(directors="1") OsmAndCore

// Namespaces are useless at this point
//%nspace;

%{
#include <OsmAndCore.h>
#include <OsmAndCore/CommonTypes.h>
#include <OsmAndCore/Color.h>
#include <OsmAndCore/PointsAndAreas.h>
#include <OsmAndCore/LatLon.h>
#include <OsmAndCore/Bitmask.h>
#include <OsmAndCore/ResourcesManager.h>
#include <OsmAndCore/IObfsCollection.h>
#include <OsmAndCore/ObfsCollection.h>
#include <OsmAndCore/ObfDataInterface.h>
#include <OsmAndCore/ICoreResourcesProvider.h>
#include <OsmAndCore/CoreResourcesEmbeddedBundle.h>
#include <OsmAndCore/IFontFinder.h>
#include <OsmAndCore/CachingFontFinder.h>
#include <OsmAndCore/ChainedFontFinder.h>
#include <OsmAndCore/EmbeddedFontFinder.h>
#include <OsmAndCore/SystemFontFinder.h>
#include <OsmAndCore/TextRasterizer.h>
#include <OsmAndCore/Logging.h>
#include <OsmAndCore/ILogSink.h>
#include <OsmAndCore/DefaultLogSink.h>
#include <OsmAndCore/QIODeviceLogSink.h>
#include <OsmAndCore/Utilities.h>
#include <OsmAndCore/WorldRegions.h>
#include <OsmAndCore/Data/DataCommonTypes.h>
#include <OsmAndCore/Data/ObfFile.h>
#include <OsmAndCore/Data/ObfInfo.h>
#include <OsmAndCore/Data/MapObject.h>
#include <OsmAndCore/Data/ObfMapObject.h>
#include <OsmAndCore/Data/BinaryMapObject.h>
#include <OsmAndCore/Data/Road.h>
#include <OsmAndCore/Map/MapCommonTypes.h>
#include <OsmAndCore/Map/MapSymbolsGroup.h>
#include <OsmAndCore/Map/MapSymbol.h>
#include <OsmAndCore/Map/SymbolRasterizer.h>
#include <OsmAndCore/Map/IMapStylesCollection.h>
#include <OsmAndCore/Map/UnresolvedMapStyle.h>
#include <OsmAndCore/Map/MapStyleConstantValue.h>
#include <OsmAndCore/Map/MapStyleValueDefinition.h>
#include <OsmAndCore/Map/IMapStyle.h>
#include <OsmAndCore/Map/ResolvedMapStyle.h>
#include <OsmAndCore/Map/MapStylesCollection.h>
#include <OsmAndCore/Map/MapStyleBuiltinValueDefinitions.h>
#include <OsmAndCore/Map/MapPresentationEnvironment.h>
#include <OsmAndCore/Map/MapRendererState.h>
#include <OsmAndCore/Map/MapRendererSetupOptions.h>
#include <OsmAndCore/Map/MapRendererConfiguration.h>
#include <OsmAndCore/Map/MapRendererDebugSettings.h>
#include <OsmAndCore/Map/MapRendererTypes.h>
#include <OsmAndCore/Map/IMapRenderer.h>
#include <OsmAndCore/Map/AtlasMapRendererConfiguration.h>
#include <OsmAndCore/Map/IMapDataProvider.h>
#include <OsmAndCore/Map/IMapTiledDataProvider.h>
#include <OsmAndCore/Map/IMapKeyedDataProvider.h>
#include <OsmAndCore/Map/IMapElevationDataProvider.h>
#include <OsmAndCore/Map/IMapLayerProvider.h>
#include <OsmAndCore/Map/IRasterMapLayerProvider.h>
#include <OsmAndCore/Map/ImageMapLayerProvider.h>
#include <OsmAndCore/Map/IMapTiledSymbolsProvider.h>
#include <OsmAndCore/Map/IMapKeyedSymbolsProvider.h>
#include <OsmAndCore/Map/MapPrimitiviser.h>
#include <OsmAndCore/Map/IMapObjectsProvider.h>
#include <OsmAndCore/Map/MapObjectsProvider.h>
#include <OsmAndCore/Map/ObfMapObjectsProvider.h>
#include <OsmAndCore/Map/MapPrimitivesProvider.h>
#include <OsmAndCore/Map/MapObjectsSymbolsProvider.h>
#include <OsmAndCore/Map/MapRasterLayerProvider.h>
#include <OsmAndCore/Map/MapRasterLayerProvider_Software.h>
#include <OsmAndCore/Map/IOnlineTileSources.h>
#include <OsmAndCore/Map/OnlineTileSources.h>
#include <OsmAndCore/Map/OnlineRasterMapLayerProvider.h>
#include "SwigUtilities.h"

// To omit 'OsmAnd::' prefixes inside namespace itself in headers, use that namespace for SWIG
using namespace OsmAnd;
%}

#if defined(SWIG_JAVA) || defined(SWIG_CSHARP)
	%include <enums.swg>
#endif
%include <typemaps.i>
%include <carrays.i>
#if defined(SWIG_JAVA)
	%include <various.i>
#endif
%include <stdint.i>
%include <cpointer.i>
	%pointer_class(bool, BoolPtr);
	%pointer_class(int, IntPtr);
	%pointer_class(unsigned int, UIntPtr);
	%pointer_class(float, FloatPtr);
	%pointer_class(double, DoublePtr);
%include <std_shared_ptr.i>
	%shared_ptr(OsmAnd::IObfsCollection)
	%shared_ptr(OsmAnd::ObfsCollection)
	%shared_ptr(OsmAnd::ObfDataInterface)
	%shared_ptr(OsmAnd::ResourcesManager::Resource)
	%shared_ptr(OsmAnd::ResourcesManager::Resource::Metadata)
	%shared_ptr(OsmAnd::ResourcesManager::BuiltinResource)
	%shared_ptr(OsmAnd::ResourcesManager::LocalResource)
	%shared_ptr(OsmAnd::ResourcesManager::ResourceInRepository)
	%shared_ptr(OsmAnd::ResourcesManager::InstalledResource)
	%shared_ptr(OsmAnd::ResourcesManager::UnmanagedResource)
	%shared_ptr(OsmAnd::ResourcesManager::ObfMetadata)
	%shared_ptr(OsmAnd::ResourcesManager::MapStyleMetadata)
	%shared_ptr(OsmAnd::ResourcesManager::OnlineTileSourcesMetadata)
	%shared_ptr(OsmAnd::ICoreResourcesProvider)
	%shared_ptr(OsmAnd::CoreResourcesEmbeddedBundle)
	%shared_ptr(OsmAnd::IFontFinder)
	%shared_ptr(OsmAnd::CachingFontFinder)
	%shared_ptr(OsmAnd::ChainedFontFinder)
	%shared_ptr(OsmAnd::EmbeddedFontFinder)
	%shared_ptr(OsmAnd::SystemFontFinder)
	%shared_ptr(OsmAnd::TextRasterizer)
	%shared_ptr(OsmAnd::Logger)
	%shared_ptr(OsmAnd::ILogSink)
	%shared_ptr(OsmAnd::DefaultLogSink)
	%shared_ptr(OsmAnd::QIODeviceLogSink)
	%shared_ptr(OsmAnd::ObfFile)
	%shared_ptr(OsmAnd::ObfInfo)
	%shared_ptr(OsmAnd::MapObject)
	%shared_ptr(OsmAnd::ObfMapObject)
	%shared_ptr(OsmAnd::BinaryMapObject)
	%shared_ptr(OsmAnd::Road)
	%shared_ptr(OsmAnd::MapSymbolsGroup)
	%shared_ptr(OsmAnd::MapSymbol)
	%shared_ptr(OsmAnd::SymbolRasterizer)
	%shared_ptr(OsmAnd::UnresolvedMapStyle)
	%shared_ptr(OsmAnd::UnresolvedMapStyle::RuleNode)
	%shared_ptr(OsmAnd::UnresolvedMapStyle::BaseRule)
	%shared_ptr(OsmAnd::UnresolvedMapStyle::Rule)
	%shared_ptr(OsmAnd::UnresolvedMapStyle::Attribute)
	%shared_ptr(OsmAnd::UnresolvedMapStyle::Parameter)
	%shared_ptr(OsmAnd::MapStyleConstantValue)
	%shared_ptr(OsmAnd::MapStyleValueDefinition)
	%shared_ptr(OsmAnd::IMapStyle)
	%shared_ptr(OsmAnd::IMapStyle::Value)
	%shared_ptr(OsmAnd::IMapStyle::IRuleNode)
	%shared_ptr(OsmAnd::IMapStyle::IRule)
	%shared_ptr(OsmAnd::IMapStyle::IAttribute)
	%shared_ptr(OsmAnd::IMapStyle::IParameter)
	%shared_ptr(OsmAnd::ResolvedMapStyle)
	%shared_ptr(OsmAnd::ResolvedMapStyle::ResolvedValue)
	%shared_ptr(OsmAnd::ResolvedMapStyle::RuleNode)
	%shared_ptr(OsmAnd::ResolvedMapStyle::BaseRule)
	%shared_ptr(OsmAnd::ResolvedMapStyle::Rule)
	%shared_ptr(OsmAnd::ResolvedMapStyle::Attribute)
	%shared_ptr(OsmAnd::ResolvedMapStyle::Parameter)
	%shared_ptr(OsmAnd::ResolvedMapStyle::ParameterValueDefinition)
	%shared_ptr(OsmAnd::IMapStylesCollection)
	%shared_ptr(OsmAnd::MapStylesCollection)
	%shared_ptr(OsmAnd::MapStyleBuiltinValueDefinitions)
	%shared_ptr(OsmAnd::MapStyleBuiltinValueDefinitions::MapStyleBuiltinValueDefinition)
	%shared_ptr(OsmAnd::MapPresentationEnvironment)
	%shared_ptr(OsmAnd::MapRendererSetupOptions)
	%shared_ptr(OsmAnd::MapRendererConfiguration)
	%shared_ptr(OsmAnd::MapRendererDebugSettings)
	%shared_ptr(OsmAnd::IMapRenderer)
	%shared_ptr(OsmAnd::AtlasMapRendererConfiguration)
	%shared_ptr(OsmAnd::IMapDataProvider)
	%shared_ptr(OsmAnd::IMapTiledDataProvider)
	%shared_ptr(OsmAnd::IMapKeyedDataProvider)
	%shared_ptr(OsmAnd::IMapElevationDataProvider)
	%shared_ptr(OsmAnd::IMapLayerProvider)
	%shared_ptr(OsmAnd::IRasterMapLayerProvider)
	%shared_ptr(OsmAnd::ImageMapLayerProvider)
	%shared_ptr(OsmAnd::IMapTiledSymbolsProvider)
	%shared_ptr(OsmAnd::IMapKeyedSymbolsProvider)
	%shared_ptr(OsmAnd::MapPrimitiviser)
	%shared_ptr(OsmAnd::MapPrimitiviser::CoastlineMapObject)
	%shared_ptr(OsmAnd::MapPrimitiviser::SurfaceMapObject)
	%shared_ptr(OsmAnd::MapPrimitiviser::Cache)
	%shared_ptr(OsmAnd::MapPrimitiviser::Primitive)
	%shared_ptr(OsmAnd::MapPrimitiviser::PrimitivesGroup)
	%shared_ptr(OsmAnd::MapPrimitiviser::Symbol)
	%shared_ptr(OsmAnd::MapPrimitiviser::SymbolsGroup)
	%shared_ptr(OsmAnd::MapPrimitiviser::TextSymbol)
	%shared_ptr(OsmAnd::MapPrimitiviser::IconSymbol)
	%shared_ptr(OsmAnd::MapPrimitiviser::PrimitivisedArea)
	%shared_ptr(OsmAnd::IMapObjectsProvider)
	%shared_ptr(OsmAnd::ObfMapObjectsProvider)
	%shared_ptr(OsmAnd::MapObjectsProvider)
	%shared_ptr(OsmAnd::MapPrimitivesProvider)
	%shared_ptr(OsmAnd::MapObjectsSymbolsProvider)
	%shared_ptr(OsmAnd::MapObjectsSymbolsProvider::MapObjectSymbolsGroup)
	%shared_ptr(OsmAnd::MapRasterLayerProvider)
	%shared_ptr(OsmAnd::MapRasterLayerProvider_Software)
	%shared_ptr(OsmAnd::IOnlineTileSources)
	%shared_ptr(OsmAnd::IOnlineTileSources::Source)
	%shared_ptr(OsmAnd::OnlineTileSources)
	%shared_ptr(OsmAnd::OnlineRasterMapLayerProvider)
%include <std_pair.i>
%include <std_string.i>
#ifdef SWIG_JAVA
	%include <swig/java/QString.i>
		%apply QString { std::string };
#endif
%include <std_vector.i>
#ifdef SWIG_JAVA
	%include <swig/java/QList.i>
		%template(QStringList) QList<QString>;
	%include <swig/java/QVector.i>
#endif
%include <std_map.i>
#ifdef SWIG_JAVA
	%include <swig/java/QHash.i>
	%include <swig/java/QMap.i>
#endif
%template(QStringStringHash) QHash<QString, QString>;
%template(QStringStringMap) QMap<QString, QString>;
#ifdef SWIG_JAVA
	%include <swig/java/byteArrays.i>
#endif

#ifdef SWIG_JAVA
	%rename(equals) operator==;
	%rename(notEquals) operator!=;
	%rename(method) operator();
#endif
%include <swig/OsmAndCore_Stubs.h>
%include <swig/SwigUtilities.h>
%include <OsmAndCore.h>
%include <OsmAndCore/CommonSWIG.h>
%include <OsmAndCore/QuickAccessors.h>
%include <OsmAndCore/Observable.h>
%include <OsmAndCore/Callable.h>
%include <OsmAndCore/CommonTypes.h>
%include <OsmAndCore/Color.h>
%include <OsmAndCore/PointsAndAreas.h>
	%template(PointI) OsmAnd::Point<int32_t>;
//	%template(PointI64) OsmAnd::Point<int64_t>;
	%template(PointF) OsmAnd::Point<float>;
	%template(PointD) OsmAnd::Point<double>;
	%template(AreaI) OsmAnd::Area<int32_t>;
//	%template(AreaI64) OsmAnd::Area<int64_t>;
	%template(AreaF) OsmAnd::Area<float>;
	%template(AreaD) OsmAnd::Area<double>;
	%template(OOBBI) OsmAnd::OOBB<int32_t>;
//	%template(OOBBI64) OsmAnd::OOBB<int64_t>;
	%template(OOBBF) OsmAnd::OOBB<float>;
	%template(OOBBD) OsmAnd::OOBB<double>;
%include <OsmAndCore/LatLon.h>
%include <OsmAndCore/Bitmask.h>
	%template(MapRendererStateChanges) OsmAnd::Bitmask<OsmAnd::MapRendererStateChange, unsigned int>;
%include <OsmAndCore/IObfsCollection.h>
%include <OsmAndCore/ObfsCollection.h>
%include <OsmAndCore/ObfDataInterface.h>
%include <OsmAndCore/ResourcesManager.h>
%include <OsmAndCore/ICoreResourcesProvider.h>
%include <OsmAndCore/CoreResourcesEmbeddedBundle.h>
%include <OsmAndCore/IFontFinder.h>
%include <OsmAndCore/CachingFontFinder.h>
%include <OsmAndCore/ChainedFontFinder.h>
%include <OsmAndCore/EmbeddedFontFinder.h>
%include <OsmAndCore/SystemFontFinder.h>
%include <OsmAndCore/TextRasterizer.h>
%include <OsmAndCore/Logging.h>
%include <OsmAndCore/ILogSink.h>
%include <OsmAndCore/DefaultLogSink.h>
%include <OsmAndCore/QIODeviceLogSink.h>
%include <OsmAndCore/Utilities.h>
%include <OsmAndCore/WorldRegions.h>
%include <OsmAndCore/Data/DataCommonTypes.h>
%include <OsmAndCore/Data/ObfFile.h>
%include <OsmAndCore/Data/ObfInfo.h>
%include <OsmAndCore/Data/MapObject.h>
%include <OsmAndCore/Data/ObfMapObject.h>
%include <OsmAndCore/Data/BinaryMapObject.h>
%include <OsmAndCore/Data/Road.h>
%include <OsmAndCore/Map/MapCommonTypes.h>
%include <OsmAndCore/Map/MapSymbol.h>
%include <OsmAndCore/Map/MapSymbolsGroup.h>
%include <OsmAndCore/Map/SymbolRasterizer.h>
%include <OsmAndCore/Map/UnresolvedMapStyle.h>
%include <OsmAndCore/Map/MapStyleConstantValue.h>
%include <OsmAndCore/Map/MapStyleValueDefinition.h>
%include <OsmAndCore/Map/IMapStyle.h>
%include <OsmAndCore/Map/ResolvedMapStyle.h>
%include <OsmAndCore/Map/IMapStylesCollection.h>
%include <OsmAndCore/Map/MapStylesCollection.h>
%include <OsmAndCore/Map/MapStyleBuiltinValueDefinitions.h>
%include <OsmAndCore/Map/MapPresentationEnvironment.h>
%include <OsmAndCore/Map/MapRendererState.h>
%include <OsmAndCore/Map/MapRendererSetupOptions.h>
%include <OsmAndCore/Map/MapRendererConfiguration.h>
%include <OsmAndCore/Map/MapRendererDebugSettings.h>
%include <OsmAndCore/Map/MapRendererTypes.h>
%include <OsmAndCore/Map/IMapRenderer.h>
%include <OsmAndCore/Map/AtlasMapRendererConfiguration.h>
%include <OsmAndCore/Map/IMapDataProvider.h>
%include <OsmAndCore/Map/IMapTiledDataProvider.h>
%include <OsmAndCore/Map/IMapKeyedDataProvider.h>
%include <OsmAndCore/Map/IMapElevationDataProvider.h>
%include <OsmAndCore/Map/IMapLayerProvider.h>
%include <OsmAndCore/Map/IRasterMapLayerProvider.h>
%include <OsmAndCore/Map/ImageMapLayerProvider.h>
%include <OsmAndCore/Map/IMapTiledSymbolsProvider.h>
%include <OsmAndCore/Map/IMapKeyedSymbolsProvider.h>
%include <OsmAndCore/Map/MapPrimitiviser.h>
%include <OsmAndCore/Map/IMapObjectsProvider.h>
%include <OsmAndCore/Map/ObfMapObjectsProvider.h>
%include <OsmAndCore/Map/MapPrimitivesProvider.h>
%include <OsmAndCore/Map/MapObjectsSymbolsProvider.h>
%include <OsmAndCore/Map/MapRasterLayerProvider.h>
%include <OsmAndCore/Map/MapRasterLayerProvider_Software.h>
%include <OsmAndCore/Map/IOnlineTileSources.h>
%include <OsmAndCore/Map/OnlineTileSources.h>
%include <OsmAndCore/Map/OnlineRasterMapLayerProvider.h>
