//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Polyhedron.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <gl/glut.h>
#pragma hdrstop
#include "Polyhedron.h"
#include "Face.h"
#include "Axis.h"
#include "Group.h"
#include "Colour.h"
#include "Vectors.h"
#include "Reader.h"
#include "Material.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// erase polyhedron
void Polyhedron::erase() {
    for (int vertexIndex = 0; vertexIndex < _numberOfVertices; ++vertexIndex) {
        delete _vertices[vertexIndex];
        delete _transformVertices[vertexIndex];
        delete _projectVertices[vertexIndex];
    }
    delete[] _vertices;
    delete[] _transformVertices;
    delete[] _projectVertices;
    for (int faceIndex = 0; faceIndex < _numberOfFaces; ++faceIndex) {
        delete _faces[faceIndex];
    }
    delete[] _faces;
}

//------------------------------------------------------------------------------
// read polyhedron
bool Polyhedron::read(istream &in, string &token, Group &group) {
    if (token == "Polyhedron") {
        if (in >> token, token != OPENING_BRACE) {
            throw string("Error : Missing polyhedron opening brace");
        }
        Polyhedron *polyhedron = new Polyhedron;
        group.push_back(polyhedron);
        while (in >> token, token != CLOSING_BRACE) {
            if (polyhedron->_material.read(in, token)) {}
            else if (token == "Filename") {
                in >> polyhedron->_filename;
            }
            else if (token == "Radius") {
                in >> polyhedron->_radius;
            }
            else if (token == "Angle") {
                in >> polyhedron->_angle;
            }
            else if (token == "Spin") {
                in >> polyhedron->_spin;
            }
            else if (token == "Axis") {
                polyhedron->_axis.readDirection(in);
            }
            else if (token == "Rotate") {
                in >> polyhedron->_theta >> polyhedron->_phi >> polyhedron->_psi;
            }
            else if (token == "RotateSpin") {
                in >> polyhedron->_rotateSpin;
            }
            else {
                throw string("Error : Invalid polyhedron attribute = " + token);
            }
        }
        try {
            ifstream in(polyhedron->_filename.c_str());
            if (!in.good()) {
                throw string("Error : Invalid file name = " + polyhedron->_filename);
            }
            polyhedron->readFile(in);
        }
        catch (string s) {
            cout << s << endl;
        }
        catch (...) {
            cout << "Error : Unknown exception caught in read" << endl;
        }
        Axis *axisX = new Axis(*polyhedron, X);
        group.push_back(axisX);
        Axis *axisY = new Axis(*polyhedron, Y);
        group.push_back(axisY);
        Axis *axisZ = new Axis(*polyhedron, Z);
        group.push_back(axisZ);
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// read polyhedron file
void Polyhedron::readFile(istream &in) {
    in >> _numberOfVertices;
    _vertices = new Vectors *[_numberOfVertices];
    _transformVertices = new Vectors *[_numberOfVertices];
    _projectVertices = new Vectors *[_numberOfVertices];
    for (int vertexIndex = 0; vertexIndex < _numberOfVertices; ++vertexIndex) {
        // read into container of vertices
        _vertices[vertexIndex] = new Vectors();
        _vertices[vertexIndex]->readPosition(in);
        // create container of transformed vertices
        _transformVertices[vertexIndex] = new Vectors();
        // create container of projected vertices
        _projectVertices[vertexIndex] = new Vectors();
    }
    in >> _numberOfFaces;
    _faces = new Face *[_numberOfFaces];
    for (int faceIndex = 0; faceIndex < _numberOfFaces; ++faceIndex) {
        // read into container of faces
        _faces[faceIndex] = new Face();
        in >> *_faces[faceIndex];
    }
}

//------------------------------------------------------------------------------
// centroid of face of this polyhedron
Vectors Polyhedron::centroid(int face) const {
    Vectors faceCentroid;
    for (int index = 0; index < _faces[face]->numberOfIndices(); ++index) {
        // sum the transformed vertices
        faceCentroid += *_transformVertices[_faces[face]->indices()[index]];
    }
    // mean of the transformed vertices
    faceCentroid /= _faces[face]->numberOfIndices();
    return faceCentroid;
}

//------------------------------------------------------------------------------
// normal to face of this polyhedron
Vectors Polyhedron::normal(int face) const {
    return (centroid(face) - _centroid).unit();
}

//------------------------------------------------------------------------------
// cull face of this polyhedron
bool Polyhedron::cull(int face) const {
    return normal(face).dot(Vectors(0.0, 0.0, 0.0, 1.0) - centroid(face)) < 0.0;
}

//------------------------------------------------------------------------------
// clip face of this polyhedron
bool Polyhedron::clip(int face) const {
    for (int index = 0; index < _faces[face]->numberOfIndices(); ++index) {
        if ((*_transformVertices[_faces[face]->indices()[index]])(Z) > -EPSILON) {
            return true;
        }
    }
    return false;
}

//------------------------------------------------------------------------------
// light face of this polyhedron
Colour Polyhedron::light(const vector<Light *> &lights, int face) const {
    Vectors centroidVector(centroid(face));
    Vectors normalVector(normal(face));
    Vectors cameraVector(Vectors(0.0, 0.0, 0.0, 1.0) - centroidVector);
    cameraVector.normalize();
    Colour colour;
    for (vector<Light *>::const_iterator light = lights.begin(); light != lights.end(); ++light) {
        colour += (*light)->ambient() * _material.ambient();
        Vectors lightVector((*light)->position());
        // point or directional light source
        if (fabs(lightVector(W)) >= EPSILON ) {
            lightVector -= centroidVector;
        }
        lightVector.normalize();
        double intensity = lightVector.dot(normalVector);
        // apply diffuse and specular lighting if light is visible at the face
        if (intensity >= 0.0) {
            colour += intensity * (*light)->diffuse() * _material.diffuse();
            double intensity = (lightVector + cameraVector).unit().dot(normalVector);
            if (intensity >= 0.0) {
                colour += pow(intensity, _material.shininess()) *
                          (*light)->specular() * _material.specular();
            }
        }
    }
    colour += _material.emission();
    return colour;
}

//------------------------------------------------------------------------------
// draw this polyhedron
void Polyhedron::draw(const vector<Light *> &lights, bool solid) const {
    for (int faceIndex = 0; faceIndex < _numberOfFaces; ++faceIndex) {
        draw(lights, solid, faceIndex);
    }
}

//------------------------------------------------------------------------------
// draw face of this polyhedron
void Polyhedron::draw(const vector<Light *> &lights, bool solid, int face) const {
    if (!(cull(face) && solid) && !clip(face)) {
        Colour colour(light(lights, face));
        glColor4f(colour(R), colour(G), colour(B), colour(A));
        if (solid) {
            glBegin(GL_POLYGON);
        }
        else {
            glBegin(GL_LINE_LOOP);
        }
        for (int index = 0; index < _faces[face]->numberOfIndices(); ++index) {
            Vectors vertex = *_projectVertices[_faces[face]->indices()[index]];
            glVertex2d(vertex(X), vertex(Y));
        }
        glEnd();
    }
}

//------------------------------------------------------------------------------
