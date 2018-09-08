#pragma once
#include "Entity.h"
#include <map>
namespace visualiser {
    //TODO: write doxygen comments/etc
    //TODO: might be possible to optimise this by using aa template for the number of objects and states and allocating all memory on the stack (making it more contigious and facilitate processor caching, etc)
            //since it would only need to occurr once per event file loading
    //note that this is the non-engine-connected class and isn't aware of meshes or entity types (yet?)
	class VisualisationController {
    private:
        
        //todo: make this object or components thereof serialisable??        
        //todo: for mem caching speed it is possibly better to store keyframes (and possibly the associated hypercoords) contigously for all entities for a given point in time; but we'll worry about that later!
        //todo: discuss the fact that in the long run for our project/for the sim the memory caching properties will likely affect performance more heavily than the (generally minute) number of steps involved in our methods
        //todo: consider ways to control memory allocation at runtime to support this (e.g. a single vector containing the type and hypercoord of all entities for every key time point? )
        //todo: it may even be worthwhile to generate the cache of current frames/states each tick (each call to setTime/moveTime) 
        //todo: one way to encourage compiler optimisations is to use only standard layout and/or trivial/pod types (making them mem-copyable without additional logic or work)
        std::vector<Entity> data;

        //todo: decide whether or not we need to track a list of all keyframe times available? Does it affect performance not precompute the key positions for all objects where other objects need a keyframe?

        //conceptually, this stores the current keyframe (or, more specifically, the current pair of frames we are between) for active objects, for performance purposes.
        //this will only contain data for all objects currently needing animation; todo: it may be more performant to 
        std::map<std::size_t, std::pair<Entity::frame_iterator, Entity::frame_iterator>> watches;

        double worldTime;

        bool timeForward;

        //note that this speed is the playspeed as shown in the UI, and scales the impact of updateTime calls
        double speed;

        std::pair<Entity::frame_iterator, Entity::frame_iterator> findWatchIterators(const Entity& entity);

    public:
        //default to time=0, speed=1, SimData=new SimData(), currentframes = empty()
        VisualisationController();

        //use a MOVE operation to set the state data to simulate; may as well move since it won't need to be modified or externally touched again until the input event file changes
        //note, clears frames
        void setData(std::vector<Entity>&& data);

        bool isTimeForward();
        void setTimeFoward(bool timeToward);

        double getSpeed();
        void setSpeed(double speed);

        //gets the current world time
        double getTime();

        //snap to a given time
        void setTime(double time);

        //move time along according to the supply deltaTime
        //(note that the direction and speed of time-flow should be controlled via parameters supplied to other methods, not by modifying the timeDelta here)
        void moveTime(double deltaTime);

        //calculates and returns the hypercoord for the given entity at current worldTime
        //todo: throw an error if the entity doesn't exist?

        HyperCoord getState(std::size_t entityId);

        //todo: we may not use includeEntity/excludeEntity in future?
        //todo: throw errors or use returns to indicate whether or not the target exists in the SimData
        //adds an entity to the list to be animated/updated automatically with setTime/moveTime
        //these are basically just optimisation for entities that will be checked for this frame and the next that reduces the amount of processing for getting a new star=te after moveTime()
        void watchEntity(std::size_t entityId);
        void unwatchEntity(std::size_t entityId);

        void watchAll();
        void unwatchAll();

        //gets the type of a particular entity;
        Entity::Type getType(std::size_t entityId);

        //gets the number of entities that exist in the system
        std::size_t size();


    };
}