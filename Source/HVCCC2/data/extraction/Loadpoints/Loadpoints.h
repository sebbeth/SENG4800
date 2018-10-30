/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-30 21:30:03.549963
 **/
#pragma once
#include <string>
#include "../TerminalId.h"
#include "../../util.h"
class LoadpointsEvent;
class LoadpointsState;
class Loadpoints {
public:
    using AssociatedEvent = LoadpointsEvent;
        using AssociatedState = LoadpointsState;
    static const std::string ENTITY_NAME;
    static const std::string XML_TAG_PREFIX;
    class Id {
    public:
        using Entity = Loadpoints;
        std::string name;
        Id();
        Id(const std::string& name);        std::string nameForBinaryFile() const;
        template<class Archive>
        void serialize(Archive & archive);
    };
};

bool operator<(const Loadpoints::Id& a, const Loadpoints::Id& b);
bool operator==(const Loadpoints::Id& a, const Loadpoints::Id& b);
bool operator!=(const Loadpoints::Id& a, const Loadpoints::Id& b);

template<class Archive>
void Loadpoints::Id::serialize(Archive & archive) {
    archive(name);
}