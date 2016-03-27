#ifndef _OSMAND_CORE_STREET_H_
#define _OSMAND_CORE_STREET_H_

#include <OsmAndCore/stdlib_common.h>

#include <OsmAndCore/QtExtensions.h>
#include <QString>
#include <QHash>

#include <OsmAndCore.h>
#include <OsmAndCore/CommonTypes.h>
#include <OsmAndCore/PointsAndAreas.h>
#include <OsmAndCore/Data/DataCommonTypes.h>
#include <OsmAndCore/Data/Address.h>

namespace OsmAnd
{
    class StreetGroup;

    class OSMAND_CORE_API Street Q_DECL_FINAL : public Address
    {
        Q_DISABLE_COPY_AND_MOVE(Street);

    private:
    protected:
    public:
        Street(const std::shared_ptr<const StreetGroup>& streetGroup);
        virtual ~Street();

        ObfObjectId id;
        QString nativeName;
        QHash<QString, QString> localizedNames;
        PointI position31;
        uint32_t offset;
        uint32_t firstBuildingInnerOffset;
        uint32_t firstIntersectionInnerOffset;

        const std::shared_ptr<const StreetGroup> streetGroup;
    };
}

#endif // !defined(_OSMAND_CORE_STREET_H_)

