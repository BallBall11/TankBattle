#pragma once
#ifndef LIST_INCLUDED
#define LIST_INCLUDED

#include "basic_define.h"
#include <vector>
#include <algorithm>

void InsertTank(int id, int x, int y, int facing);
void InsertEntity(int id, int type, int x, int y);
void InsertFly(int id, int x, int y, int facing, bool disappearable = false);

std::list<class TANK>::iterator		DeleteTank		(	std::list<class TANK>	::iterator	tank_iterator);
std::list<class ENTITY>::iterator	DeleteEntity	(	std::list<class ENTITY>	::iterator	entity_iterator);
std::list<class FLY>::iterator		DeleteFly		(	std::list<class FLY>	::iterator	fly_iterator);

#endif