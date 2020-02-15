#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class BaseClassForAll : public GraphObject
{
public:
	//constructor
	BaseClassForAll(int imageID, double startX, double startY, Direction dir = 0, int depth = 0, double size = 1.0) :
		GraphObject(imageID, startX, startY, dir, depth, size);

	//destructor
	virtual ~BaseClassForAll();

	//virtual function to move, MUST HAVE
	virtual void moveTo(double x, double y);

	//virtual function, MUST HAVE
	virtual void moveAngle(Direction angle, int units = 1);

	//virtual function, MUST HAVE
	virtual void getPositionInThisDirection(Direction angle, int units, double& dx, double& dy);


	virtual void doSomething() = 0;

	virtual bool isStillAlive();

private:

	bool is_alive_status;

};

class Socrates : public BaseClassForAll
{
public:
	Socrates(Direction dir = 180, int depth = 0, double size = 1.0);

	void doSomething();

	void setAsDead();

	int Socrates::getHitPoints();

	virtual bool getAliveStatus();

private:
	int hitPoints;
	int numOfSprayCharges;
	int numOfFlameThrowerCharges;
	bool aliveStatus;

};
#endif // ACTOR_H_
