#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h>


class Camera
{
public:
    Camera();
    ~Camera();

    GLdouble eye[3];
    GLdouble center[3];
    GLdouble up[3];

};

#endif // CAMERA_H
