//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Scene.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Scene_h
#define Scene_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Colour.h"
#include "Vectors.h"
#include "Screen.h"
#include "Group.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Scene {

    public:

        void read(const string &filename);
        void draw(bool axis, bool solid);
        void write(const string &filename) { _screen.write(filename); }
        double width() const { return _screen.width(); }
        double height() const { return _screen.height(); }
        void resize(int width, int height) { _screen.resize(width, height); }
        const Colour &background() const { return _screen.background(); }
        void next() { _screen.next(); }
        void move(const Vectors &rotation, double distance, const Vectors &centre) {
            _screen.move(rotation, distance, centre);
        }

    private:

        Screen _screen;
        Group _group;

    };

} // ComputerGraphics

#endif // Scene_h

//------------------------------------------------------------------------------
