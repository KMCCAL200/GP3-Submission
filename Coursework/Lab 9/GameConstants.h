#ifndef _GAMECONSTANTS_H
#define _GAMECONSTANTS_H

#define GLM_FORCE_RADIANS

#include <stdlib.h>
#include <Windows.h>
#include <GL\glut.h>
#include <assimp\Importer.hpp>    // C++ importer interface
#include <assimp\scene.h>           // Output data structure
#include <assimp\postprocess.h>     // Post processing flags
#include <OpenAL\al.h>
#include <OpenAL\alc.h>
#include <OpenAL\alut.h>
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\geometric.hpp"
#include "glm\gtc\quaternion.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtx\quaternion.hpp"
#include "glm-0.3.2\glm\glm.h"
#include <vector>


//Define the string to appear in the window title
#define WINDOW_TITLE "Shooting gallery"

struct mdlDimensions{
	float s_mdlWidth, s_mdlheight, s_mdldepth;
};

//Variables that can be accessed anywhere in the application

//area the game takes place in
const float PLAYFIELDX  = 100.0f;
const float PLAYFIELDZ = 300.0f;

extern int drawMode;
extern int cameraXpos;		//x position of fps camera
extern float translationZ;	//how much is player moving
extern bool fire;			// is the gun being fired
extern bool fps;			// is the fps camera active
extern bool sound;			//is sound active

#endif