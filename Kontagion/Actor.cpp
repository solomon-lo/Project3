#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include <iostream>
#include <cmath>
#include<math.h>
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

bool ActorBaseClass::blocksBacteriumMovement() const
{
	return false;
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

bool ActorBaseClass::isEdible() const
{
	return false;
}
////////////////////////////
//SOCRATES IMPLEMENTATIONS
////////////////////////////


Socrates::Socrates(StudentWorld* inputStudentWorld, int imageID, Direction dir, double startX, double startY, int depth)
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

			double newY = 128 + (128 * sin((getPositionalAngle() + 5.000000000) * 1.0 / 360 * 2 * PI));

			moveTo(newX, newY);
			changePositionalAngle(5);

			setDirection(getDirection() + 5);
		}
		if (ch == KEY_PRESS_RIGHT)
		{
			const double PI = 4 * atan(1);
			double newX = 128 + (128 * cos((getPositionalAngle() - 5.00000) * 1.0 / 360 * 2 * PI));
			double newY = 128 + (128 * sin((getPositionalAngle() - 5.00000) * 1.0 / 360 * 2 * PI));

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
				SprayProjectile* shotSpray = new SprayProjectile(shotXDirection, shotYDirection, getStudentWorld(), 4, getDirection(), 1, 1);
				numOfSprayProjectiles--;
				getStudentWorld()->addToActorsVector(shotSpray);
				getStudentWorld()->playSound(SOUND_PLAYER_SPRAY);
			}

		}

		if (ch == KEY_PRESS_ENTER)
		{
			if (numOfFlameThrowerCharges > 0)	//SHOULD HAVE numOfFlameThrowerCharges > 0
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
	modifyHP(-1);
	return true;
}

bool DirtPile::flameWillHarm()
{
	return true;
}

bool DirtPile::blocksBacteriumMovement() const
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

Food::Food(double startX, double startY, StudentWorld* inputStudentWorld, int imageID, Direction dir, int depth, int inputHP)
	:ActorBaseClass(imageID, startX, startY, dir, depth, inputStudentWorld, inputHP)
{}

void Food::doSomething()
{}

bool Food::sprayWillHarm()
{
	return false;
}

bool Food::flameWillHarm()
{
	return false;
}

bool Food::isEdible() const
{
	return true;
}
GoodieBaseClass::GoodieBaseClass(double startX, double startY, StudentWorld* inputStudentWorld, int imageID, Direction dir, int depth)
	:ActorBaseClass(imageID, startX, startY, dir, depth, inputStudentWorld)
{

	int randomTime = randInt(50, (300 - 10 * getStudentWorld()->getLevel()));
	lifetimeTicksTracker = 0;
	for (int i = 0; i < 20; i++)
	{
		randomTime = randInt(50, (300 - 10 * getStudentWorld()->getLevel()));
	}

	ticksBeforeSetAsDead = max(randomTime, 50);
}

bool ActorBaseClass::checkAliveAndIfOverlapWithSocrates()

