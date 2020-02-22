//i think this is project3_draft1 save, not accidental skeleton.zip opened save
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
	//init dirtPiles
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
		DirtPile* newDirtPile = new DirtPile(randomX, randomY, this);
		ActorsVector.push_back(newDirtPile);
	}

	//init Socrates
	playerObject = new Socrates(this);

	//init food items
    return GWSTATUS_CONTINUE_GAME;

}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
	playerObject->doSomething();
	vector<ActorBaseClass*>::iterator it;
	for (it = ActorsVector.begin(); it != ActorsVector.end(); it++)
	{
		(*it)->doSomething();
	}

	removeDeadActors();


	setGameStatText("Lives: " + to_string(getScore()) + " Level: " + to_string(getLevel()) + " Lives: " + to_string(getLives())+ " Sprays: " + to_string(getPlayerObjectSpraysLeft()) + " Flames: " + to_string(getPlayerObjectFlamesLeft()));

    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::getPlayerObjectHealth()
{
	return getPlayerObject()->getHP();
}

int StudentWorld::getPlayerObjectSpraysLeft()
{
	return getPlayerObject()->getNumOfSprayProjectiles();
}

int StudentWorld::getPlayerObjectFlamesLeft()
{
	return getPlayerObject()->getNumOfFlameThrowerCharges();
}
void StudentWorld::removeDeadActors()
{
	vector<ActorBaseClass*>::iterator it;
	for (it = ActorsVector.begin(); it != ActorsVector.end(); )
	{
		if ((*it)->getAliveStatus() == false)
		{
			delete* it;
			it = ActorsVector.erase(it);

		}
		else
		{
			it++;
		}
	}
}


int StudentWorld::getEuclideanDistance(double baseX, double baseY, double newX, double newY)
{
	double difX = abs((newX - baseX));
	double difY = abs((newY - baseY));
	double toSqrt = ((difX * difX) + (difY * difY));
	return sqrt(toSqrt);
}

ActorBaseClass* StudentWorld::getOverlappedActorPointer(ActorBaseClass* centerActor)
{
	vector<ActorBaseClass*>::iterator it;
	for (it = ActorsVector.begin(); it != ActorsVector.end(); it++)
	{

		int distanceToCenterActor = getEuclideanDistance(centerActor->getX(), centerActor->getY(), (*it)->getX(), (*it)->getY());
		if (distanceToCenterActor <= 8)
		{
			return *it;
		}
	}
}


void StudentWorld::cleanUp()
{
	delete playerObject;
	vector<ActorBaseClass*>::iterator it;
	for (it = ActorsVector.begin(); it != ActorsVector.end(); it++)
	{
		delete* it;
	}
	ActorsVector.clear();
}

void StudentWorld::addToActorsVector(ActorBaseClass* actorToAdd)
{
	ActorsVector.push_back(actorToAdd);
}

StudentWorld::~StudentWorld()
{
	this->cleanUp();
}

Socrates* StudentWorld::getPlayerObject()
{
	return playerObject;
}
