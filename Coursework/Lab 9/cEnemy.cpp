#include "cEnemy.h"

cEnemy::cEnemy() : cModel()
{
	
}

void cEnemy::randomise()
{
	//Starting position of enemy
	cModel::m_mdlPosition.y = 0.0f;
	cModel::m_mdlPosition.x = rand() % (-40 - -100) + -100;
	cModel::m_mdlPosition.z = -40.0f;

	//Enemy can spawn at either side of screen
	if (rand() % 2 == 0)
	{
		cModel::m_mdlPosition.z = 40;
	}
	else
	{
		cModel::m_mdlPosition.z = -40;
	}

	//The model is active now
	cModel::m_IsActive = true;
}

void cEnemy::update()
{
	//If player has hit right side of screen move left
	if (m_mdlPosition.z < -35)//Right
	{
		right = true;
	}
	//If player has hit left side of screen move right
	if (m_mdlPosition.z > 35)//left
	{
		right = false;
	}

	if (right == true){ cModel::m_mdlPosition.z += 0.05; }	//move right
	if (right == false){ cModel::m_mdlPosition.z -= 0.05; }	//move left
}

cEnemy::~cEnemy()
{

}

