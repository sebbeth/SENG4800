/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-30 21:30:03.549963
 **/
#pragma once
#include <string>
#include "../TerminalId.h"
#include "../../util.h"
class VesselEvent;
class VesselState;
class Vessel {
public:
    using AssociatedEvent = VesselEvent;
        using AssociatedState = VesselState;
    static const std::string ENTITY_NAME;
    static const std::string XML_TAG_PREFIX;
    class Id {
    public:
        using Entity = Vessel;
        std::string name;
        Id();
        Id(const std::string& name);        std::string nameForBinaryFile() const;
        template<class Archive>
        void serialize(Archive & archive);
    };
};

bool operator<(const Vessel::Id& a, const Vessel::Id& b);
bool operator==(const Vessel::Id& a, const Vessel::Id& b);
bool operator!=(const Vessel::Id& a, const Vessel::Id& b);

template<class Archive>
void Vessel::Id::serialize(Archive & archive) {
    archive(name);
}