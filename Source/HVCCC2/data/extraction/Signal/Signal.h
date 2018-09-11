/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-10 19:35:46.474699
 **/
#pragma once
#include <string>
#include "../TerminalId.h"
#include "../../util.h"
class SignalEvent;
class SignalState;
class Signal {
public:
    using AssociatedEvent = SignalEvent;
    using AssociatedState = SignalState;
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

bool operator<(const Signal::Id& a, const Signal::Id& b);
bool operator==(const Signal::Id& a, const Signal::Id& b);

template<class Archive>
void Signal::Id::serialize(Archive & archive) {
    archive(name);
}