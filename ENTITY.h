#pragma once
#ifndef ENTITY_INCLUDED
#define ENTITY_INCLUDED
#include "TANK.h"

class ENTITY
{
private:
	int		id;				//实体的id
	int		type;			//实体的类型
	int		x;				//实体的x坐标(像素坐标)
	int		y;				//实体的y坐标(像素坐标)
	int		size_x;			//实体的x大小
	int		size_y;			//实体的y大小
public:
	void	GetEntity(TANK* tank);
	void	EntityClear();
	int		Getid();
	int		Gettype();
	int		Getx();
	int		Gety();
	int		GetxEnd();
	int		GetyEnd();
};

#endif