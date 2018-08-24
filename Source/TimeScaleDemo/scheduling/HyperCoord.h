#pragma once
#include "Vector3D.h"
namespace visualiser {
    /**
     * A coordinate consisting of position, orientation and scale, each identifying a key frame/state for an object in the simulation
     **/
    class HyperCoord {
    public:

        //notice the PUBLIC member variables; it's a 
        Vector3D position;
        Vector3D rotation;
        Vector3D scale;

        //todo: consider adding an explicit default constructor, etc, to make this POD? (and doing the same for Vector3D)
        HyperCoord(Vector3D position, Vector3D rotation, Vector3D scale);
    };

    HyperCoord operator+(const HyperCoord& a, const HyperCoord& b);
    HyperCoord operator-(const HyperCoord& a, const HyperCoord& b);
    HyperCoord operator*(const HyperCoord& a, double scalar);
    HyperCoord operator*(double scalar, const HyperCoord& a);
}