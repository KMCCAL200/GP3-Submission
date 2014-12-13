#include "cCamera.h"

void cCamera::fps()
{//set up the fps camera
	gluLookAt(	100, 0, cameraXpos,		0, 0, cameraXpos,		0, 1, 0);
				//camera location,		camera looking at,		camera up direction
}

void cCamera::top()
{//set up the fps camera
	gluLookAt(120, 110, 0, 0, 0, 0, 0, 1, 0);
}
