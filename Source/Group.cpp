//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Group.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#pragma hdrstop
#include "Group.h"
#include "Object.h"
#include "Reader.h"
#include "Transform.h"
#include "Light.h"
#include "Shape.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static data member
vector<Light *> Group::_lights;
vector<Shape *> Group::_shapes;

//------------------------------------------------------------------------------
// erase group
void Group::erase() {
    for (vector<Object *>::const_iterator object = _objects.begin(); object != _objects.end();
        ++object) {
        delete *object;
    }
    _objects.clear();
    _lights.clear();
    _shapes.clear();
}

//------------------------------------------------------------------------------
// read group
bool Group::read(istream &in, string &token, Group &group) {
    if (token == "Group") {
        if (in >> token, token != OPENING_BRACE) {
            throw string("Error : Missing group opening brace");
        }
        Group *nestedGroup = new Group();
        group.push_back(nestedGroup);
        while (in >> token, token != CLOSING_BRACE) {
            if (Reader::comment(in, token)) {}
            else if (Object::read(in, token, *nestedGroup)) {}
            else {
                throw string("Error : Invalid group attribute = " + token);
            }
        }
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// write group
void Group::write(ostream &out) const {
    out << "Group" << endl;
    for (vector<Object *>::const_iterator object = _objects.begin(); object != _objects.end();
        ++object) {
        out << **object;
    }
}

//------------------------------------------------------------------------------
// update group
void Group::update(bool axis) {
    for (vector<Object *>::const_iterator object = _objects.begin(); object != _objects.end();
        ++object) {
        (*object)->update(axis);
    }
}

//------------------------------------------------------------------------------
// transform group
void Group::transform(Transform &transform) {
    Transform nestedTransform(transform);
    for (vector<Object *>::const_iterator object = _objects.begin(); object != _objects.end();
        ++object) {
        (*object)->transform(nestedTransform);
    }
}

//------------------------------------------------------------------------------
// project group
void Group::project(double fieldOfView) {
    for (vector<Shape *>::const_iterator shape = _shapes.begin(); shape != _shapes.end(); ++shape) {
        (*shape)->project(fieldOfView);
    }
}

//------------------------------------------------------------------------------
// draw group
void Group::draw(bool solid) const {
    for (vector<Shape *>::const_iterator shape = _shapes.begin(); shape != _shapes.end(); ++shape) {
        (*shape)->draw(_lights, solid);
    }
}

//------------------------------------------------------------------------------
