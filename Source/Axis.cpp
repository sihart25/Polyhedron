//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Axis Assessment
// Axis.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#include <gl/glut.h>
#pragma hdrstop
#include "Axis.h"
#include "Polyhedron.h"
#include "Vectors.h"
#include "Colour.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// setup this axis to match the polyhedron
void Axis::setup(const Polyhedron &polyhedron, int ident) {
    // copy polyhedron attributes
    _radius = polyhedron._radius;
    _angle = polyhedron._angle;
    _spin = polyhedron._spin;
    _axis = polyhedron._axis;
    _theta = polyhedron._theta;
    _phi = polyhedron._phi;
    _psi = polyhedron._psi;
    _rotateSpin = polyhedron._rotateSpin;
    // create containers of vertices
    _numberOfVertices = 2;
    _vertices = new Vectors *[_numberOfVertices];
    _transformVertices = new Vectors *[_numberOfVertices];
    _projectVertices = new Vectors *[_numberOfVertices];
    for (int vertexIndex = 0; vertexIndex < _numberOfVertices; ++vertexIndex) {
        _vertices[vertexIndex] = new Vectors();
        _transformVertices[vertexIndex] = new Vectors();
        _projectVertices[vertexIndex] = new Vectors();
    }
    switch (ident) {
        case X: {
            _colour = Colour(1.0, 0.0, 0.0);
            _vertices[0]->setPosition(1.0, 0.0, 0.0);
            _vertices[1]->setPosition(2.0, 0.0, 0.0);
            break;
        }
        case Y: {
            _colour = Colour(0.0, 1.0, 0.0);
            _vertices[0]->setPosition(0.0, 1.0, 0.0);
            _vertices[1]->setPosition(0.0, 2.0, 0.0);
            break;
        }
        case Z: {
            _colour = Colour(0.0, 0.0, 1.0);
            _vertices[0]->setPosition(0.0, 0.0, 1.0);
            _vertices[1]->setPosition(0.0, 0.0, 2.0);
            break;
        }
    }

}

//------------------------------------------------------------------------------
// erase this axis
void Axis::erase() {
    // delete containers of vertices
    for (int vertexIndex = 0; vertexIndex < _numberOfVertices; ++vertexIndex) {
        delete _vertices[vertexIndex];
        delete _transformVertices[vertexIndex];
        delete _projectVertices[vertexIndex];
    }
    delete[] _vertices;
    delete[] _transformVertices;
    delete[] _projectVertices;
}

//------------------------------------------------------------------------------
// clip this axis to lie in front of the camera
bool Axis::clip() const {
    for (int vertexIndex = 0; vertexIndex < _numberOfVertices; ++vertexIndex) {
        if ((*_transformVertices[vertexIndex])(Z) > -EPSILON) {
            return true;
        }
    }
    return false;
}

//------------------------------------------------------------------------------
// draw this axis using OpenGL
void Axis::draw(const vector<Light *> &/*lights*/, bool /*solid*/) const {
    if (!clip()) {
        glColor4f(_colour(R), _colour(G), _colour(B), _colour(A));
        glBegin(GL_LINES);
        for (int vertexIndex = 0; vertexIndex < _numberOfVertices; ++vertexIndex) {
            Vectors vertex = *_projectVertices[vertexIndex];
            glVertex2d(vertex(X), vertex(Y));
        }
        glEnd();
    }
}

//------------------------------------------------------------------------------
