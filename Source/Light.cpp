//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Light.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#pragma hdrstop
#include "Light.h"
#include "Group.h"
#include "Reader.h"
#include "Transform.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static function to read light
bool Light::read(istream &in, string &token, Group &group) {
    if (token == "Light") {
        if (in >> token, token != OPENING_BRACE) {
            throw string("Error : Missing light opening brace");
        }
        Light *light = new Light();
        group.push_back(light);
        while (in >> token, token != CLOSING_BRACE) {
            if (token == "Centre") {
                in >> light->_centre;
            }
            else if (token == "Ambient") {
                in >> light->_ambient;
            }
            else if (token == "Diffuse") {
                in >> light->_diffuse;
            }
            else if (token == "Specular") {
                in >> light->_specular;
            }
            else {
                throw string("Error : Invalid light attribute = " + token);
            }
        }
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// transform light
void Light::transform(Transform &transform) {
    _position = transform.forward().multiply(_centre);
}

//------------------------------------------------------------------------------
