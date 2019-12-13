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

	void	ClearIterator(std::list<class ENTITY>::iterator ite_entity);
public:
	ENTITY(
		int		Iid,
		int		Itype,
		int		Ix,
		int		Iy);
	ENTITY();
	void	GetEntity(
		std::list<class TANK>::iterator tank,
		std::list<class ENTITY>::iterator ite_entity);
													//坦克获得道具
	void	EntityClear();							//清除实体（不需要，直接调用GetEntity）
	int		Getid();								//获取实体id
	int		Gettype();								//获取实体类型
	int		Getx();
	int		Gety();									//左上坐标的x,y值
	int		GetxEnd();
	int		GetyEnd();								//右下坐标的x,y值
	void	SetIterator(std::list<class ENTITY>::iterator ite_entity);
													//更新map
};

struct ENTITY_TYPE
{
	IMAGE	picture;		//贴图
	IMAGE	picture_cover;	//掩图
	int		id;
	int		type;
};

#endif