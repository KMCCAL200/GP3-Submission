#include "cPlayer.h"

cPlayer::cPlayer() : cModel()
{

}

void cPlayer::update()
{
	//if told to move left and position is within the left boundary, move left
	if (m_mdlPosition.z > -40 && translationZ <0)//left
	{
	cModel::m_mdlPosition.z += translationZ;
	}
	//if told to move riight and position is within the right boundary, move right
	if (m_mdlPosition.z < 40 && translationZ >0)//right
	{
		cModel::m_mdlPosition.z += translationZ;
	}
	//reset movement to zero
	translationZ = 0;	
}

cPlayer::~cPlayer()
{

}