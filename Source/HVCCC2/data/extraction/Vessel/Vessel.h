/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-10 19:35:46.474699
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
        std::string name;
        std::string nameForBinaryFile() const;
        template<class Archive>
        void serialize(Archive & archive);
    };
};

bool operator<(const Vessel::Id& a, const Vessel::Id& b);
bool operator==(const Vessel::Id& a, const Vessel::Id& b);

template<class Archive>
void Vessel::Id::serialize(Archive & archive) {
    archive(name);
}