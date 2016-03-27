#include "Road.h"

#include "ObfRoutingSectionInfo.h"
#include "ObfRoutingSectionInfo_P.h"

OsmAnd::Road::Road(const std::shared_ptr<const ObfRoutingSectionInfo>& section_)
    : ObfMapObject(section_)
    , section(section_)
{
    attributeMapping = section->getAttributeMapping();
}

//OsmAnd::Road::Road( const std::shared_ptr<const Road>& that, int insertIdx, uint32_t x31, uint32_t y31 )
//    : _ref(that)
//    , _id(0)
//    , _points(_ref->_points.size() + 1)
//    , subsection(_ref->subsection)
//    , id(_ref->_id)
//    , names(_ref->_names)
//    , points(_points)
//    , types(_ref->_types)
//    , pointsTypes(_pointsTypes)
//    , restrictions(_ref->_restrictions)
//{
//    int pointIdx = 0;
//    for(; pointIdx < insertIdx; pointIdx++)
//    {
//        _points[pointIdx] = _ref->_points[pointIdx];
//        if (!_ref->_pointsTypes.isEmpty())
//            _pointsTypes.insert(pointIdx, _ref->_pointsTypes[pointIdx]);
//    }
//    _points[pointIdx++] = PointI(x31, y31);
//    for(const auto count = _points.size(); pointIdx < count; pointIdx++)
//    {
//        _points[pointIdx] = _ref->_points[pointIdx - 1];
//        if (!_ref->_pointsTypes.isEmpty())
//            _pointsTypes.insert(pointIdx, _ref->_pointsTypes[pointIdx]);
//    }
//}

OsmAnd::Road::~Road()
{
}

//double OsmAnd::Road::getDirectionDelta( uint32_t originIdx, bool forward ) const
//{
//    //NOTE: Victor: the problem to put more than 5 meters that BinaryRoutePlanner will treat
//    // 2 consequent Turn Right as UT and here 2 points will have same turn angle
//    // So it should be fix in both places
//    return getDirectionDelta(originIdx, forward, 5);
//}
//
//double OsmAnd::Road::getDirectionDelta( uint32_t originIdx, bool forward, float distance ) const
//{
//    auto itPoint = (_points.cbegin() + originIdx);
//    const auto itOriginPoint = itPoint;
//    float scannedDistance = 0.0;
//    do
//    {
//        if (forward)
//        {
//            itPoint++;
//            if (itPoint == _points.cend())
//            {
//                itPoint--;
//                break;
//            }
//        }
//        else
//        {
//            if (itPoint == _points.cbegin())
//                break;
//            itPoint--;
//        }
//
//        // translate into meters
//        scannedDistance +=
//            Utilities::x31toMeters(qAbs((int64_t)itPoint->x - (int64_t)itOriginPoint->x)) +
//            Utilities::y31toMeters(qAbs((int64_t)itPoint->y - (int64_t)itOriginPoint->y));
//    } while ( scannedDistance < distance );
//
//    return -qAtan2(itOriginPoint->x - itPoint->x, itOriginPoint->y - itPoint->y);
//}
//
//OsmAnd::RoadDirection OsmAnd::Road::getDirection() const
//{
//    const auto& encRules = subsection->section->_p->_encodingRules;
//    for(const auto& type : constOf(types))
//    {
//        const auto& rule = encRules[type];
//
//        if (rule->_type == ObfRoutingSectionInfo_P::EncodingRule::OneWay)
//            return static_cast<RoadDirection>(rule->_parsedValue.asSignedInt);
//        else if (rule->_type == ObfRoutingSectionInfo_P::EncodingRule::Roundabout)
//            return RoadDirection::OneWayForward;
//    }
//    
//    return RoadDirection::TwoWay;
//}
//
//bool OsmAnd::Road::isRoundabout() const
//{
//    const auto& encRules = subsection->section->_p->_encodingRules;
//    for(const auto& type : constOf(types))
//    {
//        const auto& rule = encRules[type];
//
//        if (rule->isRoundabout())
//            return true;
//        else if (rule->getDirection() != RoadDirection::TwoWay && isLoop())
//            return true;
//    }
//
//    return false;
//}
//
//int OsmAnd::Road::getLanes() const
//{
//    const auto& encRules = subsection->section->_p->_encodingRules;
//    for(const auto& type : constOf(types))
//    {
//        const auto& rule = encRules[type];
//
//        if (rule->_type == ObfRoutingSectionInfo_P::EncodingRule::Lanes)
//            return rule->_parsedValue.asUnsignedInt;
//    }
//    return -1;
//}
//
//QString OsmAnd::Road::getHighway() const
//{
//    const auto& encRules = subsection->section->_p->_encodingRules;
//    for(const auto& type : constOf(types))
//    {
//        const auto& rule = encRules[type];
//
//        if (rule->_type == ObfRoutingSectionInfo_P::EncodingRule::Highway)
//            return rule->_value;
//    }
//    return QString();
//}
//
//bool OsmAnd::Road::isLoop() const
//{
//    assert(_points.size() > 0);
//
//    return _points.first() == _points.last();
//}
