//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Matrix.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#pragma hdrstop
#include "Matrix.h"
#include "Vectors.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// pre-multiply this matrix by another matrix
Matrix &Matrix::preMultiply(const Matrix &m) {
    Matrix p;
    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            p._m[i][j] = m._m[i][X] * _m[X][j] + m._m[i][Y] * _m[Y][j]
                       + m._m[i][Z] * _m[Z][j] + m._m[i][W] * _m[W][j];
        }
    }
    return *this = p;
}

//------------------------------------------------------------------------------
// post-multiply this matrix by another matrix
Matrix &Matrix::postMultiply(const Matrix &m) {
    Matrix p;
    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            p._m[i][j] = _m[i][X] * m._m[X][j] + _m[i][Y] * m._m[Y][j]
                       + _m[i][Z] * m._m[Z][j] + _m[i][W] * m._m[W][j];
        }
    }
    return *this = p;
}

//------------------------------------------------------------------------------
// set this matrix to the identity matrix
Matrix &Matrix::identity() {
    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            _m[i][j] = 0.0;
        }
    }
    for (int k = 0; k < DIM; ++k) {
        _m[k][k] = 1.0;
    }
    return *this;
}

//------------------------------------------------------------------------------
// return the transpose of this matrix
Matrix Matrix::transpose() const {
    Matrix m;
    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            m._m[i][j] = _m[j][i];
        }
    }
    return m;
}

//------------------------------------------------------------------------------
// multiply this matrix by a vector
Vectors Matrix::multiply(const Vectors &v) const {
    double vx = _m[X][X] * v(X) + _m[X][Y] * v(Y) + _m[X][Z] * v(Z) + _m[X][W] * v(W);
    double vy = _m[Y][X] * v(X) + _m[Y][Y] * v(Y) + _m[Y][Z] * v(Z) + _m[Y][W] * v(W);
    double vz = _m[Z][X] * v(X) + _m[Z][Y] * v(Y) + _m[Z][Z] * v(Z) + _m[Z][W] * v(W);
    double vw = _m[W][X] * v(X) + _m[W][Y] * v(Y) + _m[W][Z] * v(Z) + _m[W][W] * v(W);
    return Vectors(vx, vy, vz, vw);
}

//------------------------------------------------------------------------------
// write this matrix as a 3 x 3
void Matrix::write3x3(ostream &out) const {
    out << "Matrix = (";
    for (int i = 0; i < DIM3; ++i) {
        out << endl << "(";
        for (int j = 0; j < DIM3; ++j) {
            out << _m[i][j] << (j < DIM3 - 1 ? ", " : ")");
        }
        out << (i < DIM3 - 1 ? "," : ")");
    }
}

//------------------------------------------------------------------------------
// write this matrix as a 4 x 4
void Matrix::write4x4(ostream &out) const {
    out << "Matrix = (";
    for (int i = 0; i < DIM4; ++i) {
        out << endl << "(";
        for (int j = 0; j < DIM4; ++j) {
            out << _m[i][j] << (j < DIM4 - 1 ? ", " : ")");
        }
        out << (i < DIM4 - 1 ? "," : ")");
    }
}

//------------------------------------------------------------------------------
