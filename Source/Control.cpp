//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Control.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <ctime>
#include <gl/glut.h>
#pragma hdrstop
#include "Control.h"
#include "Constants.h"
#include "Polyhedron.h"
#include "Reader.h"
#include "Writer.h"
#include "Scene.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// initialize
void Control::initialize(int argc, char **argv) {
    if (argc != 3) {
        _filenameIn = string("..\\Data\\Polyhedron.txt");
        _filenameOut = string("..\\Data\\Polyhedron.bmp");
    }
    else {
        _filenameIn = argv[1];
        _filenameOut = argv[2];
    }
    read();
}

//------------------------------------------------------------------------------
// menu
void Control::menu() const {
    cout << "Press <escape>    to exit program" << endl;
    cout << "Press <f1>        to toggle axis display" << endl;
    cout << "Press <f2>        to toggle solid and wire-frame mode" << endl;
    cout << "Press <f9>        to write bitmap file" << endl;
    cout << "Press <f10>       to select camera rotation and distance" << endl;
    cout << "Press <f11>       to select camera centre" << endl;
    cout << "Press <f12>       to change to next camera" << endl;
    cout << "Press <space>     to read scene file" << endl;
    cout << "Press <left>      to adjust camera yaw rotation or x centre" << endl;
    cout << "Press <right>     to adjust camera yaw rotation or x centre" << endl;
    cout << "Press <down>      to adjust camera pitch rotation or y centre" << endl;
    cout << "Press <up>        to adjust camera pitch rotation or y centre" << endl;
    cout << "Press <pagedown>  to adjust camera roll rotation or z centre" << endl;
    cout << "Press <pageup>    to adjust camera roll rotation or z centre" << endl;
    cout << "Press <end>       to adjust camera distance" << endl;
    cout << "Press <home>      to adjust camera distance" << endl;
    cout << "Press left mouse button to adjust camera yaw and pitch rotation" << endl;
    cout << "Press right mouse button to adjust camera roll rotation" << endl;
}

//------------------------------------------------------------------------------
// read
void Control::read() {
    _scene.read(_filenameIn);
    glutReshapeWindow(_scene.width(), _scene.height());
    glViewport(0, 0, _scene.width(), _scene.height());
}

//------------------------------------------------------------------------------
// display
void Control::display() {
    _scene.draw(_axis, _solid);
    glutSwapBuffers();
}

//------------------------------------------------------------------------------
// reshape
void Control::reshape(int width, int height) {
    _scene.resize(width, height);
    glViewport(0, 0, width, height);
}

//------------------------------------------------------------------------------
// keyboard
void Control::keyboard(unsigned char key, int /*x*/, int /*y*/) {
    switch (key) {
        case ' ': {
            read();
            break;
        }
        case 0x0D: {
            _scene.next();
            break;
        }
        case 0x1B: {
            glutDestroyWindow(glutGetWindow());
            delete this;
            exit(0);
        }
    }
}

//------------------------------------------------------------------------------
// special
void Control::special(int key, int /*x*/, int /*y*/) {
    const double ANGLE_INCREMENT = 5.0;
    const double POSITION_INCREMENT = 0.05;
    switch (key) {
        case GLUT_KEY_F1: {
            _axis = !_axis;
            break;
        }
        case GLUT_KEY_F2: {
            _solid = !_solid;
            break;
        }
        case GLUT_KEY_F9: {
            _scene.write(_filenameOut);
            break;
        }
        case GLUT_KEY_F10: {
            _position = true;
            break;
        }
        case GLUT_KEY_F11: {
            _position = false;
            break;
        }
        case GLUT_KEY_F12: {
            _scene.next();
            break;
        }
        case GLUT_KEY_END: {
            _scene.move(Vectors(), -POSITION_INCREMENT, Vectors());
            break;
        }
        case GLUT_KEY_HOME: {
            _scene.move(Vectors(), POSITION_INCREMENT, Vectors());
            break;
        }
        default: {
            if (_position) {
                switch (key) {
                    case GLUT_KEY_LEFT: {
                        _scene.move(Vectors(-ANGLE_INCREMENT, 0.0, 0.0), 0.0, Vectors());
                        break;
                    }
                    case GLUT_KEY_RIGHT: {
                        _scene.move(Vectors(ANGLE_INCREMENT, 0.0, 0.0), 0.0, Vectors());
                        break;
                    }
                    case GLUT_KEY_DOWN: {
                        _scene.move(Vectors(0.0, ANGLE_INCREMENT, 0.0), 0.0, Vectors());
                        break;
                    }
                    case GLUT_KEY_UP: {
                        _scene.move(Vectors(0.0, -ANGLE_INCREMENT, 0.0), 0.0, Vectors());
                        break;
                    }
                    case GLUT_KEY_PAGE_DOWN: {
                        _scene.move(Vectors(0.0, 0.0, -ANGLE_INCREMENT), 0.0, Vectors());
                        break;
                    }
                    case GLUT_KEY_PAGE_UP: {
                        _scene.move(Vectors(0.0, 0.0, ANGLE_INCREMENT), 0.0, Vectors());
                        break;
                    }
                }
            }
            else {
                switch (key) {
                    case GLUT_KEY_LEFT: {
                        _scene.move(Vectors(), 0.0, Vectors(-POSITION_INCREMENT, 0.0, 0.0));
                        break;
                    }
                    case GLUT_KEY_RIGHT: {
                        _scene.move(Vectors(), 0.0, Vectors(POSITION_INCREMENT, 0.0, 0.0));
                        break;
                    }
                    case GLUT_KEY_DOWN: {
                        _scene.move(Vectors(), 0.0, Vectors(0.0, -POSITION_INCREMENT, 0.0));
                        break;
                    }
                    case GLUT_KEY_UP: {
                        _scene.move(Vectors(), 0.0, Vectors(0.0, POSITION_INCREMENT, 0.0));
                        break;
                    }
                    case GLUT_KEY_PAGE_DOWN: {
                        _scene.move(Vectors(), 0.0, Vectors(0.0, 0.0, -POSITION_INCREMENT));
                        break;
                    }
                    case GLUT_KEY_PAGE_UP: {
                        _scene.move(Vectors(), 0.0, Vectors(0.0, 0.0, POSITION_INCREMENT));
                        break;
                    }
                }
            }
        }
    }
}

//------------------------------------------------------------------------------
// mouse
void Control::mouse(int button, int state, int x, int y) {
    _motionX = x;
    _motionY = y;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        _rotation = true;
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        _rotation = false;
    }
}

//------------------------------------------------------------------------------
// motion
void Control::motion(int x, int y) {
    const double ANGLE_INCREMENT = 1.0;
    if (_rotation) {
        _scene.move(Vectors((x - _motionX) * ANGLE_INCREMENT, -(_motionY - y) * ANGLE_INCREMENT, 0.0),
            0.0, Vectors());
    }
    else {
        _scene.move(Vectors(0.0, 0.0, ((x - _motionX) + (_motionY - y)) * ANGLE_INCREMENT),
            0.0, Vectors());
    }
    _motionX = x;
    _motionY = y;
}

//------------------------------------------------------------------------------
// idle
void Control::idle() {
    glutPostRedisplay();
}

//------------------------------------------------------------------------------
