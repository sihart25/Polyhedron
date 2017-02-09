//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Matrix.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Matrix_h
#define Matrix_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include "Vectors.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Matrix {

    public:

        Matrix() {
            identity();
        }
        const double *operator()() const {
            return _m[0];
        }
        double operator()(int i, int j) const {
            return _m[i][j];
        }
        double &operator()(int i, int j) {
            return _m[i][j];
        }
        Matrix &identity();
        Matrix transpose() const;
        Matrix &preMultiply(const Matrix &m);
        Matrix &postMultiply(const Matrix &m);
        Vectors multiply(const Vectors &v) const;
        friend ostream &operator<<(ostream &out, const Matrix &m) {
            m.write3x3(out);
            return out;
        }

    private:

        void write3x3(ostream &out) const;
        void write4x4(ostream &out) const;
        double _m[DIM][DIM];

    };

} // ComputerGraphics

#endif // Matrix_h

//------------------------------------------------------------------------------
