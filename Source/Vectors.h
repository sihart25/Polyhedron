//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Vectors.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Vectors_h
#define Vectors_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#include <gl/glut.h>
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // constants

    const int X = 0;
    const int Y = 1;
    const int Z = 2;
    const int W = 3;
    const int DIM3 = 3;
    const int DIM4 = 4;
    const int DIM = DIM4;

    //------------------------------------------------------------------------------
    // class definition

    class Vectors {

    public:

        Vectors(double x = 0.0, double y = 0.0, double z = 0.0, double w = 0.0) {
            _v[X] = x;
            _v[Y] = y;
            _v[Z] = z;
            _v[W] = w;
        }
        double operator()(int i) const {
            return _v[i];
        }
        double &operator()(int i) {
            return _v[i];
        }
        GLfloat *toGLfloat(GLfloat f[]) const {
            f[X] = _v[X];
            f[Y] = _v[Y];
            f[Z] = _v[Z];
            f[W] = _v[W];
            return f;
        }
        // add two vectors and copy into this vector
        Vectors &add(const Vectors &v1, const Vectors &v2) {
            _v[X] = v1._v[X] + v2._v[X];
            _v[Y] = v1._v[Y] + v2._v[Y];
            _v[Z] = v1._v[Z] + v2._v[Z];
            _v[W] = v1._v[W] + v2._v[W];
            return *this;
        }
        Vectors &operator+=(const Vectors &v) {
            return add(*this, v);
        }
        Vectors operator+(const Vectors &v) const {
            return Vectors().add(*this, v);
        }
        // subtract two vectors and copy into this vector
        Vectors &subtract(const Vectors &v1, const Vectors &v2) {
            _v[X] = v1._v[X] - v2._v[X];
            _v[Y] = v1._v[Y] - v2._v[Y];
            _v[Z] = v1._v[Z] - v2._v[Z];
            _v[W] = v1._v[W] - v2._v[W];
            return *this;
        }
        Vectors &operator-=(const Vectors &v) {
            return subtract(*this, v);
        }
        Vectors operator-(const Vectors &v) const {
            return Vectors().subtract(*this, v);
        }
        // multiply two vectors and copy into this vector
        Vectors &multiply(const Vectors &v1, const Vectors &v2) {
            _v[X] = v1._v[X] * v2._v[X];
            _v[Y] = v1._v[Y] * v2._v[Y];
            _v[Z] = v1._v[Z] * v2._v[Z];
            _v[W] = v1._v[W] * v2._v[W];
            return *this;
        }
        Vectors &operator*=(const Vectors &v) {
            return multiply(*this, v);
        }
        Vectors operator*(const Vectors &v) const {
            return Vectors().multiply(*this, v);
        }
        // multiply vector by scalar and copy into this vector
        Vectors &multiply(const Vectors &v, double s) {
            _v[X] = v._v[X] * s;
            _v[Y] = v._v[Y] * s;
            _v[Z] = v._v[Z] * s;
            _v[W] = v._v[W];
            return *this;
        }
        Vectors &operator*=(double s) {
            return multiply(*this, s);
        }
        Vectors operator*(double s) const {
            return Vectors().multiply(*this, s);
        }
        // divide vector by scalar and copy into this vector
        Vectors &divide(const Vectors &v, double s) {
            double rs = (fabs(s) < EPSILON) ? 0.0 : 1.0 / s;
            _v[X] = v._v[X] * rs;
            _v[Y] = v._v[Y] * rs;
            _v[Z] = v._v[Z] * rs;
            _v[W] = v._v[W];
            return *this;
        }
        Vectors &operator/=(double s) {
            return divide(*this, s);
        }
        Vectors operator/(double s) const {
            return Vectors().divide(*this, s);
        }
        // cross product between this vector and another vector
        Vectors cross(const Vectors &v) const {
            double vx = _v[Y] * v._v[Z] - _v[Z] * v._v[Y];
            double vy = _v[Z] * v._v[X] - _v[X] * v._v[Z];
            double vz = _v[X] * v._v[Y] - _v[Y] * v._v[X];
            double vw = 0.0;
            return Vectors(vx, vy, vz, vw);
        }
        // dot product between this vector and another vector
        double dot(const Vectors &v) const {
            return _v[X] * v._v[X] + _v[Y] * v._v[Y] + _v[Z] * v._v[Z];
        }
        // distance from this vector to another vector
        double distance(const Vectors &v) const {
            return (v - *this).magnitude();
        }
        // magnitude of this vector
        double magnitude() const {
            return sqrt(dot(*this));
        }
        // normalize this vector
        Vectors &normalize() {
            return *this /= magnitude();
        }
        // unit vector of this vector
        Vectors unit() const {
            return *this / magnitude();
        }
        // negate this vector
        Vectors &negate() {
            _v[X] = -_v[X];
            _v[Y] = -_v[Y];
            _v[Z] = -_v[Z];
            return *this;
        }
        // negative operator-
        Vectors operator-() const {
            return Vectors(-_v[X], -_v[Y], -_v[Z], _v[W]);
        }
        // homogenize this vector
        Vectors &homogenize() {
            return *this /= _v[W];
        }
        void setPosition(double x, double y, double z) {
            _v[X] = x;
            _v[Y] = y;
            _v[Z] = z;
            _v[W] = 1.0;
        }
        void setDirection(double x, double y, double z) {
            _v[X] = x;
            _v[Y] = y;
            _v[Z] = z;
            _v[W] = 0.0;
        }
        void set(double x, double y, double z, double w) {
            _v[X] = x;
            _v[Y] = y;
            _v[Z] = z;
            _v[W] = w;
        }
        // stream in to this vector
        void readPosition(istream &in) {
            in >> _v[X] >> _v[Y] >> _v[Z];
            _v[W] = 1.0;
        }
        // stream in to this vector
        void readDirection(istream &in) {
            in >> _v[X] >> _v[Y] >> _v[Z];
            _v[W] = 0.0;
        }
        friend Vectors operator*(double s, const Vectors &v) {
            return v * s;
        }
        friend istream &operator>>(istream &in, Vectors &v) {
            v.read(in);
            return in;
        }
        friend ostream &operator<<(ostream &out, const Vectors &v) {
            v.write3(out);
            return out;
        }

    protected:

        void read(istream &in) {
            in >> _v[X] >> _v[Y] >> _v[Z] >> _v[W];
        }
        void write3(ostream &out) const {
            out << "Vector = " << "(" << _v[X] << ", " << _v[Y] << ", " << _v[Z] << ")";
        }
        void write4(ostream &out) const {
            out << "Vector = " << "(" << _v[X] << ", " << _v[Y] << ", " << _v[Z] <<
                ", " << _v[W] << ")";
        }

        double _v[DIM];

    };

} // ComputerGraphics

#endif // Vectors_h

//------------------------------------------------------------------------------
