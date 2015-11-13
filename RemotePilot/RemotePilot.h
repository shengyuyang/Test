/********************************************************************
	created:	2015/11/13
	filename: 	RemotePilot.h
	author:		shengyu.yang
	purpose:	main
*********************************************************************/

#ifndef __RemotePilot_H__
#define __RemotePilot_H__

using namespace std ;

struct Positions{
	int x;
	int y;
	bool equal(Positions p){return (x==p.x) && (y==p.y);};
	Positions(int x=0,int y=0):x(x),y(y){}
};

struct ConflictPosition{
	Positions pos;
	int times;
	ConflictPosition(Positions x = Positions(-1,-1),unsigned int y=0):pos(x),times(y){}
};

#endif // !1