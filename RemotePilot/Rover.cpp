#include "Rover.h"

int Rover::roverId = 1;
Rover::Rover()
{
	Rover(Positions(1,1), 'N', "M");
}
Rover::Rover(Positions p, char direction, string command)
{
	m_position = p;
	m_direction = direction;
	m_command = command;
	init();
}

Rover::~Rover(){}

void Rover::init()
{
	m_curCommand = 0;
	m_died = false;
	m_conflictLess = false;
	m_id = roverId++;
	m_gameManager = GameManager::getInstance();
	m_gameManager->setMapPositionWalkable(m_position, false);					//set init position can not walk
	m_conflicPos = new ConflictPosition();

	cout<< "init Rover_"<< m_id <<": Position( " << m_position.x << ", " << m_position.y<<")     "<< "Direction( " << m_direction << " )"<< endl;
}


/**
	M: walk straight one unit
	L: turn left 90 digree   
	R: turn right 90 digree   
	B: walk back one unit
*/
bool Rover::move()
{
	if( m_curCommand >= m_command.size() || m_died || m_conflictLess)	//if command over , Rover out-of-range or Infinite conflict reutrn;
	{
		m_died = true;
		return false;
	}

	bool waitFlag = false;												//judge if need to stay
	const char& ch = m_command[m_curCommand] ; 
	switch (ch)															//according command to move   
	{
	case 'M':
		{
			if(!walkStraight(true))										//if return false, mean has conflict with other Rover  
			{
				waitFlag = true;				
			}
			break;
		}
	case 'L':
		{
			turnLeft();
			break;
		}
	case 'R':
		{
			turnRight();
			break;
		}
	case 'B':
		{
			if(!walkStraight(true))
			{
				waitFlag = true;
			}
			break;
		}
	default:
		break;
	}

	cout<< "Rover_"<< m_id <<": Position( " << m_position.x << ", " << m_position.y<<")     "<< "Direction( " << m_direction << " )"<< endl;

	if(m_gameManager->checkWalkOutside(m_position))						//out of range check, if true stop move	
	{
		cout << "Rover_" <<m_id << " DEAD" << endl;
		m_died = true;
		return true;
	}

	if(!waitFlag)
	{
		++m_curCommand;
	}
	return true;
}


// 'N','S','E','W' each represent direction ¡°north¡±,¡°south¡±,¡°east¡±,¡°west¡±  
bool Rover::walkStraight(bool straight)
{
	int step = 1;
	if(!straight)
	{
		step *=-1;
	}

	Positions p = m_position;											//add a next position to to check if next position movable 
	switch (m_direction)
	{
	case 'N':
		p.y += step; 
		break;
	case 'S':
		p.y -= step; 
		break;
	case 'E':
		p.x += step; 
		break;
	case 'W':
		p.x -= step; 
		break;

	default:
		break;
	}

	if(!m_gameManager->checkWalkOutside(p) && !m_gameManager->checkMapPositionWalkable(p))  //check conflict and out of range  
	{
		if(m_conflicPos->pos.equal(p))									//if is the old conflict Postion, add times   
		{
			m_conflicPos->times ++ ;
			if(m_conflicPos->times >= m_gameManager->m_rovers->size())	//if conflict time over all Rovers counts, stop it   
			{
				cout<< "Rover_"<<m_id <<": next_position has Rover, and it will conflict forever, so stop it!!!"<< endl;
				m_conflictLess = true;
			}
		}
		else{															//if is a new conflict position, reset it   
			m_conflicPos->pos = p;
			m_conflicPos->times = 1;
		}
		cout<< "Rover_"<<m_id <<": conflict Pos(" <<p.x<<" ,"<<p.y<<") || conflict times: " << m_conflicPos->times << endl;
		return false;
	}
	m_gameManager->setMapPositionWalkable(m_position,true);				//set the old position walkable  
	m_position = p;
	m_gameManager->setMapPositionWalkable(m_position,false);			//set the new position not walkable  
	return true;
}


void Rover::turnLeft()
{
	switch (m_direction)
	{
	case 'N':
		m_direction = 'W';
		break;
	case 'S':
		m_direction = 'E';
		break;
	case 'E':
		m_direction = 'N';
		break;
	case 'W':
		m_direction = 'S';
		break;

	default:
		break;
	}
}

void Rover::turnRight()
{
	switch (m_direction)
	{
	case 'N':
		m_direction = 'E';
		break;
	case 'S':
		m_direction = 'W';
		break;
	case 'E':
		m_direction = 'S';
		break;
	case 'W':
		m_direction = 'N';
		break;

	default:
		break;
	}
}

