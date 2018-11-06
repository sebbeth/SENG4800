/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#pragma once
#include <string>
#include "../TerminalId.h"
#include "../../util.h"
class DumpstationEvent;
class DumpstationState;
class Dumpstation {
public:
    using AssociatedEvent = DumpstationEvent;
        using AssociatedState = DumpstationState;
    static const std::string ENTITY_NAME;
    static const std::string XML_TAG_PREFIX;
    class Id {
    public:
        using Entity = Dumpstation;
        TerminalId terminal;
        std::string name;
        Id();
        Id(TerminalId terminal, const std::string& name);        std::string nameForBinaryFile() const;
        template<class Archive>
        void serialize(Archive & archive);
    };
};

bool operator<(const Dumpstation::Id& a, const Dumpstation::Id& b);
bool operator==(const Dumpstation::Id& a, const Dumpstation::Id& b);
bool operator!=(const Dumpstation::Id& a, const Dumpstation::Id& b);

template<class Archive>
void Dumpstation::Id::serialize(Archive & archive) {
    archive(terminal, name);
}