//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Colour.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Colour_h
#define Colour_h

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

    const int R = 0;
    const int G = 1;
    const int B = 2;
    const int A = 3;
    const int COLOURS = 4;

    //------------------------------------------------------------------------------
    // class definition

    class Colour {

    public:

        Colour(double r = 0.0, double g = 0.0, double b = 0.0, double a = 1.0) {
            _c[R] = r;
            _c[G] = g;
            _c[B] = b;
            _c[A] = a;
        }
        double operator()(int i) const {
            return _c[i];
        }
        double &operator()(int i) {
            return _c[i];
        }
        GLfloat *toGLfloat(GLfloat f[]) const {
            f[R] = _c[R];
            f[G] = _c[G];
            f[B] = _c[B];
            f[A] = _c[A];
            return f;
        }
        // add two colours and copy into this colour
        Colour &add(const Colour &c1, const Colour &c2) {
            _c[R] = c1._c[R] + c2._c[R];
            _c[G] = c1._c[G] + c2._c[G];
            _c[B] = c1._c[B] + c2._c[B];
            _c[A] = c1._c[A] + c2._c[A];
            return *this;
        }
        Colour &operator+=(const Colour &c) {
            return add(*this, c);
        }
        Colour operator+(const Colour &c) const {
            return Colour().add(*this, c);
        }
        // subtract two colours and copy into this colour
        Colour &subtract(const Colour &c1, const Colour &c2) {
            _c[R] = c1._c[R] - c2._c[R];
            _c[G] = c1._c[G] - c2._c[G];
            _c[B] = c1._c[B] - c2._c[B];
            _c[A] = c1._c[A] - c2._c[A];
            return *this;
        }
        Colour &operator-=(const Colour &c) {
            return subtract(*this, c);
        }
        Colour operator-(const Colour &c) const {
            return Colour().subtract(*this, c);
        }
        // multiply two colours and copy into this colour
        Colour &multiply(const Colour &c1, const Colour &c2) {
            _c[R] = c1._c[R] * c2._c[R];
            _c[G] = c1._c[G] * c2._c[G];
            _c[B] = c1._c[B] * c2._c[B];
            _c[A] = c1._c[A] * c2._c[A];
            return *this;
        }
        Colour &operator*=(const Colour &c) {
            return multiply(*this, c);
        }
        Colour operator*(const Colour &c) const {
            return Colour().multiply(*this, c);
        }
        // multiply colour by scalar and copy into this colour
        Colour &multiply(const Colour &c, double s) {
            _c[R] = c._c[R] * s;
            _c[G] = c._c[G] * s;
            _c[B] = c._c[B] * s;
            _c[A] = c._c[A] * s;
            return *this;
        }
        Colour &operator*=(double s) {
            return multiply(*this, s);
        }
        Colour operator*(double s) const {
            return Colour().multiply(*this, s);
        }
        // divide colour by scalar and copy into this colour
        Colour &divide(const Colour &c, double s) {
            double rs = (fabs(s) < EPSILON) ? 0.0 : 1.0 / s;
            _c[R] = c._c[R] * rs;
            _c[G] = c._c[G] * rs;
            _c[B] = c._c[B] * rs;
            _c[A] = c._c[A] * rs;
            return *this;
        }
        Colour &operator/=(double s) {
            return divide(*this, s);
        }
        Colour operator/(double s) const {
            return Colour().divide(*this, s);
        }
        // negate this colour
        Colour &negate() {
            _c[R] = -_c[R];
            _c[G] = -_c[G];
            _c[B] = -_c[B];
            _c[A] = -_c[A];
            return *this;
        }
        // negative operator-
        Colour operator-() const {
            return Colour(-_c[R], -_c[G], -_c[B], _c[A]);
        }
        void readRGB(istream &in) {
            in >> _c[R] >> _c[G] >> _c[B];
            _c[A] = 1.0;
        }
        void readRGBA(istream &in) {
            in >> _c[R] >> _c[G] >> _c[B] >> _c[A];
        }
        friend Colour operator*(double s, const Colour &c) {
            return c * s;
        }
        friend istream &operator>>(istream &in, Colour &c) {
            c.read(in);
            return in;
        }
        friend ostream &operator<<(ostream &out, const Colour &c) {
            c.write(out);
            return out;
        }

    private:

        void read(istream &in) {
            readRGB(in);
        }
        void write(ostream &out) const {
            out << "(" << _c[R] << ", " << _c[G] << ", " << _c[B] << ", " << _c[A] << ")";
        }

        double _c[COLOURS];

    };

} // ComputerGraphics

#endif // Colour_h

//------------------------------------------------------------------------------
