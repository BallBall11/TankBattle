#include "basic_define.h"

std::list<class TANK>		list_tank;
std::list<class ENTITY>		list_entity;
std::list<class FLY>		list_fly;

void list_setup()			//请务必事先调用这个函数,建立链表用
{
	list_tank.resize(1);
	list_entity.resize(1);
	list_fly.resize(1);
}

void InsertTank(int id, int x, int y, int facing)
{
	list_tank.push_back(TANK(id, x, y, facing));
}

void InsertEntity(int id, int type, int x, int y)
{
	list_entity.push_back(ENTITY(id, type, x, y));
}

void InsertFly(int id, int x, int y, int facing)
{
	list_fly.push_back(FLY(id, x, y, facing));
}

void DeleteTank(std::list<class TANK>::iterator tank_iterator)
{
	list_tank.erase(tank_iterator);
}

void DeleteEntity(std::list<class ENTITY>::iterator entity_iterator)
{
	list_entity.erase(entity_iterator);
}

void DeleteFly(std::list<class FLY>::iterator fly_iterator)
{
	list_fly.erase(fly_iterator);
}
