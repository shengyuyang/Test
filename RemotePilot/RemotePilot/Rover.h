/********************************************************************
	created:	2015/11/13
	filename: 	Rover.h
	author:		shengyu.yang
	purpose:	Rover actor
*********************************************************************/

#ifndef  __Rover_H__
#define  __Rover_H__

#include "stdio.h"
#include <iostream>
#include <string>
#include <vector>
#include "GameManager.h"
#include "RemotePilot.h"

using namespace std;

class GameManager;
class Rover
{
public:
	Rover();
	~Rover();
	Rover(Positions p, char direction, string command);	//init position direction and move command   
	static int roverId;									//Rover unique id   

	void init();										//handle params init
	bool move();										//handle Rover move logic  
	bool walkStraight(bool straight);					//true:forward   false:backward     
	void turnLeft();									//direction turn to the left
	void turnRight();									//direction turn to the right
	GameManager* m_gameManager;							
public:
	Positions m_position;								//Rover cur position
	char m_direction;									//Rover cur direction
	string m_command;									//move command string
	int m_id;											//unique id  
	bool m_died;										//if died is true, stop move
	bool m_conflictLess;								//if two Rover`s posion or next position conficted, and confict times over than all Rover counts, stop move
	size_t m_curCommand;								//Rover according m_curCommand to move
	ConflictPosition* m_conflicPos;						//save the conflict position 
};

#endif
