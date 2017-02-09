//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Object.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Object_h
#define Object_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // forward declarations

    class Group;
    class Transform;

    //------------------------------------------------------------------------------
    // class definition

    class Object {

    public:

        virtual ~Object() {}
        static bool read(istream &in, string &token, Group &group);
        virtual void update(bool axis) {}
        virtual void transform(Transform &transform) = 0;
        friend ostream &operator<<(ostream &out, const Object &object) {
            object.write(out);
            return out;
        }

    protected:

        virtual void write(ostream &out) const = 0;

    };

} // ComputerGraphics

#endif // Object_h

//------------------------------------------------------------------------------
