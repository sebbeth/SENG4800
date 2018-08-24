#pragma once
#include <string>
#include "LoadPointEventType.h"

//forward declare a class to associate with the event
class LoadPointState;

class LoadPointEvent {
public:
    typedef LoadPointState AssociatedState;
    LoadPointEventType type;

    double amount;
    int cycleID;
    std::string loadPointID;
    std::string loadPointName;
    double time;

    bool hasAmount() const;
    bool hasCycleID() const;
    bool hasLoadPointID() const;
    bool hasLoadPointName() const;
    bool hasTime() const;

    template<class Archive>
    void serialize(Archive & archive);

    //STUB: INCLUDE A SPECIFIER FOR THE ID TYPE AND AN ID GETTER
};

template<class Archive>
void LoadPointEvent::serialize(Archive & archive) {
    archive(type, amount, cycleID, loadPointID, loadPointName, time);
}