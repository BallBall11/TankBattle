#pragma once
#ifndef ENTITY_INCLUDED
#define ENTITY_INCLUDED
#include "TANK.h"

class ENTITY
{
private:
	int		id;				//ʵ���id
	int		type;			//ʵ�������
	int		x;				//ʵ���x����(��������)
	int		y;				//ʵ���y����(��������)
	int		size_x;			//ʵ���x��С
	int		size_y;			//ʵ���y��С
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