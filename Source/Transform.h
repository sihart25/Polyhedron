//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Transform.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Transform_h
#define Transform_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#include "Object.h"
#include "Vectors.h"
#include "Matrix.h"
#include "Constants.h"
#include "Group.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Transform : public Object {

    public:

        Transform() : _translate(0.0, 0.0, 0.0), _angle(0.0), _spin(0.0), _axis(0.0, 0.0, 1.0),
            _theta(0.0), _phi(0.0), _psi(0.0), _rotateSpin(0.0), _scale(1.0, 1.0, 1.0) {}
        static bool read(istream &in, string &token, Group &group);
        virtual void transform(Transform &transform);
        void transform();
        Transform &identity();
        Transform &scale(const Vectors &v);
        Transform &rotate(double theta, double phi, double psi);
        Transform &rotate(double angle, const Vectors &axis, bool unit = false);
        Transform &euler(double theta, double phi, double psi);
        Transform &translate(const Vectors &v);
        Transform &preMultiply(const Transform &transform);
        Transform &postMultiply(const Transform &transform);
        Transform &projection(double fieldOfView);
        const Matrix &forward() const { return _forward; }
        const Matrix &operator()() const { return _forward; }

    private:

        void write(ostream &out) const;
        Matrix _forward;
        Vectors _translate;
        double _angle;
        double _spin;
        Vectors _axis;
        double _theta;
        double _phi;
        double _psi;
        double _rotateSpin;
        Vectors _scale;

        //------------------------------------------------------------------------------
        // nested class definition

        class Angle {

        public:

            Angle(double deg = 0.0) {
                _rad = deg * PI / 180.0;
                _c = cos(_rad);
                _s = sin(_rad);
            }
            double c() const {return _c;}
            double s() const {return _s;}

        private:

            double _rad;
            double _c;
            double _s;

        };

    };

} // ComputerGraphics

#endif // Transform_h

//------------------------------------------------------------------------------
