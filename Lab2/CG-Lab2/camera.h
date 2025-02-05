#ifndef _CAMERA_H
#define _CAMERA_H
#include "algebra.h"

typedef struct _Camera {
	Vector position;
	Vector rotation;
	double fov; 
	double nearPlane; 
	double farPlane; 
} Camera;

enum ProjectionMode{
    ORTHOGONAL,
    PERSPECTIVE
};

Matrix ProjectionMatrix(
	Camera cam, 
	int screenWidth, 
	int screenHeight, 
	ProjectionMode mode = PERSPECTIVE);
Matrix ViewMatrix(Camera cam);

#endif