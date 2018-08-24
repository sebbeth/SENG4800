#pragma once
#include <cstddef>
namespace visualiser {
    //note: yes it's a struct;
    //it's only intended for transport/storage in containers
    //it's perfectly appropriate design 
    struct KeyFrame {
        double time;
        std::size_t stateId;  //todo: we could store a reference or reference_wrapper here but would it be worth it?
    };
}