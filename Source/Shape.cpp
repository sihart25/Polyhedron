//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Shape.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#pragma hdrstop
#include "Shape.h"
#include "Group.h"
#include "Polyhedron.h"
#include "Transform.h"
#include "Vectors.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static function to read shape
bool Shape::read(istream &in, string &token, Group &group) {
    if (Polyhedron::read(in, token, group)) {
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// transform this shape
void Shape::transform(Transform &transform) {
    _transform = transform;
    _transform.rotate(_angle,  _axis);
    _transform.rotate(_theta, _phi, _psi);
    _transform.scale(Vectors(_radius, _radius, _radius, 0.0));
    _angle += _spin;
    _angle -= 360.0 * floor(_angle / 360.0);
    _psi += _rotateSpin;
    _psi -= 360.0 * floor(_psi / 360.0);
    for (int vertexIndex = 0; vertexIndex < _numberOfVertices; ++vertexIndex) {
        // transform container of vertices
        *_transformVertices[vertexIndex] = _transform().multiply(*_vertices[vertexIndex]);
    }
    centroid();
}

//------------------------------------------------------------------------------
// project this polyhedron
void Shape::project(double fieldOfView) {
    Transform projection;
    projection.projection(fieldOfView);
    for (int vertexIndex = 0; vertexIndex < _numberOfVertices; ++vertexIndex) {
        // project container of transformed vertices
        *_projectVertices[vertexIndex] =
            projection().multiply(*_transformVertices[vertexIndex]).homogenize();
    }
}

//------------------------------------------------------------------------------
// centroid of this shape
void Shape::centroid() {
    _centroid = Vectors();
    for (int vertexIndex = 0; vertexIndex < _numberOfVertices; ++vertexIndex) {
        // sum the transformed vertices
        _centroid += *_transformVertices[vertexIndex];
    }
    // mean of the transformed vertices
    _centroid /= _numberOfVertices;
}

//------------------------------------------------------------------------------
