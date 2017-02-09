//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Group.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Group_h
#define Group_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // forward declarations

    class Transform;
    class Light;
    class Shape;

    //------------------------------------------------------------------------------
    // class definition

    class Group : public Object {

    public:

        Group() {}
        ~Group() { erase(); }
        void clear() { erase(); }
        static bool read(istream &in, string &token, Group &group);
        virtual void update(bool axis);
        virtual void transform(Transform &transform);
        void project(double fieldOfView);
        void draw(bool solid) const;
        void push_back(Object *object) { _objects.push_back(object); }
        static vector<Light *> &lights() { return _lights; }
        static vector<Shape *> &shapes() { return _shapes; }

    private:

        Group(const Group &group);
        Group &operator=(const Group &group);
        void erase();
        void write(ostream &out) const;

        vector<Object *> _objects;
        static vector<Light *> _lights;
        static vector<Shape *> _shapes;

    };

} // ComputerGraphics

#endif // Group_h

//------------------------------------------------------------------------------
