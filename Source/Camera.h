//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Camera.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Camera_h
#define Camera_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#include "Transform.h"
#include "Vectors.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Camera {

    public:

        Camera() : _rotation(0.0, 0.0, 0.0), _distance(0.0), _centre(0.0, 0.0, 0.0),
            _position(0.0, 0.0, 0.0, 1.0), _direction(0.0, 0.0, -1.0, 0.0), _up(0.0, 1.0, 0.0, 0.0),
            _fieldOfView(60.0), _scale(1.0) {}
        static void clear();
        static bool read(istream &in, string &token, vector<Camera *> &cameras);
        static void next(vector<Camera *> &_cameras);
        static void move(const Vectors &rotation, double distance, const Vectors &centre);
        static void transform(Transform &transform);
        static double fieldOfView() { return _camera->_fieldOfView; }

    private:

        Transform transform();

        Vectors _rotation;
        double _distance;
        Vectors _centre;
        Vectors _position;
        Vectors _direction;
        Vectors _up;
        double _fieldOfView;
        double _scale;
        static Camera *_camera;

    };

} // ComputerGraphics

#endif // Camera_h

//------------------------------------------------------------------------------
