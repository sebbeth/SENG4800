#include "HyperCoord.h"
namespace visualiser {
    HyperCoord::HyperCoord(Vector3D position, Vector3D rotation, Vector3D scale): position(position), rotation(rotation), scale(scale) {}
    HyperCoord operator+(const HyperCoord& a, const HyperCoord& b) {
        return HyperCoord(a.position+b.position, a.rotation+b.rotation, a.scale+b.scale);
    }
    
    HyperCoord operator-(const HyperCoord& a, const HyperCoord& b) {
        return HyperCoord(a.position-b.position, a.rotation-b.rotation, a.scale-b.scale);
    }

    HyperCoord operator*(const HyperCoord& a, double scalar) {
        return HyperCoord(a.position*scalar, a.rotation*scalar, a.scale*scalar);
    }
    HyperCoord operator*(double scalar, const HyperCoord& a) {
        return HyperCoord(a.position*scalar, a.rotation*scalar, a.scale*scalar);
    }
}