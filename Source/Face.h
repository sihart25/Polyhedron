//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Face.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Face_h
#define Face_h

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
    // class definition

    class Face {

    public:

        Face() : _numberOfIndices(0), _indices(0) {}
        ~Face() { erase(); }
        friend istream &operator>>(istream &in, Face &face) {
            face.read(in);
            return in;
        }
        friend ostream &operator<<(ostream &out, const Face &face) {
            face.write(out);
            return out;
        }
        int numberOfIndices() const { return _numberOfIndices; }
        const int *indices() const { return _indices; }

    private:

        Face(const Face &face);
        Face &operator=(const Face &face);
        void erase();
        void read(istream &in);
        void write(ostream &out) const;

        int _numberOfIndices;
        int *_indices;

    };

} // ComputerGraphics

#endif // Face_h

//------------------------------------------------------------------------------
