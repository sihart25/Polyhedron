//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Light.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Light_h
#define Light_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Object.h"
#include "Group.h"
#include "Transform.h"
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

    class Light : public Object {

    public:

        Light() : _centre(0.0, 0.0, 0.0, 1.0), _ambient(0.0, 0.0, 0.0, 1.0),
                  _diffuse(0.0, 0.0, 0.0, 1.0), _specular(0.0, 0.0, 0.0, 1.0) {}
        static bool read(istream &in, string &token, Group &group);
        virtual void update(bool axis) { Group::lights().push_back(this); }
        virtual void transform(Transform &transform);
        const Colour &ambient() const { return _ambient; }
        const Colour &diffuse() const { return _diffuse; }
        const Colour &specular() const { return _specular; }
        const Vectors &position() const { return _position; }

    private:

        void write(ostream &out) const { out << "Light" << endl; }

        Colour _ambient;
        Colour _diffuse;
        Colour _specular;
        Vectors _centre;
        Vectors _position;

    };

} // ComputerGraphics

#endif // Light_h

//------------------------------------------------------------------------------
