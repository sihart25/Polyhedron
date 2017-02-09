//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Face.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#pragma hdrstop
#include "Face.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// erase face
void Face::erase() {
    delete[] _indices;
}

//------------------------------------------------------------------------------
// read face
void Face::read(istream &in) {
    in >> _numberOfIndices;
    _indices = new int[_numberOfIndices];
    for (int index = 0; index < _numberOfIndices; ++index) {
        in >> _indices[index];
    }
}

//------------------------------------------------------------------------------
// write face
void Face::write(ostream &out) const {
    out << _numberOfIndices;
    for (int index = 0; index < _numberOfIndices; ++index) {
        out << " " << _indices[index];
    }
}

//------------------------------------------------------------------------------
