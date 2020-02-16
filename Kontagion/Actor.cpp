#include "Actor.h"
#include "StudentWorld.h"
using namespace std;

ActorBaseClass::ActorBaseClass(int imageID, double startX, double startY, Direction dir, int depth, double size, StudentWorld* inputStudentWorld)
	:GraphObject(imageID, startX, startY, dir, depth, size)
{
	aliveStatus = true;
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
	return m_gameWorld;
}



//Socrates::Socrates(Direction dir, int depth, double size)	//TODO: got rid of default parameters, unsure if we're supposed to
//	: ActorBaseClass(IID_PLAYER, 0, 128, dir, depth, size)
//{
//	hitPoints = 100;
//	numOfSprayCharges = 20;
//	numOfFlameThrowerCharges = 5;
//}
//
//int Socrates::getHitPoints()
//{
//	return hitPoints;
//}
//
//void Socrates::doSomething()
//{
//
//}
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
