/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 15:53:43.172985
 **/
#pragma once
#include "StackerReclaimer.h"
#include "StackerReclaimerStateType.h"
#include "../Stacker/StackerState.h"
#include "../Reclaimer/ReclaimerState.h"
class StackerReclaimerState {
    using Entity = StackerReclaimer;
    Entity::Id id;
    StackerReclaimerStateType type;
    double position;
    double time;
    Stockpile::Id stockpileID;
    double amount;
    StackerReclaimerState(const StackerState& src);
    StackerReclaimerState(const ReclaimerState& src);
    template<class Archive>
    void serialize(Archive & archive);
};

template<class Archive>
void StackerReclaimerState::serialize(Archive & archive) {
    archive(id, type, amount, position, stockpileID, time);
}