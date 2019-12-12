#pragma once
#ifndef ENTITY_INCLUDED
#define ENTITY_INCLUDED

#define MAX_ENTITY 6
#include "basic_define.h"

class ENTITY
{
private:
	IMAGE	picture;		//贴图
	IMAGE	picture_cover;	//掩图
	int		id;				//实体的id
	int		type;			//实体的类型
	int		x;				//实体的x坐标(像素坐标)
	int		y;				//实体的y坐标(像素坐标)
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