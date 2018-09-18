/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 20:48:43.204362
 **/
#pragma once
#include <string>
#include "../TerminalId.h"
#include "../../util.h"
#include "../Stacker/Stacker.h"
#include "../Reclaimer/Reclaimer.h"
class StackerReclaimerState;
class StackerReclaimer {
public:
    using AssociatedEntities = TypeList<Stacker, Reclaimer>;
        using AssociatedState = StackerReclaimerState;
    static const std::string ENTITY_NAME;
    class Id {
    public:
        using Entity = StackerReclaimer;
        TerminalId terminal;
        std::string name;
        Id();
        Id(TerminalId terminal, const std::string& name);
        Id(const Stacker::Id& src);
        Id(const Reclaimer::Id& src);        std::string nameForBinaryFile() const;
        template<class Archive>
        void serialize(Archive & archive);
    };
};

bool operator<(const StackerReclaimer::Id& a, const StackerReclaimer::Id& b);
bool operator==(const StackerReclaimer::Id& a, const StackerReclaimer::Id& b);
bool operator!=(const StackerReclaimer::Id& a, const StackerReclaimer::Id& b);

template<class Archive>
void StackerReclaimer::Id::serialize(Archive & archive) {
    archive(terminal, name);
}