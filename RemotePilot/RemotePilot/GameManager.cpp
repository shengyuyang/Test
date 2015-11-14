
#include "GameManager.h"

GameManager* GameManager::m_instance = NULL;
GameManager* GameManager::getInstance()
{
	if(!m_instance)
	{
		m_instance = new GameManager();
	}
	return m_instance;
}

GameManager::GameManager()
{
	m_rovers = new vector<Rover* >;
	m_length = 0;
	m_width = 0;
	m_mapArea = nullptr;
}

GameManager::~GameManager()
{
	//cout<< "       ~GameManager      "<<endl;
	//cout<<"pro "<<m_rovers->capacity()<<endl;

	vector<Rover* >::iterator it = m_rovers->begin();
	while(it != m_rovers->end())
	{
		delete *it;
		it++;
	}
	m_rovers->clear();
	delete m_rovers;

	//cout<<"end "<<m_rovers->capacity()<<endl;

	for(int i=0;i<m_width;i++)
	{
		delete [] m_mapArea[i];
	}
	delete [] m_mapArea;
}

void GameManager::setArea(int l, int w)										//init m_mapArea  
{
	m_length = l;
	m_width = w;

	m_mapArea = new int*[m_length];				 
	for(int i=0; i<m_length;i++)
	{
		m_mapArea[i] = new int [m_width];
	}

	for(int i=0; i<m_length; i++)
	{
		for(int j=0; j<m_width; j++)
		{
			m_mapArea[i][j] = 0;
		}
	}
}

void GameManager::setMapPositionWalkable(Positions p, bool flag)
{
	if(checkWalkOutside(p))												//if position out of range ,return, if keep run, will make array error 
	{
		return;
	}
	if(flag)
	{
		m_mapArea[p.x][p.y]=0;
	}else
	{
		m_mapArea[p.x][p.y]=1;
	}
}

void GameManager::addRover(Rover* rover)
{
	m_rovers->push_back(rover);
}

bool GameManager::checkMapPositionWalkable(Positions p)
{
	return m_mapArea[p.x][p.y] == 0;
}

void GameManager::commandRoversMove()
{
	while(true)														//if has Rover move, keep run
	{
		bool continueFlag = false;
		vector<Rover* >::iterator it = m_rovers->begin();			//traverse all Rover   
		while( it != m_rovers->end())
		{
			Rover* rover = (Rover*)*it;
			if(rover->move())										//if return move, has rover alive  
			{
				continueFlag = true;
			}
			it++;
		}

		if(!continueFlag)											//if all Rover died ,return, stop game  
		{
			break;
		}
	}
}

bool GameManager::checkWalkOutside(Positions p)
{
	if(p.x < 0 || p.x >=m_length || p.y < 0 || p.y >= m_width)		//judge this Rover out of range   
	{
		return true;
	}
	return false;
}