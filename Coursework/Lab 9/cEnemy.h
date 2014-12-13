#ifndef _CENEMIES_H
#define _CENEMIES_H

#include "GameConstants.h"
#include "cModel.h"

class cEnemy : public cModel
{
public:
	cEnemy();

	void randomise();		//set starting position
	virtual void update();	//update position

	~cEnemy();

private:
	bool right = true; //is the enemy moving right
};
#endif