
#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>
#include <cmath>
using namespace std;
//class ActorBaseClass;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{

}

int StudentWorld::init()
{
	int numOfDirtPiles = max(180 - 20 * getLevel(), 20);
	for (int i = 0; i < numOfDirtPiles; i++)
	{
		int randomX = 0;
		int randomY = 0;
		while (sqrt((randomX - (VIEW_WIDTH / 2)) * (randomX - (VIEW_WIDTH / 2)) + (randomY - (VIEW_HEIGHT / 2)) * (randomY - (VIEW_HEIGHT / 2))) > 120)
		{

			randomX = randInt((VIEW_WIDTH / 2) - 120, (VIEW_WIDTH / 2) + 120);
			randomY = randInt((VIEW_HEIGHT / 2) - 120, (VIEW_HEIGHT / 2) + 120);
		}
		DirtPile* newDirtPile = new DirtPile(IID_DIRT, randomX, randomY, this, 0, 1, 1);
		ActorsVector.push_back(newDirtPile);
	}
	playerObject = new Socrates(0, 1, this);
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
 
	decLives();
	playerObject->doSomething();
	vector<ActorBaseClass*>::iterator it;
	for (it = ActorsVector.begin(); it != ActorsVector.end(); it++)
	{
		(*it)->doSomething();
	}
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
	delete playerObject;
	vector<ActorBaseClass*>::iterator it;
}
