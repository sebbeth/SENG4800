#pragma once
#include <vector>
#include "HyperCoord.h"
#include "KeyFrame.h"
namespace visualiser {        
        //todo: should this just be implemented as an extension of vector<hypercoord>? or, should they be public, with the frame list having a class extension that supports indexing by time as well as number?
        //probably not;
    class Entity {
    public:
        enum Type {
			DEMO_CUBE,
            COAL_PILE,
            STACKER,
            RECLAIMER,
            TRAIN
        };

        typedef std::vector<HyperCoord>::const_iterator state_iterator;
        typedef std::vector<KeyFrame>::const_iterator frame_iterator;
    private:
        std::size_t id;
        //the type identifies which mesh will be required, etc
        Type type;
        //conceptually this is: map<stateid, coord>
        std::vector<HyperCoord> states;

        //conceptually this is: map<time, stateid>
        //this will contain all keyframes needed for the current event file
        std::vector<KeyFrame> frames;

    public:
        Entity(std::size_t id, Type type);

        std::size_t getId();

        void setType(Type type);
        Type getType() const;

        //todo: does next an index operator for states? probably not a big deal for now..

        void clear();
        //adds a state to the list of states availble for a given entity
        void addState(const HyperCoord& state);

        //adds a keyframe to the list of frames available for a given entity
        //note that stateIds are per-entity?
        void addFrame(const KeyFrame& frame);

        //todo: how do I know which state set?? (we'd be in the simulator when we assign this normally??)
        const HyperCoord& getState(std::size_t stateId) const;

        //gets the frame by index; used mainly for efficiency
        const KeyFrame& getFrame(std::size_t frameId) const;

        //todo: if we publically expose the underlying data then only this last keyframe method is required?
                //but is that bad practice?

        state_iterator stateBegin() const;
        state_iterator stateEnd() const;

        frame_iterator frameBegin() const;
        frame_iterator frameEnd() const;

        //searches for the frame that would have started most recently at the given time
        //returns the index of the first frame if no frame started /at or before/ the given time
        std::size_t getIndexOfMostRecentFrame(double time) const;

        //searches for the frame that would have started most recently at the given time
        //returns an iterator to the first frame if no frame started /at or before/ the given time
        frame_iterator getIteratorToMostRecentFrame(double time) const;

                //todo: we'll initially only animate between discrete points, but the interpolation may need to be replaced with some kind of curve/spline
        static HyperCoord interpolate(const HyperCoord& a, const HyperCoord& b, double scale);
        

        //todo: do we need remove/set/update things as well in the long term?

    };
}