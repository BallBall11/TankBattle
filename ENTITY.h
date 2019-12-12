#pragma once
#ifndef ENTITY_INCLUDED
#define ENTITY_INCLUDED

#define MAX_ENTITY 6
#include "basic_define.h"

class ENTITY
{
private:
	IMAGE	picture;		//��ͼ
	IMAGE	picture_cover;	//��ͼ
	int		id;				//ʵ���id
	int		type;			//ʵ�������
	int		x;				//ʵ���x����(��������)
	int		y;				//ʵ���y����(��������)
public:
	ENTITY(
		int		Iid,
		int		Itype,
		int		Ix,
		int		Iy);
	ENTITY();
	void	GetEntity(std::list<class TANK>::iterator tank);
	void	EntityClear();
	int		Getid();
	int		Gettype();
	int		Getx();
	int		Gety();
	int		GetxEnd();
	int		GetyEnd();
};

struct ENTITY_TYPE
{

};

#endif