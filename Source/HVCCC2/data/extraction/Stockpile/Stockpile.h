/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-10 19:35:46.474699
 **/
#pragma once
#include <string>
#include "../TerminalId.h"
#include "../../util.h"
class StockpileEvent;
class StockpileState;
class Stockpile {
public:
    using AssociatedEvent = StockpileEvent;
    using AssociatedState = StockpileState;
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

bool operator<(const Stockpile::Id& a, const Stockpile::Id& b);
bool operator==(const Stockpile::Id& a, const Stockpile::Id& b);

template<class Archive>
void Stockpile::Id::serialize(Archive & archive) {
    archive(terminal, name);
}