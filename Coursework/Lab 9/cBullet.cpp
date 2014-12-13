#include "cBullet.h"

cBullet::cBullet() : cModel()
{

}

void cBullet::update()
{
	//bullets new position
	cModel::m_mdlPosition += cModel::m_mdlDirection *cModel::m_mdlSpeed *0.07f;

	//if bullet leaves game area disable it
	if (cModel::m_mdlPosition.x > PLAYFIELDX ||
		cModel::m_mdlPosition.x < -PLAYFIELDX ||
		cModel::m_mdlPosition.z > PLAYFIELDZ ||
		cModel::m_mdlPosition.z < -PLAYFIELDZ)
		cModel::m_IsActive = false;
}

cBullet::~cBullet()
{

}
