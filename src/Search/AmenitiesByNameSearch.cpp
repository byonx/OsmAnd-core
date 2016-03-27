#include "AmenitiesByNameSearch.h"

#include "ObfDataInterface.h"
#include "Amenity.h"

OsmAnd::AmenitiesByNameSearch::AmenitiesByNameSearch(const std::shared_ptr<const IObfsCollection>& obfsCollection_)
    : BaseSearch(obfsCollection_)
{
}

OsmAnd::AmenitiesByNameSearch::~AmenitiesByNameSearch()
{
}

void OsmAnd::AmenitiesByNameSearch::performSearch(
    const ISearch::Criteria& criteria_,
    const NewResultEntryCallback newResultEntryCallback,
    const std::shared_ptr<const IQueryController>& queryController /*= nullptr*/) const
{
    const auto criteria = *dynamic_cast<const Criteria*>(&criteria_);

    const auto dataInterface = obfsCollection->obtainDataInterface(
        criteria.bbox31.getValuePtrOrNullptr(),
        MinZoomLevel,
        MaxZoomLevel,
        ObfDataTypesMask().set(ObfDataType::POI),
        criteria.sourceFilter);

    const ObfPoiSectionReader::VisitorFunction visitorFunction =
        [newResultEntryCallback, criteria_]
        (const std::shared_ptr<const OsmAnd::Amenity>& amenity) -> bool
        {
            ResultEntry resultEntry;
            resultEntry.amenity = amenity;
            newResultEntryCallback(criteria_, resultEntry);

            return true;
        };

    dataInterface->scanAmenitiesByName(
        criteria.name,
        nullptr,
        criteria.bbox31.getValuePtrOrNullptr(),
        criteria.tileFilter,
        criteria.categoriesFilter.isEmpty() ? nullptr : &criteria.categoriesFilter,
        visitorFunction,
        queryController);
}

OsmAnd::AmenitiesByNameSearch::Criteria::Criteria()
{
}

OsmAnd::AmenitiesByNameSearch::Criteria::~Criteria()
{
}

OsmAnd::AmenitiesByNameSearch::ResultEntry::ResultEntry()
{
}

OsmAnd::AmenitiesByNameSearch::ResultEntry::~ResultEntry()
{
}
