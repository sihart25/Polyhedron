//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Scene.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <gl/glut.h>
#pragma hdrstop
#include "Scene.h"
#include "Reader.h"
#include "Group.h"
#include "Screen.h"
#include "Transform.h"
#include "Shape.h"
#include "Colour.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// read scene
void Scene::read(const string &filename) {
    Reader::read(filename, _group, _screen);
    next();
}

//------------------------------------------------------------------------------
// draw scene
void Scene::draw(bool axis, bool solid) {
    // setup OpenGL with orthonormal projection, no lighting and no depth buffering
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-0.5 * _screen.aspectRatio(), 0.5 * _screen.aspectRatio(), -0.5, 0.5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_LIGHTING);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(background()(R), background()(G), background()(B), background()(A));
    // clear and update containers of lights and shapes
    Group::lights().clear();
    Group::shapes().clear();
    _group.update(axis);
    // transform according to camera and transform objects
    Transform transform;
    _screen.transform(transform);
    _group.transform(transform);
    // sort shapes according to depth
    sort(Group::shapes().begin(), Group::shapes().end(), ShapePredicate());
    // project according to field of view
    _group.project(_screen.fieldOfView());
    // draw all objects
    _group.draw(solid);
}

//------------------------------------------------------------------------------
