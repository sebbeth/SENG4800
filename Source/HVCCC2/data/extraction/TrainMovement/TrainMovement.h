/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-07 18:18:44.676555
 **/
#pragma once
#include <string>
#include "../TerminalId.h"
#include "../../util.h"
class TrainMovementEvent;
class TrainMovementState;
class TrainMovement {
public:
    using AssociatedEvent = TrainMovementEvent;
        using AssociatedState = TrainMovementState;
    static const std::string ENTITY_NAME;
    static const std::string XML_TAG_PREFIX;
    class Id {
    public:
        using Entity = TrainMovement;
        std::string name;
        Id();
        Id(const std::string& name);        std::string nameForBinaryFile() const;
        template<class Archive>
        void serialize(Archive & archive);
    };
};

bool operator<(const TrainMovement::Id& a, const TrainMovement::Id& b);
bool operator==(const TrainMovement::Id& a, const TrainMovement::Id& b);
bool operator!=(const TrainMovement::Id& a, const TrainMovement::Id& b);

template<class Archive>
void TrainMovement::Id::serialize(Archive & archive) {
    archive(name);
}