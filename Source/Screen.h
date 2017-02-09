//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Screen.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Screen_h
#define Screen_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Constants.h"
#include "Colour.h"
#include "Camera.h"
#include "Vectors.h"
#include "Transform.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Screen {

    public:

        Screen(int width = WIDTH, int height = HEIGHT) : _width(width), _height(height) {}
        ~Screen() { erase(); }
        void clear();
        bool read(istream &in, string &token);
        void write(const string &filename);
        void resize(int width, int height);
        int width() const { return _width; }
        int height() const { return _height; }
        double aspectRatio() const { return (double)_width / (double)(_height ? _height : 1); }
        const Colour &background() const { return _background; }
        double fieldOfView() const { return Camera::fieldOfView(); }
        void next() { Camera::next(_cameras); }
        void move(const Vectors &rotation, double distance, const Vectors &centre) {
            Camera::move(rotation, distance, centre);
        }
        void transform(Transform &transform) const { Camera::transform(transform); }

    private:

        Screen(const Screen &screen);
        Screen &operator=(const Screen &screen);
        void erase();

        int _width;
        int _height;
        Colour _background;
        vector<Camera *> _cameras;

    };

} // ComputerGraphics

#endif // Screen_h

//------------------------------------------------------------------------------
