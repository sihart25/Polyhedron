//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Reader.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <fstream>
#include <string>
#pragma hdrstop
#include "Reader.h"
#include "Group.h"
#include "Screen.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static function to read scene
void Reader::read(const string &filename, Group &group, Screen &screen) {
    try {
        ifstream in(filename.c_str());
        if (!in.good()) {
            throw string("Error : Invalid file name = " + filename);
        }
        string token;
        screen.clear();
        if (!(in >> token, screen.read(in, token))) {
            throw string("Error : Invalid file attribute = " + token);
        }
        group.clear();
        if (!(in >> token, Group::read(in, token, group))) {
            throw string("Error : Invalid file attribute = " + token);
        }
    }
    catch (string s) {
        cout << s << endl;
    }
    catch (...) {
        cout << "Error : Unknown exception caught in reader" << endl;
    }
}

//------------------------------------------------------------------------------
// static function to read comment
bool Reader::comment(istream &in, string &token) {
    if (token == OPENING_COMMENT) {
        while (in >> token, token != CLOSING_COMMENT) {
        }
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
