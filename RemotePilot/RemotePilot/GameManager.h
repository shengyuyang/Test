/********************************************************************
	created:	2015/11/13
	filename: 	GameManager.h
	author:		shengyu.yang
	purpose:	manager game logic  
*********************************************************************/

#ifndef  __GameManager_H__
#define  __GameManager_H__

#include "stdio.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include "RemotePilot.h"
#include "Rover.h"


using namespace std;

class Rover;
class GameManager
{
public:
	~GameManager();
	static GameManager* getInstance();
	void setMapPositionWalkable(Positions p, bool flag);	//make the position walkable    
	bool checkMapPositionWalkable(Positions p);				//check the position walkable   
	void addRover(Rover* rover);							//add Rover to vector
	void commandRoversMove();								//run all Rover`s move action
	void setArea(int l, int w);								//set the game area   
	bool checkWalkOutside(Positions p);						//check move out of range  
public:
	int **m_mapArea;										//to help judge the position walkable , ps :0:no Rover ,1:has Rover
	vector<Rover* >* m_rovers;								//save all Rovers   
	int m_length, m_width;									//area range
private:
	GameManager();
	static GameManager* m_instance;
};

#endif // !1