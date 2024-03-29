/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-08 19:15:43.572274
 **/
#pragma once
#include <string>
#include "../TerminalId.h"
#include "../../util.h"
class ShiploaderEvent;
class ShiploaderState;
class Shiploader {
public:
    using AssociatedEvent = ShiploaderEvent;
        using AssociatedState = ShiploaderState;
    static const std::string ENTITY_NAME;
    static const std::string XML_TAG_PREFIX;
    class Id {
    public:
        using Entity = Shiploader;
        TerminalId terminal;
        std::string name;
        Id();
        Id(TerminalId terminal, const std::string& name);        std::string nameForBinaryFile() const;
        template<class Archive>
        void serialize(Archive & archive);
    };
};

bool operator<(const Shiploader::Id& a, const Shiploader::Id& b);
bool operator==(const Shiploader::Id& a, const Shiploader::Id& b);
bool operator!=(const Shiploader::Id& a, const Shiploader::Id& b);

template<class Archive>
void Shiploader::Id::serialize(Archive & archive) {
    archive(terminal, name);
}