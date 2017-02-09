//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Test Assessment
// Test.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#pragma hdrstop
#include "Test.h"
#include "Constants.h"
#include "Vectors.h"
#include "Transform.h"
#include "Matrix.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// test
void Test::test() {

    string filename("..\\Data\\Test.txt");
    ofstream out(filename.c_str());
    if (!out.good()) {
        throw string("Error : Invalid file name = " + filename);
    }

    rand();
    double theta = (double)rand() / (double)RAND_MAX * 90.0;
    double phi = (double)rand() / (double)RAND_MAX * 90.0;
    double psi = (double)rand() / (double)RAND_MAX * 90.0;

    out << "Arbitrary values are used to test the rotation matrix." << endl;
    out << "theta = " << theta << endl;
    out << "phi = " << phi << endl;
    out << "psi = " << psi << endl;
    out << endl;

    Transform transform;
    transform.rotate(theta, phi, psi);
    out << "The rotation matrix is generated." << endl;
    out << fixed << transform() << endl;
    out << endl;

    Vectors origin;
    origin.setPosition(0.0, 0.0, 0.0);
    Vectors transformedOrigin;
    transformedOrigin = transform().multiply(origin);
    out << "The origin is rotated onto itself." << endl;
    out << origin << endl;
    out << transformedOrigin << endl;
    out << endl;

    theta *= PI / 180.0;
    phi *= PI / 180.0;
    psi *= PI / 180.0;

    Vectors axis;
    axis.setPosition(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
    Vectors transformedAxis;
    transformedAxis = transform().multiply(axis);
    out << "A point on the axis is rotated onto itself." << endl;
    out << axis << endl;
    out << transformedAxis << endl;
    out << endl;

    Vectors point;
    point.setPosition((double)rand() / (double)RAND_MAX, (double)rand() / (double)RAND_MAX,
        (double)rand() / (double)RAND_MAX);
    Vectors transformedPoint;
    transformedPoint = transform().multiply(point);
    out << "An arbitrary point is rotated around the axis." << endl;
    out << point << endl;
    out << transformedPoint << endl;
    out << endl;

    double pointDistance = (point - axis).magnitude();
    double transformedPointDistance = (transformedPoint - axis).magnitude();
    out << "The distances of the arbitrary point and the rotated point from the axis are equal." <<
        endl;
    out << "distance = " << pointDistance << endl;
    out << "distance = " << transformedPointDistance << endl;
    out << endl;

    double angle = acos((point.cross(axis).unit()).dot(transformedPoint.cross(axis).unit())) /
        PI * 180.0;
    out << "The angle between the arbitrary point and the rotated point is equal to psi." << endl;
    out << "angle = " << angle << endl;
    out << endl;

    Matrix transpose(transform().transpose());
    out << "The product of the matrix and its transpose is the identity matrix." << endl;
    out << fixed << transpose.postMultiply(transform()) << endl;
}

//------------------------------------------------------------------------------
