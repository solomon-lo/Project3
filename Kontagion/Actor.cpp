#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>
#include "math.h"
using namespace std;

class StudentWorld;

ActorBaseClass::ActorBaseClass(int imageID, double startX, double startY, Direction dir, int depth, StudentWorld* inputStudentWorld)
	:GraphObject(imageID, startX, startY, dir, depth)
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
//SOCRATES IMPLEMENTATIONS
////////////////////////////


Socrates::Socrates( StudentWorld* inputStudentWorld, int imageID, Direction dir, double startX, double startY, int depth)
	: ActorBaseClass(IID_PLAYER, 0, 128, 0, 0, inputStudentWorld)
{
	hitPoints = 100;
	numOfSprayCharges = 20;
	numOfFlameThrowerCharges = 5;
	positionalAngle = 180;
}

int Socrates::getPositionalAngle()
{
	return positionalAngle;
}

void Socrates::changePositionalAngle(int change)
{
	positionalAngle += change;
	positionalAngle = positionalAngle % 360;
}

//int Socrates::getHitPoints()
//{
//	return hitPoints;
//}


void Socrates::doSomething()
{

	if (!getAliveStatus())
	{
		return;
	}
	int ch;
	if (getStudentWorld()->getKey(ch))
	{
		if (ch == KEY_PRESS_LEFT)
		{

			const double PI = 4 * atan(1);
			double newX = 128 + (128 * cos((getPositionalAngle() + 5.000000000) * 1.0 / 360 * 2 * PI));
			cerr << "getpositionalnagle is" << getPositionalAngle() << endl;
			cerr << "newX is" << newX << endl;
			double newY = 128 + (128 * sin((getPositionalAngle() + 5.000000000) * 1.0 / 360 * 2 * PI));
			cerr << "newY is" << newY << endl;
			moveTo(newX, newY);
			changePositionalAngle(5);

			//int premoveDegrees = getDirection();
			//int radianConversion = (premoveDegrees + 5) * 3.1415926f / 180.0f;
			//int newX = (120) * cos(radianConversion) + (128);
			//cerr << "newX is" << newX << endl;
			//int newY = (120) * sin((radianConversion) + (128));
			//cerr << "newY is" << newY << endl;
			//moveTo(newX, newY);
			setDirection(getDirection() + 5);
		}
		if (ch == KEY_PRESS_RIGHT)
		{
			const double PI = 4 * atan(1);
			double newX = 128 + (128 * cos((getPositionalAngle() - 5.00000) * 1.0 / 360 * 2 * PI));
			cerr << "getpositionalnagle is" << getPositionalAngle() << endl;
			cerr << "newX is" << newX << endl;
			double newY = 128 + (128 * sin((getPositionalAngle() - 5.00000) * 1.0 / 360 * 2 * PI));
			cerr << "newY is" << newY << endl;
			moveTo(newX, newY);
			changePositionalAngle(-5);

			setDirection(getDirection() - 5);
		}
	}
}

////////////////////////////
//DIRTPILE IMPLEMENTATIONS
////////////////////////////


DirtPile::DirtPile(double startX, double startY, StudentWorld* inputStudentWorld, int imageID, Direction dir, int depth)
	:ActorBaseClass(imageID, startX, startY, dir, depth, inputStudentWorld)
{}

void DirtPile::doSomething()
{}


// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
