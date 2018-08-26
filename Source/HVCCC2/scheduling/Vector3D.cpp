#include "Vector3D.h"
namespace visualiser {
    double Vector3D::dot(const Vector3D& a, const Vector3D& b) {
        return a.x*b.x + a.y*b.y + a.z*b.z;
    }

    // Vector3D cross(const Vector3D& a, const Vector3D& b) {
    //     return Vector3D(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
    // }

    Vector3D::Vector3D(double x, double y, double z): x(x), y(y), z(z) {}


    Vector3D::Vector3D(const Vector3D& src): x(src.x), y(src.y), z(src.z) {}

    // double Vector3D::angle() const {
    //     return std::atan2((double)y, (double)x, ());
    // }

    // Vector3D Vector3D::fromPolar(double radians, double length) {
    //     return Vector3D(length*std::cos(radians), length*std::sin(radians));
    // }


    double Vector3D::length() const {
        return std::sqrt(dot(*this, *this));
    }

    Vector3D Vector3D::normalized() const {
        double len = length();
        return len != 0 ? (*this)/len : Vector3D(0,0,0);
    }

    Vector3D& Vector3D::operator=(const Vector3D &src) {
        x = src.x;
        y = src.y;
        return *this;
    }

    Vector3D& Vector3D::operator+=(const Vector3D &src) {
        x += src.x;
        y += src.y;
        return *this;
    }

    Vector3D& Vector3D::operator*=(double scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector3D& Vector3D::operator/=(double scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    Vector3D& Vector3D::operator-=(const Vector3D &src) {
        x -= src.x;
        y -= src.y;
        return *this;
    }

    Vector3D abs(const Vector3D& a) {
        return Vector3D(std::abs(a.x), std::abs(a.y), std::abs(a.z));
    }

    Vector3D operator*(const Vector3D& a, double scalar) {
        return Vector3D(a.x*scalar, a.y*scalar, a.z*scalar);
    }

    Vector3D operator*(double scalar, const Vector3D& a) {
        return Vector3D(a.x*scalar, a.y*scalar, a.z*scalar);
    }

    Vector3D operator/(const Vector3D& a, double scalar) {
        return Vector3D(a.x/scalar, a.y/scalar, a.z/scalar);
    }

    Vector3D operator+(const Vector3D& a, const Vector3D& b) {
        return Vector3D(a.x+b.x, a.y+b.y, a.z+b.z);
    }

    Vector3D operator-(const Vector3D& a, const Vector3D& b) {
        return Vector3D(a.x-b.x, a.y-b.y, a.z-b.z);
    }

    Vector3D operator-(const Vector3D& a) {
        return Vector3D(-a.x, -a.y, -a.z);
    }

    bool operator==(const Vector3D& a, const Vector3D& b) {
        return a.x==b.x && a.y==b.y && a.z==b.z;
    }

    bool operator!=(const Vector3D& a, const Vector3D& b) {
        return !(a==b);
    }

    Vector3D round(const Vector3D &a) {
        return Vector3D(std::round(a.x), std::round(a.y), std::round(a.z));
    }

    Vector3D floor(const Vector3D& a) {
        return Vector3D(std::floor(a.x), std::floor(a.y), std::floor(a.z));
    }

    Vector3D ceil(const Vector3D& a) {
        return Vector3D(std::ceil(a.x), std::ceil(a.y), std::ceil(a.z));
    }
}