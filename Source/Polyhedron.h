//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Polyhedron.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Polyhedron_h
#define Polyhedron_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#include "Shape.h"
#include "Face.h"
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
    // forward declarations

    class Axis;

    //------------------------------------------------------------------------------
    // class definition

    class Polyhedron : public Shape {

        friend class Axis;

    public:

        Polyhedron() : _numberOfFaces(0), _faces(0) {}
        ~Polyhedron() { erase(); }
        static bool read(istream &in, string &token, Group &group);
        virtual void draw(const vector<Light *> &lights, bool solid) const;

    private:

        Polyhedron(const Polyhedron &polyhedron);
        Polyhedron &operator=(const Polyhedron &polyhedron);
        void erase();
        void readFile(istream &in);
        double depth() const { return _centroid(Z); }
        Vectors centroid(int face) const;
        Vectors normal(int face) const;
        bool cull(int face) const;
        bool clip(int face) const;
        Colour light(const vector<Light *> &lights, int face) const;
        void draw(const vector<Light *> &lights, bool solid, int face) const;
        void write(ostream &out) const { out << "Polyhedron" << endl; }

        int _numberOfFaces;
        Face **_faces;
        string _filename;

    };

} // ComputerGraphics

#endif // Polyhedron_h

//------------------------------------------------------------------------------
