/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 20:05:50.446537
 **/
#pragma once
#include <string>
#include "../TerminalId.h"
#include "../../util.h"
class StackerEvent;
class StackerState;
class Stacker {
public:
    using AssociatedEvent = StackerEvent;
        using AssociatedState = StackerState;
    static const std::string ENTITY_NAME;
    static const std::string XML_TAG_PREFIX;
    class Id {
    public:
        using Entity = Stacker;
        TerminalId terminal;
        std::string name;
        Id();
        Id(TerminalId terminal, const std::string& name);        std::string nameForBinaryFile() const;
        template<class Archive>
        void serialize(Archive & archive);
    };
};

bool operator<(const Stacker::Id& a, const Stacker::Id& b);
bool operator==(const Stacker::Id& a, const Stacker::Id& b);
bool operator!=(const Stacker::Id& a, const Stacker::Id& b);

template<class Archive>
void Stacker::Id::serialize(Archive & archive) {
    archive(terminal, name);
}