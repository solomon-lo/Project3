#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>
#include <cmath>
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

double ActorBaseClass::getHP()
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

bool ActorBaseClass::SetAsDeadIfLessThan0HP()
{
	if (getHP() <= 0)
	{
		setAsDead();
		return true;
	}

	return false;
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

void Socrates::modifyNumOfFlameThrowerCharges(int changeAmount)
{
	numOfFlameThrowerCharges += changeAmount;
}

void Socrates::restoreSocratesFullHP()
{
	modifyHP(100 - getHP());
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
	bool temp = getStudentWorld()->wentOverSprayableObject(getX(), getY());
	if (temp == true)
	{
		this->setAsDead();
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
	bool temp = getStudentWorld()->wentOverSprayableObject(getX(), getY());
	if (temp == true)
	{
		this->setAsDead();
	}
	moveAngle(getDirection(), SPRITE_RADIUS * 2);
	distanceTraveled += SPRITE_RADIUS * 2;

	if (distanceTraveled >= 32)
	{
		setAsDead();
	}
}
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp


GoodieBaseClass::GoodieBaseClass(double startX, double startY, StudentWorld* inputStudentWorld, int imageID, Direction dir, int depth)
	:ActorBaseClass(imageID, startX, startY, dir, depth, inputStudentWorld)
{

	int randomTime = randInt(50, (300 - 10 * getStudentWorld()->getLevel()));
	cerr << "randomly generated" << randomTime << endl;
	lifetimeTicksTracker = 0;
	for (int i = 0; i < 20; i++)
	{
		randomTime = randInt(50, (300 - 10 * getStudentWorld()->getLevel()));
		cerr << "randomly generated" << randomTime << endl;
	}

	ticksBeforeSetAsDead = max(randomTime, 50);
	cerr << ticksBeforeSetAsDead << " is the time" << endl;
}

bool GoodieBaseClass::checkAliveAndIfOverlapWithSocrates()

{
	if (SetAsDeadIfLessThan0HP())
	{
		return false;
		cerr << "set as dead because under 1 HP" << endl;
	}

	StudentWorld* currentStudentWorldPointer = getStudentWorld();
	int distanceFromSocrates = currentStudentWorldPointer->getDistanceFromSocrates(this);
	if (distanceFromSocrates < 2 * SPRITE_RADIUS)
	{
		cerr << "overlapped" << endl;
		return true;
	}

	return false;
}

void GoodieBaseClass::baseActionsIfOverlapWithSocrates(int pointsChange)
{

	StudentWorld* currentStudentWorldPointer = getStudentWorld();
	currentStudentWorldPointer->increaseScore(pointsChange);
	setAsDead();
	currentStudentWorldPointer->playSound(SOUND_GOT_GOODIE);
}

void GoodieBaseClass::trackAndDieIfExceedLifeTimeThenIncTick()
{
	if (lifetimeTicksTracker >= ticksBeforeSetAsDead) 
	{
		setAsDead();
	}

	lifetimeTicksTracker++;
}


bool GoodieBaseClass::sprayWillHarm()
{
	return true;
}

bool GoodieBaseClass::flameWillHarm()
{
	return true;
}

RestoreHealthGoodie::RestoreHealthGoodie(double startX, double startY, StudentWorld* inputStudentWorld, int imageID, Direction dir, int depth)
	:GoodieBaseClass(startX, startY, inputStudentWorld, imageID, dir, depth)
{}

void RestoreHealthGoodie::doSomething()
{
	if (checkAliveAndIfOverlapWithSocrates())
	{
		//cerr << "overlppaed with soc and goodie" << endl;
		baseActionsIfOverlapWithSocrates(250);

		getStudentWorld()->makeSocratesFullHP();
		return;
	}

	trackAndDieIfExceedLifeTimeThenIncTick();
}

FlameThrowerGoodie::FlameThrowerGoodie(double startX, double startY, StudentWorld* inputStudentWorld, int imageID, Direction dir, int depth)
	:GoodieBaseClass(startX, startY, inputStudentWorld, imageID, dir, depth)
{}

void FlameThrowerGoodie::doSomething()
{
	if (checkAliveAndIfOverlapWithSocrates())
	{
		//cerr << "overlppaed with soc and goodie" << endl;
		baseActionsIfOverlapWithSocrates(300);

		getStudentWorld()->flameThrowerGoodieEffect();
		return;
	}

	trackAndDieIfExceedLifeTimeThenIncTick();
}

ExtraLifeGoodie::ExtraLifeGoodie(double startX, double startY, StudentWorld* inputStudentWorld, int imageID, Direction dir, int depth)
	:GoodieBaseClass(startX, startY, inputStudentWorld, imageID, dir, depth)
{}

void ExtraLifeGoodie::doSomething()
{
	if (checkAliveAndIfOverlapWithSocrates())
	{
		//cerr << "overlppaed with soc and goodie" << endl;
		baseActionsIfOverlapWithSocrates(500);

		getStudentWorld()->incLives();
		return;
	}

	trackAndDieIfExceedLifeTimeThenIncTick();
}

Fungus::Fungus(double startX, double startY, StudentWorld* inputStudentWorld, int imageID, Direction dir, int depth)
	:GoodieBaseClass(startX, startY, inputStudentWorld, imageID, dir, depth)
{}

void Fungus::doSomething()
{
	if (checkAliveAndIfOverlapWithSocrates())
	{
		//cerr << "overlppaed with soc and goodie" << endl;
		baseActionsIfOverlapWithSocrates(-50);

		getStudentWorld()->fungusEffect();
		return;
	}

	trackAndDieIfExceedLifeTimeThenIncTick();
}