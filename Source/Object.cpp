//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Object.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#pragma hdrstop
#include "Object.h"
#include "Group.h"
#include "Transform.h"
#include "Light.h"
#include "Shape.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static function to read shape
bool Object::read(istream &in, string &token, Group &group) {
    if (Group::read(in, token, group)) {
        return true;
    }
    else if (Transform::read(in, token, group)) {
        return true;
    }
    else if (Light::read(in, token, group)) {
        return true;
    }
    else if (Shape::read(in, token, group)) {
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
