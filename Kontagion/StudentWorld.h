#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "Actor.h"
#include "GameWorld.h"
#include "GraphObject.h"
#include <vector>
#include <iostream>
#include <string>

class Socrates;
class ActorBaseClass;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

//using Direction = int;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
	~StudentWorld();
	void addToActorsVector(ActorBaseClass* actorToAdd);
	Socrates* getPlayerObject();


	ActorBaseClass* getOverlappedActorPointer(ActorBaseClass* centerActor);

	//helper functions
	void removeDeadActors();
	int getPlayerObjectHealth();
	int getPlayerObjectSpraysLeft();
	int getPlayerObjectFlamesLeft();
	int getEuclideanDistance(double baseX, double baseY, double newX, double newY);
	
private:
	Socrates* playerObject;
	std::vector<ActorBaseClass*> ActorsVector;

};

#endif // STUDENTWORLD_H_
