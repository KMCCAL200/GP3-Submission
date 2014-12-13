#include "cModel.h"

cModel::cModel()
{
	//set the default values for all new models
	m_mdlPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	m_mdlRotation = 0.0f;
	m_mdlDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	m_mdlSpeed = 0.0f;
	m_IsActive = false;
	m_mdlScale = glm::vec3(1.0f, 1.0f, 1.0f);
	m_Dimensions.s_mdldepth = 0.0f;
	m_Dimensions.s_mdlheight = 0.0f;
	m_Dimensions.s_mdlWidth = 0.0f;
	m_mdlRadius = m_Dimensions.s_mdldepth / 2;
}

// +++++++++++++++++++++++++++++++++++++++++++++
// Setters
// +++++++++++++++++++++++++++++++++++++++++++++

void cModel::setPosition(glm::vec3 mdlPosition)
{//set position
	m_mdlPosition = mdlPosition;
}

void cModel::setRotation(GLfloat mdlRotation)
{//set rotation
	m_mdlRotation = mdlRotation;
}

void cModel::setDirection(glm::vec3 mdlDirection)
{//set direction facing
	m_mdlDirection = mdlDirection;
}

void cModel::setSpeed(float mdlSpeed)
{//set the speed
	m_mdlSpeed = mdlSpeed;
}

void cModel::setIsActive(bool mdlIsActive)
{//set the model to active
	m_IsActive = mdlIsActive;
}

void cModel::setMdlDimensions(mdlDimensions mdlDims)
{//set dimentions
	m_Dimensions = mdlDims;
	m_mdlRadius = m_Dimensions.s_mdldepth / 2;
}

void cModel::setMdlRadius(float mdlRadius)
{//set radius of the model for collisions
	m_mdlRadius = mdlRadius;
}

void cModel::setScale(glm::vec3 mdlScale)
{//set the scale of the model
	m_mdlScale = mdlScale;
}

// +++++++++++++++++++++++++++++++++++++++++++++
// Getters
// +++++++++++++++++++++++++++++++++++++++++++++

glm::vec3 cModel::getPosition()
{//get position
	return m_mdlPosition;
}

GLfloat cModel::getRotation()
{//get rotation
	return m_mdlRotation;
}

glm::vec3 cModel::getDirection()
{//get direction facing
	return m_mdlDirection;
}

float cModel::getSpeed()
{//get the speed
	return m_mdlSpeed;
}

bool cModel::isActive()
{//get the model to active
	return m_IsActive;
}

mdlDimensions cModel::getMdlDimensions()
{//get dimentions
	return m_Dimensions;
}

float cModel::getMdlRadius()
{//get radius of the model for collisions
	return m_mdlRadius;
}

glm::vec3 cModel::getScale()
{//get the scale of the model
	return m_mdlScale;
}

void cModel::initialise(glm::vec3 mdlPosition, GLfloat mdlRotation, glm::vec3 mdlScale, glm::vec3 mdlDirection, float mdlSpeed, bool mdlIsActive)
{
	//set actual values of all variables
	setPosition(mdlPosition);
	setRotation(mdlRotation);
	setScale(mdlScale);
	setDirection(mdlDirection);
	setSpeed(mdlSpeed);
	setIsActive(mdlIsActive);
	m_Dimensions.s_mdldepth = 0.0f;
	m_Dimensions.s_mdlheight = 0.0f;
	m_Dimensions.s_mdlWidth = 0.0f;
	m_mdlRadius = m_Dimensions.s_mdldepth / 2;
	glm::vec3 mdlPos = getPosition();
	GLfloat mdlRot = getRotation();
	glRotatef(mdlRot, 0.0f, 1.0f, 0.0f);
	glTranslatef(mdlPos.x,mdlPos.y,mdlPos.z);
}

bool cModel::SphereSphereCollision(glm::vec3 mdlPosition, float mdlRadius)
{
	//use radius of the model to check for
	//sphere-sphere collisions

	const float distSq = lengthSQRD(m_mdlPosition - mdlPosition);

	const float sumRadius = (m_mdlRadius + mdlRadius);

	if (distSq < sumRadius * sumRadius)
	{
		return true; // Collision
	}
	return false; // No Collision
}

float cModel::lengthSQRD(glm::vec3 mdlLength)
{
	return (mdlLength.x * mdlLength.x) + (mdlLength.y * mdlLength.y) + (mdlLength.z * mdlLength.z);
}

cModel::~cModel()
{

}
