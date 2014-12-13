#include "cModelLoader.h"

cModelLoader::cModelLoader()
{
	m_model = NULL;
}

void cModelLoader::loadModel(const char* mdlFilename)
{
	//Load model from file
	m_model = glmReadOBJ(mdlFilename);
	glmVertexNormals(m_model, 180.0, false);
}

//Render the model
void cModelLoader::renderMdl(glm::vec3 mdlPosition, float mdlRotationAngle, glm::vec3 mdlScale)
{
	//Render the model using current position , rotation and scale
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(mdlPosition.x, 0.0f, -mdlPosition.z);
	glRotatef(mdlRotationAngle, 0, 1, 0);
	glScalef(mdlScale.x, mdlScale.y, mdlScale.z);
	//DrW THE MODEL
	glmDraw(m_model, GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
	glPopMatrix();
}

mdlDimensions cModelLoader::getModelDimensions()
{
	//Set the dimentions of the model (width, height, depth)
	mdlDimensions mdl_Dims;
	GLfloat mdlDims[3];
	glmDimensions(m_model, mdlDims);
	mdl_Dims.s_mdlWidth = mdlDims[0];
	mdl_Dims.s_mdlheight = mdlDims[1];
	mdl_Dims.s_mdldepth = mdlDims[2];
	return mdl_Dims;
}

cModelLoader::~cModelLoader()
{

}
