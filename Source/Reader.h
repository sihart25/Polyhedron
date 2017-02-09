//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Reader.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Reader_h
#define Reader_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Group.h"
#include "Screen.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // constants

    const char OPENING_BRACE[] = "{";
    const char CLOSING_BRACE[] = "}";
    const char OPENING_COMMENT[] = "/*";
    const char CLOSING_COMMENT[] = "*/";

    //------------------------------------------------------------------------------
    // class definition

    class Reader {

    public:

        static void read(const string &filename, Group &group, Screen &screen);
        static bool comment(istream &in, string &token);

    private:

    };

} // ComputerGraphics

#endif // Reader_h

//------------------------------------------------------------------------------