{

	int distanceFromSocrates = getStudentWorld()->getDistanceFromSocrates(this);
	if (distanceFromSocrates < 2 * SPRITE_RADIUS)
	{
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

//Bacteria Implementation

Bacteria::Bacteria(double startX, double startY, StudentWorld* inputStudentWorld, int imageID, Direction dir, int depth, int inputHP)
	:ActorBaseClass(imageID, startX, startY, dir, depth, inputStudentWorld, inputHP)
{
	foodEaten = 0;

	movementPlanDistance = 0;
}
void Bacteria::modifyFoodEaten(int modifyAmount)
{
	foodEaten += modifyAmount;
}

double Bacteria::newXAfter3Food(double inputX)
{
	if (inputX < VIEW_WIDTH / 2)
	{
		return inputX + SPRITE_RADIUS;
	}

	return inputX - SPRITE_RADIUS;
}

double Bacteria::newYAfter3Food(double inputY)
{
	if (inputY < VIEW_HEIGHT / 2)
	{
		return inputY + SPRITE_HEIGHT;
	}

	return inputY - SPRITE_HEIGHT;
}

bool Bacteria::sprayWillHarm()
{
	modifyHP(-2);
	return true;
}

bool Bacteria::flameWillHarm()
{
	modifyHP(-5);
	return true;
}

void Bacteria::modifyMovementPlanDistance(int modifyAmount)
{
	movementPlanDistance += modifyAmount;
}

int Bacteria::getMovementPlanDistance()
{
	return movementPlanDistance;
}

int Bacteria::getFoodEaten()
{
	return foodEaten;
}


void Bacteria::checkIfWentOverFoodAndIncrementIfSo()
{
	if (getStudentWorld()->wentOverFood(getX(), getY()))
	{
		cerr << "finally ate food" << endl;
		modifyFoodEaten(+1);
		return;
		cerr << "ate food" << endl;
		cerr << getFoodEaten() << endl;
	}
}

bool Bacteria::checkIfOverlappedWithSocratesAndModifySocratesHP(int socratesHPModifyAmount)
{
	if (checkAliveAndIfOverlapWithSocrates())
	{

		getStudentWorld()->modifySocratesHP(socratesHPModifyAmount);
		return true;	//tells socrates to take 1 damage	
	}
}

AggressiveSalmonella::AggressiveSalmonella(double startX, double startY, StudentWorld* inputStudentWorld, int imageID = IID_SALMONELLA, Direction dir = 90, int depth = 0, int inputHP = 10)
	:Bacteria(startX, startY, inputStudentWorld, dir, depth, inputHP)
{}

void AggressiveSalmonella::doSomething()
{
	
}

Salmonella::Salmonella(double startX, double startY, StudentWorld* inputStudentWorld, int imageID, Direction dir, int depth, int inputHP)
	:Bacteria(startX, startY, inputStudentWorld, imageID, dir, 0, 4)
{
}
void Salmonella::doSomething()
{
	SetAsDeadIfLessThan0HP();

	bool overlappedWithSocratesThisTick = false;
	bool hasDividedThisTick = false;

	overlappedWithSocratesThisTick = checkIfOverlappedWithSocratesAndModifySocratesHP(-1);

	if (!overlappedWithSocratesThisTick)
	{
		if (getFoodEaten() == 3)
		{
			int newX = newXAfter3Food(getX());
			int newY = newYAfter3Food(getY());
			getStudentWorld()->addToActorsVector(new Salmonella(newX, newY, getStudentWorld()));
			modifyFoodEaten(-3);
		}
		hasDividedThisTick = true;
	}

	if (!hasDividedThisTick && !overlappedWithSocratesThisTick)
	{

		checkIfWentOverFoodAndIncrementIfSo();
	}


	double possibleFoodX;
	double possibleFoodY;
	if (getMovementPlanDistance() > 0)
	{
		modifyMovementPlanDistance(-1);
		double tempX;
		double tempY;
		getPositionInThisDirection(getDirection(), 3, tempX, tempY);

		//following if statement checks to see if it DOESN'T go outside of circle or go over dirtpile
		if ((getStudentWorld()->getEuclideanDistance(tempX, tempY, (VIEW_WIDTH / 2), (VIEW_HEIGHT / 2)) > VIEW_DIAMETER) || (getStudentWorld()->wentOverDirtPile(tempX, tempY)))
		{
			int newDirection = randInt(0, 359);
			setDirection(newDirection);
			modifyMovementPlanDistance(10 - getMovementPlanDistance());

		}
		else
		{
			moveAngle(getDirection(), 3);
			//modifyMovementPlanDistance(-1);
		}
	}
	else
	{

		double newFoodX;
		double newFoodY;
		if (getStudentWorld()->findFoodWithin128(getX(), getY(), newFoodX, newFoodY))
		{
			const double PI = 4 * atan(1);
			double angle = (180.00000 / PI) * atan2(newFoodY - getY(), newFoodX - getX());
			//setDirection(angle);
			double newXAfterFoodFound;
			double newYAfterFoodFound;
			getPositionInThisDirection(angle, 3, newXAfterFoodFound, newYAfterFoodFound);
			if ((getStudentWorld()->getEuclideanDistance(newXAfterFoodFound, newYAfterFoodFound, (VIEW_WIDTH / 2), (VIEW_HEIGHT / 2)) > VIEW_DIAMETER) || getStudentWorld()->wentOverDirtPile(newXAfterFoodFound, newYAfterFoodFound))
			{
				int randomDirection = randInt(0, 359);
				setDirection(randomDirection);
				modifyMovementPlanDistance(10 - getMovementPlanDistance());
			}
			else
			{
				setDirection(angle);
				moveAngle(getDirection(), 3);
			}
		}
		else
		{
			int randomDirection = randInt(0, 359);
			setDirection(randomDirection);
			modifyMovementPlanDistance(10 - getMovementPlanDistance());
		}
	}
}


EColi::EColi(double startX, double startY, StudentWorld* inputStudentWorld, int imageID, Direction dir, int depth, int inputHP)
	:Bacteria(startX, startY, inputStudentWorld, imageID, dir, depth, inputHP)
{}

void EColi::doSomething()
{
	SetAsDeadIfLessThan0HP();

	bool overlappedWithSocratesThisTick = false;
	bool hasDividedThisTick = false;

	overlappedWithSocratesThisTick = checkIfOverlappedWithSocratesAndModifySocratesHP(-4);

	if (!overlappedWithSocratesThisTick)
	{
		if (getFoodEaten() >= 3)
		{
			int newX = newXAfter3Food(getX());
			int newY = newYAfter3Food(getY());
			getStudentWorld()->addToActorsVector(new EColi(newX, newY, getStudentWorld()));
			modifyFoodEaten(-1 * getFoodEaten());
		}
		hasDividedThisTick = true;
	}

	if (!hasDividedThisTick && !overlappedWithSocratesThisTick)
	{

		checkIfWentOverFoodAndIncrementIfSo();
	}

	//step 5

	double tempSocratesX;
	double tempSocratesY;
	if (getStudentWorld()->findSocratesWithin256(getX(), getY(), tempSocratesX, tempSocratesY))
	{
		const double PI = 4 * atan(1);
		double angle = (180.00000 / PI) * atan2(tempSocratesY - getY(), tempSocratesX - getX());
		
		for (int i = 0; i < 10; i++)
		{
			double newXChasingSocrates;
			double newYChasingSocrates;
			getPositionInThisDirection(angle,2, newXChasingSocrates, newYChasingSocrates);
			if (!(getStudentWorld()->getEuclideanDistance(newXChasingSocrates, newYChasingSocrates, (VIEW_WIDTH / 2), (VIEW_HEIGHT / 2)) > VIEW_DIAMETER) && !(getStudentWorld()->wentOverDirtPile(newXChasingSocrates, newYChasingSocrates)))
			{
				setDirection(angle);
				moveAngle(angle, 2);
				return;
			}
		}
			//TODO:IS THIS THE RIGHT WAY?
		
	}
}

