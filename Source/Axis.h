//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Axis Assessment
// Axis.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Axis_h
#define Axis_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#include "Shape.h"
#include "Polyhedron.h"
#include "Group.h"
#include "Light.h"
#include "Colour.h"
#include "Vectors.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Axis : public Shape {

    public:

        Axis(const Polyhedron &polyhedron = Polyhedron(), int ident = X) {
            setup(polyhedron, ident);
        }
        ~Axis() { erase(); }
        virtual void update(bool axis) {
            if (axis) {
                Group::shapes().push_back(this);
            }
        }
        virtual void draw(const vector<Light *> &lights, bool solid) const;

    private:

        Axis(const Axis &axis);
        Axis &operator=(const Axis &axis);
        void setup(const Polyhedron &polyhedron, int ident);
        void erase();
        double depth() const { return _centroid(Z); }
        bool clip() const;
        void write(ostream &out) const { out << "Axis" << endl; }

        Colour _colour;

    };

} // ComputerGraphics

#endif // Axis_h

//------------------------------------------------------------------------------
