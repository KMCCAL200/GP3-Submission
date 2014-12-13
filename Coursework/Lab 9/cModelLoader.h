#ifndef _CMODELLOADER_H
#define _CMODELLOADER_H

#include "GameConstants.h"

class cModelLoader
{
public:
	cModelLoader();

	void loadModel(const char* mdlFilename); //get the model
	void renderMdl(glm::vec3 mdlPosition, float mdlRotationAngle, glm::vec3 mdlScale); //render the model
	mdlDimensions getModelDimensions(); // get size of model

	~cModelLoader();
private:
	// Set the position of the model in world space, and set the rotation.
	GLMmodel* m_model;
};
#endif