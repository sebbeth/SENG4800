#include "Entity.h"
namespace visualiser {
    Entity::Entity(std::size_t id, Type type): id(id), type(type) {}

    std::size_t Entity::getId() {
        return id;
    }

    void Entity::setType(Type type) {
        this->type = type;
    }

    Entity::Type Entity::getType() const {
        return type;
    }

    void Entity::clear() {
        states.clear();
        frames.clear();
    }

    void Entity::addState(const HyperCoord& state) {
        states.push_back(state);
    }

    void Entity::addFrame(const KeyFrame& frame) {
        frames.push_back(frame);
    }

    const HyperCoord& Entity::getState(std::size_t stateId) const {
        return states[stateId];
    }

    const KeyFrame& Entity::getFrame(std::size_t frameId) const {
        return frames[frameId];
    }

    std::size_t Entity::getIndexOfMostRecentFrame(double time) const {
        std::size_t result = 0;
        std::size_t next_result = result+1;
        while(next_result < frames.size() && frames[next_result].time < time) {
            result = next_result;
            next_result += 1;
        }
        return result;
    }

    Entity::frame_iterator Entity::getIteratorToMostRecentFrame(double time) const {
        frame_iterator result = frames.begin();
        frame_iterator next_result = result+1;
        while(next_result != frames.end() && next_result->time < time) {
            result = next_result;
            next_result = next_result+1;
        }
        return result;
    }

    
    HyperCoord Entity::interpolate(const HyperCoord& a, const HyperCoord& b, double scale) {
        return a+((b-a)*scale);
    }
}