#pragma once
template<typename State>
class StateTraits {
public:
    typedef typename State::AssociatedEvent AssociatedEvent;
    static State initializeFromEvent(const AssociatedEvent& src);
    static State generateNextState(const State& current, const AssociatedEvent& event);
};