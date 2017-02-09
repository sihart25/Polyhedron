//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Material.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#pragma hdrstop
#include "Material.h"
#include "Colour.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// read material
bool Material::read(istream &in, string &token) {
    if (token == "Material") {
        if (in >> token, token != "{") {
            throw string("Error : Missing material open brace");
        }
        while (in >> token, token != "}") {
            if (token == "Ambient") {
                in >> _ambient;
            }
            else if (token == "Diffuse") {
                in >> _diffuse;
            }
            else if (token == "Specular") {
                in >> _specular;
            }
            else if (token == "Shininess") {
                in >> _shininess;
            }
            else if (token == "Emission") {
                in >> _emission;
            }
            else {
                throw string("Error : Invalid material attribute = " + token);
            }
        }
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
