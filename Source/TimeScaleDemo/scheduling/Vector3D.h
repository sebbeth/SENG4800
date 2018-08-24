#pragma once

#include <cmath>
#include <type_traits>
#define M_PI 3.14159265358979323846
namespace visualiser {
    class Vector3D {
    public:
        double x,y,z;
        Vector3D(double x, double y, double z);
        Vector3D(const Vector3D& src);

        // double angle() const;

        double length() const;

        //optionally choose the precision with which to normalise
        Vector3D normalized() const;

        Vector3D& operator=(const Vector3D& src);
        Vector3D& operator+=(const Vector3D& src);
        Vector3D& operator-=(const Vector3D& src);
        Vector3D& operator*=(double scalar);
        Vector3D& operator/=(double scalar);

        // static Vector3D fromPolar(double angle, double length);

        static double dot(const Vector3D& a, const Vector3D& b);
    };

    Vector3D abs(const Vector3D& a);
    Vector3D operator*(const Vector3D& a, double scalar);
    Vector3D operator*(double scalar, const Vector3D& a);
    Vector3D operator/(const Vector3D& a, double scalar);
    Vector3D operator+(const Vector3D& a, const Vector3D& b);
    Vector3D operator-(const Vector3D& a, const Vector3D& b);
    Vector3D operator-(const Vector3D& a);
    bool operator==(const Vector3D& a, const Vector3D& b);
    bool operator!=(const Vector3D& a, const Vector3D& b);
    Vector3D round(const Vector3D &a);
    Vector3D floor(const Vector3D& a);
    Vector3D ceil(const Vector3D& a);
}