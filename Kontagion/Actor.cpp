#include "Actor.h"
#include "StudentWorld.h"
using namespace std;

class StudentWorld;

ActorBaseClass::ActorBaseClass(int imageID, double startX, double startY, Direction dir, int depth, double size, StudentWorld* inputStudentWorld)
	:GraphObject(imageID, startX, startY, dir, depth, size)
{
	aliveStatus = true;
	m_StudentWorld = inputStudentWorld;	
}
bool ActorBaseClass::getAliveStatus()
{
	return aliveStatus;
}

void ActorBaseClass::setAsDead()
{
	 aliveStatus = false;
}

StudentWorld* ActorBaseClass::getStudentWorld()
{
	return m_StudentWorld;
}

ActorBaseClass::~ActorBaseClass()
{}


////////////////////////////
//DIRTPILE IMPLEMENTATIONS
////////////////////////////


DirtPile::DirtPile(int imageID, double startX, double startY, Direction dir, int depth, double size, StudentWorld* inputStudentWorld)
	:ActorBaseClass(imageID, startX, startY, dir, depth, size, inputStudentWorld)
{}

void DirtPile::doSomething()
{}


Socrates::Socrates(int depth, double size, StudentWorld* inputStudentWorld)	//TODO: got rid of default parameters, unsure if we're supposed to
	: ActorBaseClass(IID_PLAYER, 0, 128, 0, depth, size, inputStudentWorld)
{
	hitPoints = 100;
	numOfSprayCharges = 20;
	numOfFlameThrowerCharges = 5;
}

int Socrates::getHitPoints()
{
	return hitPoints;
}
 

void Socrates::doSomething()
{

	if (!getAliveStatus())
	{
		return;
	}
	int ch;
	if (getStudentWorld()->getKey(ch))

	{
		switch (ch)
		{
			//TODO: THIS IMPLEMENTATION IS INCORRECT
		case KEY_PRESS_LEFT:
			this->moveTo(getX() - 5, getY());
			this->setDirection(getDirection() - 5);
		case KEY_PRESS_RIGHT:

			this->moveTo(getX() + 5, getY());
			this->setDirection(getDirection() + 5);
		case KEY_PRESS_SPACE:
			this->moveTo(getX() + 10, getY());
			this->setDirection(getDirection() - 20);
		}
	}
}
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
