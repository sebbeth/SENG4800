#include "VisualisationController.h"
#include <algorithm>
namespace visualiser {
    VisualisationController::VisualisationController(): data(), watches(), worldTime(0), timeForward(true), speed(1) {}

    std::pair<Entity::frame_iterator, Entity::frame_iterator> VisualisationController::findWatchIterators(const Entity& entity) {
        auto mostRecentIt = entity.getIteratorToMostRecentFrame(worldTime);
        auto nextIt = mostRecentIt == entity.frameEnd() ? mostRecentIt : ++mostRecentIt;
        if(nextIt == entity.frameEnd()) {
            nextIt = mostRecentIt;
        }
        return std::make_pair(mostRecentIt, nextIt);
    }

    void VisualisationController::setData(std::vector<Entity>&& data) {
        this->data = data;
    }

    bool VisualisationController::isTimeForward() {
        return timeForward;
    }   

    void VisualisationController::setTimeFoward(bool timeForward) {
        this->timeForward = timeForward;
    }

    double VisualisationController::getSpeed() {
        return speed;
    }

    void VisualisationController::setSpeed(double speed) {
        this->speed = speed;
    }

    double VisualisationController::getTime() {
        return worldTime;
    }

    void VisualisationController::setTime(double time) {
        worldTime = time;
        for(auto watchIt = watches.begin(); watchIt != watches.end(); ++watchIt) {
            watchIt->second = findWatchIterators(data[watchIt->first]);
        }
    }

    void VisualisationController::moveTime(double deltaTime) {
        worldTime += deltaTime;
        if(timeForward) {
            //this is optimised for forward play
            for(auto watchIt = watches.begin(); watchIt != watches.end(); ++watchIt) {
                Entity& eachEntity = data[watchIt->first];
                std::pair<Entity::frame_iterator, Entity::frame_iterator>& iterators = watchIt->second;
                auto nextIt = iterators.second;
                while(iterators.second->time < worldTime) {
                    ++nextIt;
                    if(nextIt != eachEntity.frameEnd()) {
                        iterators.first = iterators.second;
                        iterators.second = nextIt;   
                    } else {
                        break;
                    }
                }
                //remember to set everything to the end if we reach it
                if(iterators.second->time < worldTime) {
                    iterators.first = iterators.second;
                }
            }
        } else {
            //this is optimised for backward play
            for(auto watchIt = watches.begin(); watchIt != watches.end(); ++watchIt) {
                Entity& eachEntity = data[watchIt->first];
                std::pair<Entity::frame_iterator, Entity::frame_iterator>& iterators = watchIt->second;
                auto nextIt = iterators.first;
                while(iterators.first->time > worldTime) {
                    if(nextIt != eachEntity.frameBegin()) {
                        --nextIt;
                    } else {
                        break;
                    }
                    iterators.second = iterators.first;
                    iterators.first = nextIt;
                }
                //remember to set everything to the end if we reach it
                if(iterators.first->time > worldTime) {
                    iterators.second = iterators.first;
                }
            }
        }
    }


    //todo: support non-linear interpolation?
    HyperCoord VisualisationController::getState(std::size_t entityId) {
        auto it = watches.find(entityId);
        Entity& theEntity = data[it->first];
        std::pair<Entity::frame_iterator, Entity::frame_iterator> targets = it != watches.end() ? it->second : findWatchIterators(theEntity);

        //todo: maxDist is cachable along with the rest of the watch data? so is the difference vector for interpolation, and/or the states, depending on the interpolation method
        double maxDist = targets.second->time - targets.first->time;

        //we have to limit the target time in case the worldTime is beyond the current frame
        double targetTime = std::max(targets.first->time, std::min(targets.second->time, worldTime));
        //determine the scale as a 
        double scale = maxDist > 0 ? (targetTime - targets.first->time)/maxDist : 0;

        //now apply the interpolation
        return Entity::interpolate(theEntity.getState(targets.first->stateId), theEntity.getState(targets.second->stateId), scale);
    }

    void VisualisationController::watchEntity(std::size_t entityId) {
        watches.insert_or_assign(entityId, findWatchIterators(data[entityId]));
    }

    void VisualisationController::unwatchEntity(std::size_t entityId) {
        watches.erase(entityId);
    }

    void VisualisationController::watchAll() {
        for(Entity& eachEntity : data) {
            watches.insert_or_assign(eachEntity.getId(), findWatchIterators(eachEntity));
        }
    }

    void VisualisationController::unwatchAll() {
        watches.clear();
    }

    Entity::Type VisualisationController::getType(std::size_t entityId) {
        return data[entityId].getType();
    }

    std::size_t VisualisationController::size() {
        return data.size();
    }
}