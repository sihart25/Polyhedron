//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Shape.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Shape_h
#define Shape_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
#include "Group.h"
#include "Transform.h"
#include "Light.h"
#include "Material.h"
#include "Vectors.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Shape : public Object {

        friend class ShapePredicate;

    public:

        Shape() : _radius(1.0), _angle(0.0), _spin(0.0), _axis(0.0, 1.0, 0.0, 0.0),
            _theta(0.0), _phi(0.0), _psi(0.0), _rotateSpin(0.0),
            _numberOfVertices(0), _vertices(0), _transformVertices(0), _projectVertices(0) {}
        virtual ~Shape() {}
        static bool read(istream &in, string &token, Group &group);
        virtual void update(bool axis) { Group::shapes().push_back(this); }
        virtual void transform(Transform &transform);
        virtual void project(double fieldOfView);
        virtual void draw(const vector<Light *> &lights, bool solid) const = 0;

    protected:

        void centroid();
        virtual double depth() const = 0;
        virtual void write(ostream &out) const = 0;

        Transform _transform;
        Material _material;
        double _radius;
        double _angle;
        double _spin;
        Vectors _axis;
        double _theta;
        double _phi;
        double _psi;
        double _rotateSpin;
        int _numberOfVertices;
        Vectors **_vertices;
        Vectors **_transformVertices;
        Vectors **_projectVertices;
        Vectors _centroid;

    };

    //------------------------------------------------------------------------------
    // class definition

    class ShapePredicate {
    public:
        bool operator()(const Shape *a, const Shape *b) const { return a->depth() < b->depth(); }
    };

} // ComputerGraphics

#endif // Shape_h

//------------------------------------------------------------------------------
