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
	ActorBaseClass(int imageID, double startX, double startY, Direction dir, int depth, double size, StudentWorld* inputStudentWorld);

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

private:

	bool aliveStatus;
	StudentWorld* m_StudentWorld;

};

class DirtPile : public ActorBaseClass
{
public:
	DirtPile(int imageID, double startX, double startY, StudentWorld* inputStudentWorld, Direction dir = 90, int depth = 0, double size = 1);

	virtual void doSomething();

private:
};

class Socrates : public ActorBaseClass
{
public:
	Socrates(int depth, double size, StudentWorld* inputStudentWorld);

	void doSomething();

	int getPositionalAngle();

	void changePositionalAngle(int change);
	//void setAsDead();

	int Socrates::getHitPoints();

	//virtual bool getAliveStatus();

private:
	int hitPoints;
	int numOfSprayCharges;
	int numOfFlameThrowerCharges;
	int positionalAngle;

};
#endif // ACTOR_H_
