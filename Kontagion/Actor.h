#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"
class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class ActorBaseClass : public GraphObject
{
public:
	//constructor
	ActorBaseClass(int imageID, double startX, double startY, Direction dir, int depth, StudentWorld* inputStudentWorld, int inputHP = 1);

	//Not sure if we have to implement these virtual functions from GraphObject
	////virtual function to move, MUST HAVE
	//virtual void moveTo(double x, double y);

	////virtual function, MUST HAVE
	//virtual void moveAngle(Direction angle, int units = 1);

	////virtual function, MUST HAVE
	//virtual void getPositionInThisDirection(Direction angle, int units, double& dx, double& dy);


	virtual void doSomething() = 0;

	virtual bool getAliveStatus();

	virtual void setAsDead();

	virtual StudentWorld* getStudentWorld();

	virtual ~ActorBaseClass();

	virtual double getHP();

	virtual bool SetAsDeadIfLessThan0HP();

	virtual void modifyHP(int modifyAmount);

	
	
	virtual bool sprayWillHarm();
	virtual bool flameWillHarm();



private:

	bool aliveStatus;
	StudentWorld* m_StudentWorld;
	double HP;
};

class DirtPile : public ActorBaseClass
{
public:
	DirtPile(double startX, double startY, StudentWorld* inputStudentWorld, int imageID = IID_DIRT, Direction dir = 0, int depth = 1);

	virtual void doSomething();

	virtual bool sprayWillHarm();

	virtual bool flameWillHarm();

private:
};

class Socrates : public ActorBaseClass
{
public:
	Socrates(StudentWorld* inputStudentWorld, int imageID = IID_PLAYER, Direction dir = 0, double startX = 0, double startY = 128, int depth = 0);

	void doSomething();

	int getPositionalAngle();

	void changePositionalAngle(int change);

	int getNumOfSprayProjectiles();

	int getNumOfFlameThrowerCharges();

	virtual void restoreSocratesFullHP();

	

private:
	int numOfSprayProjectiles;
	int numOfFlameThrowerCharges;
	int positionalAngle;

};

class SprayProjectile : public ActorBaseClass
{
public:
	SprayProjectile(double startX, double startY, StudentWorld* inputStudentWorld, int imageID = IID_SPRAY, Direction dir = 0, int depth = 1, int inputHP = 1);

	void doSomething();

private:
	int distanceTraveled;
};

class FlameProjectile : public ActorBaseClass
{
public:
	FlameProjectile(double startX, double startY, StudentWorld* inputStudentWorld, int imageID = IID_FLAME, Direction dir = 0, int depth = 1, int inputHP = 1);

	void doSomething();

private:
	int distanceTraveled;
};

class GoodieBaseClass : public ActorBaseClass
{
public:

	GoodieBaseClass(double startX, double startY, StudentWorld* inputStudentWorld, int imageID, Direction dir = 0, int depth = 1);

	virtual bool checkAliveAndIfOverlapWithSocrates();

	virtual void actionsIfOverlapWithSocrates(int pointsChange);
	virtual void trackAndDieIfExceedLifeTimeThenIncTick();

	virtual void incrementLifetimeTicksTracker();


private:
	int lifetimeTicksTracker;
	int ticksBeforeSetAsDead;
};

class RestoreHealthGoodie : public GoodieBaseClass
{
public:

	RestoreHealthGoodie(double startX, double startY, StudentWorld* inputStudentWorld, int imageID = IID_RESTORE_HEALTH_GOODIE, Direction dir = 0, int depth = 1);

	void doSomething();

private:
};
#endif // ACTOR_H_
