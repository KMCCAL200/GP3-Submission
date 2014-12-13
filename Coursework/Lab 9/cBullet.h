#ifndef _CBULLET_H
#define _CBULLET_H

#include "GameConstants.h"
#include "cModel.h"

class cBullet : public cModel
{
public:
	cBullet();

	virtual void update(); //update the bullet

	~cBullet();

};
#endif