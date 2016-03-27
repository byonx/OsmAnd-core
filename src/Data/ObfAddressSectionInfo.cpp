#include "ObfAddressSectionInfo.h"

#include "ignore_warnings_on_external_includes.h"
#include "OBF.pb.h"
#include "restore_internal_warnings.h"

typedef OsmAnd::OBF::OsmAndAddressIndex_CitiesIndex_CitiesType _ObfAddressBlockType;
static_assert(
    _ObfAddressBlockType::OsmAndAddressIndex_CitiesIndex_CitiesType_CitiesOrTowns ==
        static_cast<int>(OsmAnd::ObfAddressStreetGroupType::CityOrTown) &&
    _ObfAddressBlockType::OsmAndAddressIndex_CitiesIndex_CitiesType_Postcodes ==
        static_cast<int>(OsmAnd::ObfAddressStreetGroupType::Postcode) &&
    _ObfAddressBlockType::OsmAndAddressIndex_CitiesIndex_CitiesType_Villages ==
        static_cast<int>(OsmAnd::ObfAddressStreetGroupType::Village),
    "OsmAnd::ObfAddressStreetGroupType must match OBF::OsmAndAddressIndex_CitiesIndex_CitiesType");

OsmAnd::ObfAddressSectionInfo::ObfAddressSectionInfo(const std::shared_ptr<const ObfInfo>& container_)
    : ObfSectionInfo(container_)
    , nameIndexInnerOffset(0)
    , firstStreetGroupInnerOffset(0)
{
}

OsmAnd::ObfAddressSectionInfo::~ObfAddressSectionInfo()
{
}
//
//OsmAnd::ObfAddressBlocksSectionInfo::ObfAddressBlocksSectionInfo(const std::shared_ptr<const ObfAddressSectionInfo>& addressSection, const std::shared_ptr<const ObfInfo>& container)
//    : ObfSectionInfo(container)
//    , type(_type)
//{
//}
//
//OsmAnd::ObfAddressBlocksSectionInfo::~ObfAddressBlocksSectionInfo()
//{
//}
