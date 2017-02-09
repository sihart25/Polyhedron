//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Control.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Control_h
#define Control_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Scene.h"
#include "Transform.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Control {

    public:

        Control() : _position(true), _rotation(true), _motionX(0), _motionY(0),
            _axis(true), _solid(true) {}
        ~Control() { cout << "Control object successfully destructed" << endl; }
        void initialize(int argc, char **argv);
        void menu() const;
        void read();
        void display();
        void reshape(int width, int height);
        void keyboard(unsigned char key, int x, int y);
        void special(int key, int x, int y);
        void mouse(int button, int state, int x, int y);
        void motion(int x, int y);
        void idle();

    private:

        Scene _scene;
        string _filenameIn;
        string _filenameOut;
        bool _position;
        bool _rotation;
        int _motionX;
        int _motionY;
        bool _axis;
        bool _solid;

    };

} // ComputerGraphics

#endif // Control_h

//------------------------------------------------------------------------------
