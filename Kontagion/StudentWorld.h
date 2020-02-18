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
	StudentWorld();
    StudentWorld(std::string assetPath);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
	~StudentWorld();

private:
	Socrates* playerObject;
	std::vector<ActorBaseClass*> ActorsVector;

};

#endif // STUDENTWORLD_H_
