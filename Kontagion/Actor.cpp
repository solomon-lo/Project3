#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>
#include "math.h"
using namespace std;

class StudentWorld;

ActorBaseClass::ActorBaseClass(int imageID, double startX, double startY, Direction dir, int depth, StudentWorld* inputStudentWorld, int inputHP)
	:GraphObject(imageID, startX, startY, dir, depth)
{
	aliveStatus = true;
	m_StudentWorld = inputStudentWorld;	
	HP = inputHP;
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

int ActorBaseClass::getHP()
{
	return HP;
}

void ActorBaseClass::modifyHP(int modifyAmount)
{
	HP += modifyAmount;
}

bool ActorBaseClass::sprayWillHarm()
{
	return false;
}
bool ActorBaseClass::flameWillHarm()
{
	return false;
}

void ActorBaseClass::SetAsDeadIfLessThan0HP()
{
	if (getHP() <= 0)
	{
		setAsDead();
	}
}


////////////////////////////
//SOCRATES IMPLEMENTATIONS
////////////////////////////


Socrates::Socrates( StudentWorld* inputStudentWorld, int imageID, Direction dir, double startX, double startY, int depth)
	: ActorBaseClass(IID_PLAYER, 0, 128, 0, 0, inputStudentWorld, 100)
{
	numOfSprayProjectiles = 20;
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

int Socrates::getNumOfSprayProjectiles()
{
	return numOfSprayProjectiles;
}

int Socrates::getNumOfFlameThrowerCharges()
{
	return numOfFlameThrowerCharges;
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
		if (ch == KEY_PRESS_LEFT)
		{

			const double PI = 4 * atan(1);
			double newX = 128 + (128 * cos((getPositionalAngle() + 5.000000000) * 1.0 / 360 * 2 * PI));
			//cerr << "getpositionalnagle is" << getPositionalAngle() << endl;
			//cerr << "newX is" << newX << endl;
			double newY = 128 + (128 * sin((getPositionalAngle() + 5.000000000) * 1.0 / 360 * 2 * PI));
			//cerr << "newY is" << newY << endl;
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
			//cerr << "getpositionalnagle is" << getPositionalAngle() << endl;
			//cerr << "newX is" << newX << endl;
			double newY = 128 + (128 * sin((getPositionalAngle() - 5.00000) * 1.0 / 360 * 2 * PI));
			//cerr << "newY is" << newY << endl;
			moveTo(newX, newY);
			changePositionalAngle(-5);

			setDirection(getDirection() - 5);
		}

		if (ch == KEY_PRESS_SPACE)
		{
			if (numOfSprayProjectiles > 0)
			{
				double shotXDirection = 0;
				double shotYDirection = 0;
				getPositionInThisDirection(getDirection(), SPRITE_RADIUS * 2, shotXDirection, shotYDirection);
				SprayProjectile* shotSpray = new SprayProjectile(shotXDirection, shotYDirection,getStudentWorld() , 4, getDirection(), 1, 1);
				numOfSprayProjectiles--;
				getStudentWorld()->addToActorsVector(shotSpray);
				getStudentWorld()->playSound(SOUND_PLAYER_SPRAY);
			}

		}

		if (ch == KEY_PRESS_ENTER)
		{
			if (true)	//SHOULD HAVE numOfFlameThrowerCharges > 0
			{
				for (int i = 0; i < 16; i++)
				{
					cerr << "created flame" << i << endl;
					double shotXDirection = 0;
					double shotYDirection = 0;
					getPositionInThisDirection(22 * i, SPRITE_RADIUS * 2, shotXDirection, shotYDirection);
					FlameProjectile* shotFlame = new FlameProjectile(shotXDirection, shotYDirection, getStudentWorld(), IID_FLAME, 22 * i, 1, 1);
					getStudentWorld()->addToActorsVector(shotFlame);
				}
				numOfFlameThrowerCharges--;
				getStudentWorld()->playSound(SOUND_PLAYER_FIRE);
			}
		}
	}
	else
	{
		if (numOfSprayProjectiles < 20)
		{
			numOfSprayProjectiles++;
		}
	}
}

////////////////////////////
//DIRTPILE IMPLEMENTATIONS
////////////////////////////


DirtPile::DirtPile(double startX, double startY, StudentWorld* inputStudentWorld, int imageID, Direction dir, int depth)
	:ActorBaseClass(imageID, startX, startY, dir, depth, inputStudentWorld, 1)
{}

void DirtPile::doSomething()
{
	SetAsDeadIfLessThan0HP();
}


bool DirtPile::sprayWillHarm()
{
	return true;
}

bool DirtPile::flameWillHarm()
{
	return true;
}

////////////////////////////
//SPRAY IMPLEMENTATIONS
////////////////////////////

SprayProjectile::SprayProjectile(double startX, double startY, StudentWorld* inputStudentWorld, int imageID, Direction dir, int depth, int inputHP)
	:ActorBaseClass(imageID, startX, startY, dir, depth, inputStudentWorld, 1)
{
	distanceTraveled = 0;
}


void SprayProjectile::doSomething()
{
	//TODO:CHECK FOR OVERLAP
	SetAsDeadIfLessThan0HP();
	ActorBaseClass* temp = getStudentWorld()->getOverlappedActorPointer(this);
	if (temp != nullptr)
	{
		if (temp->sprayWillHarm() == true)
		{
			temp->setAsDead();
			this->setAsDead();
		}
	}
	moveAngle(getDirection(), SPRITE_RADIUS * 2);
	distanceTraveled += SPRITE_RADIUS * 2;
	//otherwise part(bullet point 3)

	if (distanceTraveled >= 112)
	{
		setAsDead();
	}
}

FlameProjectile::FlameProjectile(double startX, double startY, StudentWorld* inputStudentWorld, int imageID, Direction dir, int depth, int inputHP)
	:ActorBaseClass(imageID, startX, startY, dir, depth, inputStudentWorld, 1)
{
	distanceTraveled = 0;
}

void FlameProjectile::doSomething()
{
	//TODO:CHECK FOR OVERLAP
	SetAsDeadIfLessThan0HP();
	ActorBaseClass* temp = getStudentWorld()->getOverlappedActorPointer(this);
	if (temp != nullptr)
	{
		if (temp->flameWillHarm() == true)
		{
			temp->modifyHP(-5);
			this->setAsDead();
		}
	}
	moveAngle(getDirection(), SPRITE_RADIUS * 2);
	distanceTraveled += SPRITE_RADIUS * 2;

	if (distanceTraveled >= 32)
	{
		setAsDead();
	}
}
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp


GoodieBaseClass::GoodieBaseClass(double startX, double startY, StudentWorld* inputStudentWorld, int imageID = IID_RESTORE_HEALTH_GOODIE, Direction dir = 0, int depth = 1)
	:ActorBaseClass(imageID, startX, startY, dir, depth, inputStudentWorld)
{
	lifetimeTicksTracker = 0;
}

void GoodieBaseClass::checkAliveAndIfOverlapWithSocratesActions(int pointsChange, int soundPlayerSoundConstant)
{
	SetAsDeadIfLessThan0HP();

	StudentWorld* currentStudentWorldPointer = getStudentWorld();
	int distanceFromSocrates = currentStudentWorldPointer->getEuclideanDistance(currentStudentWorldPointer->getPlayerObject()->getX(), currentStudentWorldPointer->getPlayerObject()->getX(), getX(), getY());
	if (distanceFromSocrates < 2 * SPRITE_RADIUS)
	{
		currentStudentWorldPointer->increaseScore(pointsChange);
		setAsDead();
	}
	currentStudentWorldPointer->playSound(soundPlayerSoundConstant);
}
