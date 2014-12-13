#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that the local glxext.h is picked up, rather than the system one

#define GL_GLEXT_PROTOTYPES

#include <glew.h>
#include "GameConstants.h"
#include <windows.h>
#include "windowOGL.h"
#include "cWNDManager.h"
#include "libdrawtext-0.2.1\drawtext.h"
#include "cModelLoader.h"
#include "cModel.h"
#include "cEnemy.h"
#include "cPlayer.h"
#include "cBullet.h"
#include "cSound.h"
#include "cCamera.h"
#include "cImageLoader.h"
#include <vector>
#include <time.h>
#include <FreeImage.h>

#define FONT_SZ	24

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR cmdLine,
                   int cmdShow)
{

    //Set thwe window settings
    const int windowWidth = 1024;
    const int windowHeight = 768;
    const int windowBPP = 16;

	//create the image loader
	cImageLoader img;

	//How many enemies have been hit
	int hits = 0;

    //This is the window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

    //The OpenGL code
    windowOGL theOGLWnd;

	//setup the cameras
	cCamera cam;

    //Attach the game to the window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);


    //Attempt to create the window
	if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
    {//If it fails
        MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	//Initialize the game
	if (!theOGLWnd.initOGL()) 
    {
        MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	srand(time(NULL));

	//create the enemy
	cModelLoader enemyMdl;

	//Load the model for the enemies
	enemyMdl.loadModel("Models/Handgun Model.obj"); //enemy
	
	//create a list of 5 enemies
	cEnemy enemyList[5];

	//set up the enemies position and size
	for (int loop = 0; loop < 5; loop++)
	{
		enemyList[loop].randomise();
		enemyList[loop].setMdlDimensions(enemyMdl.getModelDimensions());
		enemyList[loop].setScale(glm::vec3(2, 2, 2));
	}

	img.LoadTexture("Models/textures/map_Kd Tardis.tga"); 

	//create the emeny
	cModelLoader playerMdl;

	//Load the model for the player
	playerMdl.loadModel("Models/forlan_gun.obj"); // Player

	//set up the players position and size
	cPlayer thePlayer;
	thePlayer.initialise(glm::vec3(0, 0, 0), 0.0f, glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), 5.0f, true);
	thePlayer.setMdlDimensions(playerMdl.getModelDimensions());
	thePlayer.setScale(glm::vec3(20, 20, 20));
	thePlayer.setRotation(270);
		
	//create the bullet
	cModelLoader theBullet;

	//Load the model for the bullet
	theBullet.loadModel("Models/bullet.obj");
	
	//crete list to hold the bullets
	std::vector<cBullet*> BulletList;
	std::vector<cBullet*>::iterator index;

	// create the font
	struct dtx_font *fntmain;

	//load the font
	fntmain = dtx_open_font("Fonts/doctor_who.ttf", 0);
	dtx_prepare_range(fntmain, FONT_SZ, 0, 256);             /* ASCII */
	//set the font and size
	dtx_use_font(fntmain, FONT_SZ);

	//Load music
	cSound themeMusic;
	themeMusic.createContext();
	themeMusic.loadWAVFile("Audio/robot.wav");

	//play the music in a loop
	//themeMusic.playAudio(AL_LOOPING);

	//load explosion
	cSound explosionFX;
	explosionFX.createContext();
	explosionFX.loadWAVFile("Audio/boom.wav");

	//load firing sound
	cSound firingFX;
	firingFX.createContext();
	firingFX.loadWAVFile("Audio/laser.wav");

    //This is the mainloop, we render frames until isRunning returns false
	while (pgmWNDMgr->isWNDRunning())
	{
		pgmWNDMgr->processWNDEvents(); //Process any window events

		//set up the window
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		theOGLWnd.initOGL();
		glClearColor(0.8, 0.9, 1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Select a camera to use
		if (fps == true)
		{//close up moving camera
			cam.fps();
		}
		else
		{//top down statonary camera
			cam.top();
		}

		//Do any pre-rendering logic
		//Render the scene
		//Drawing the model

		//If the enemy has not been shot render it
		for (int loop = 0; loop < 5; loop++)
		{
			if (enemyList[loop].isActive())
			{
			enemyMdl.renderMdl(enemyList[loop].getPosition(), enemyList[loop].getRotation(), enemyList[loop].getScale());
			enemyList[loop].update();
			}
		}

		//Render the player model
		playerMdl.renderMdl(thePlayer.getPosition(), thePlayer.getRotation(), thePlayer.getScale());
		thePlayer.update();
		
		//are we shooting?
		if (fire)
		{
			//create and set up a bullet
			cBullet* bullet = new cBullet();
			glm::vec3 mdlBulletDirection;
			mdlBulletDirection.z = 0.0f;
			mdlBulletDirection.y = 0.0f;
			mdlBulletDirection.x = 1.0f;
			mdlBulletDirection *= -1;

			//set the position and direction the bullet will move in
			bullet->setDirection(mdlBulletDirection);
			bullet->setRotation(255.0f);
			bullet->setScale(glm::vec3(2, 2, 2));
			bullet->setSpeed(5.0f);
			bullet->setPosition(thePlayer.getPosition() + mdlBulletDirection);
			bullet->setIsActive(true);
			bullet->setMdlDimensions(theBullet.getModelDimensions());
			bullet->update();
			BulletList.push_back(bullet);
			fire = false;
			//if sound is on play shooting sound
			if (sound == true)
			firingFX.playAudio(AL_FALSE);
		}

		//Check to see if a collision between a bullet and enemy has happened
		for (index = BulletList.begin(); index != BulletList.end(); ++index)
		{
			if ((*index)->isActive())//Find active bullet
			{
				//render the bullet
				theBullet.renderMdl((*index)->getPosition(), (*index)->getRotation(), (*index)->getScale());
				(*index)->update();
				for (int loop = 0; loop < 5; loop++)// check all enemies
				{
					enemyList[loop].update();
					if (enemyList[loop].isActive())//if the enemy is dead dont need to check for a collision
					{
						//check for a collision
						if ((*index)->SphereSphereCollision(enemyList[loop].getPosition(), enemyList[loop].getMdlRadius()))
						{
							//disable enemy
							enemyList[loop].setIsActive(false);
							//disable bullet
							(*index)->setIsActive(false);
							//if sound is on play explosion sound
							if (sound == true)
								explosionFX.playAudio(AL_FALSE);
							//add to player score
							hits++;
							break; // No need to check for other bullets.
						}
					}
				}
			}
		}

		//set the scene and how it will appear
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, windowWidth, 0, windowHeight);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glPushAttrib(GL_DEPTH_TEST);
		glDisable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glTranslatef(0, 730, 0);

		//set the text on the screen
		dtx_string("Score: ");

		//finish drawing scene
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

		//switch  the buffers, to start drawig the next frame
		pgmWNDMgr->swapBuffers();
    }

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

    return 0; //Return success
}
