/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 14:36:15.744470
 **/
#pragma once
#include <string>
#include "../TerminalId.h"
#include "../../util.h"
class ReclaimerEvent;
class ReclaimerState;
class Reclaimer {
public:
    using AssociatedEvent = ReclaimerEvent;
     using AssociatedState = ReclaimerState;
     static const std::string ENTITY_NAME;
    static const std::string XML_TAG_PREFIX;
    class Id {
    public:
        TerminalId terminal;
        std::string name;
        std::string nameForBinaryFile() const;
        template<class Archive>
        void serialize(Archive & archive);
    };
};

bool operator<(const Reclaimer::Id& a, const Reclaimer::Id& b);
bool operator==(const Reclaimer::Id& a, const Reclaimer::Id& b);

template<class Archive>
void Reclaimer::Id::serialize(Archive & archive) {
    archive(terminal, name);
}