#include "stdio.h"
#include <iostream>
#include <string>
#include <vector>
#include "GameManager.h"
#include "Rover.h"
#include "RemotePilot.h"

int main()
{
	GameManager* gm = GameManager::getInstance();								//init GameManager
	gm->setArea(20,20);															//set map Area, set lenth and width

	Rover* rover1 = new Rover(Positions(0,0), 'N', "MMMMRMMMRMMMRLMMMR");		//init Rover object
	Rover* rover2 = new Rover(Positions(3,3), 'E', "MMRMRMMRRMRMLM");
	
	gm->addRover(rover1);														//add to GameManager, Unified handling   
	gm->addRover(rover2);

	printf("\n");
	gm->commandRoversMove();													//togethor move by command  

	getchar();
	return 0;
}