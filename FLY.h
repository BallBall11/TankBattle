#pragma once
#ifndef FLY_INCLUDED
#define FLY_INCLUDED

#include "basic_define.h"
#define MAX_FLY 3

class FLY
{
private:
	IMAGE	picture;			//子弹的贴图
	IMAGE	picture_cover;		//掩图
	int		id;					//子弹的ID
	int		x;					//子弹的x坐标(像素坐标)
	int		y;					//子弹的y坐标(像素坐标)
	int		size_x;				//子弹的x大小
	int		size_y;				//子弹的y大小
	int		facing;				//子弹的朝向
	int		speed;				//子弹的速度
	int		explosion_radium;	//子弹的爆破半径
	void	ClearIterator();
public:
	FLY(
		int Iid,
		int Ix,
		int Iy,
		int Ifacing);
	FLY();
	bool	CanStand(int x, int y);
	void	Turning(int position);
	void	Move();
	void	Paint();
	void    FlyClear();
	int		Getx();
	int		Gety();
	int		GetxEnd();
	int		GetyEnd();
	int		Getid();
	void	SetIterator(std::list<class FLY>::iterator ite_fly);
};

struct FLY_TYPE
{
	IMAGE	picture;			//子弹贴图
	IMAGE	picture_cover;		//掩体
	int		size_x;				//子弹的x大小
	int		size_y;				//子弹的y大小
	int		speed;				//子弹的速度
	int		explosion_radium;	//子弹的爆破半径			
	FLY_TYPE(
		LPCTSTR	Lpicture,
		LPCTSTR Lpicture_cover,
		int		Isize_x,
		int		Isize_y,
		int		Ispeed,
		int		Iexplosion_radium
	)
	{
		loadimage(&picture, Lpicture);
		loadimage(&picture_cover, Lpicture_cover);
		size_x = Isize_x;
		size_y = Isize_y;
		speed = Ispeed;
		explosion_radium = Iexplosion_radium;
	}
	FLY_TYPE()
	{
		picture = NULL;
		size_x = 0;
		size_y = 0;
		speed = 0;
	}
};

#endif