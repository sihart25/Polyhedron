//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Display.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <gl/glut.h>
#pragma hdrstop
#include "Display.h"
#include "Control.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static data member
Control *Display::_control = 0;

//------------------------------------------------------------------------------
// initialize
void Display::initialize(int argc, char **argv) {
    try {
        // initialise OpenGL
        _control = new Control();
        glutInit(&argc, argv);
        glutInitWindowPosition(0, 0);
        glutInitWindowSize(WIDTH, HEIGHT);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        glutCreateWindow("Polyhedron");
        glutDisplayFunc(Display::display);
        glutReshapeFunc(Display::reshape);
        glutKeyboardFunc(Display::keyboard);
        glutMouseFunc(Display::mouse);
        glutMotionFunc(Display::motion);
        glutSpecialFunc(Display::special);
        glutIdleFunc(Display::idle);
        // initialise control
        _control->menu();
        _control->initialize(argc, argv);
        // call GLUT main loop
        glutMainLoop();
    }
    catch (...) {
        cout << "Error : Unknown exception caught in display" << endl;
    }
    delete _control;
}

//------------------------------------------------------------------------------
