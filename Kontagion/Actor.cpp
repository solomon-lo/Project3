#include "Actor.h"
#include "StudentWorld.h"


Socrates::Socrates(Direction dir = 180, int depth = 0, double size = 1.0) 
	: BaseClassForAll(IID_PLAYER, 0, 128, dir, depth, size)
{
	hitPoints = 100;
	numOfSprayCharges = 20;
	numOfFlameThrowerCharges = 5;
	aliveStatus = true;
}

int Socrates::getHitPoints()
{
	return hitPoints;
}

bool Socrates::getAliveStatus()
{
	return aliveStatus;
}

void Socrates::setAsDead()
{
	aliveStatus = false;
}
void Socrates::doSomething()
{
	if (!getAliveStatus)
	{
		return;
	}

}
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
