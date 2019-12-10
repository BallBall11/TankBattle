#pragma once
#ifndef TANK_INCLUDED
#define TANK_INCLUDED

#include"basic_define.h"
#include<easyx.h>
#include<graphics.h>
#include<conio.h>

#define MAX_TANK 2

#define WEAPON 0

#define WE_BASIC 0
#define WE_LASER 1
#define WE_EXPLOSION 2

#define HEAL 1

#define HE_SMALL 0
#define SMALL_HEALING_BLOOD 1
#define HE_BIG 1
#define BIG_HEALING_BLOOD 2

enum Direction_Cannot_Go {
	NONE = -1,
	UP, DOWN, LEFT, RIGHT,
	UP_DOWN, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT, LEFT_RIGHT,
	UP_DOWN_LEFT, UP_DOWN_RIGHT, UP_LEFT_RIGHT, DOWN_LEFT_RIGHT,
	UP_DOWN_LEFT_RIGHT
};

class TANK
{
private:
	IMAGE	picture;			//坦克的贴图
	int		id;					//坦克的ID
	int		x;					//坦克的x坐标(像素坐标)
	int		y;					//坦克的y坐标(像素坐标)
	int		size_x;				//坦克的x大小
	int		size_y;				//坦克的y大小
	int		facing;				//坦克的朝向
	int		weapon_id;			//坦克的武器ID
	int		blood;				//坦克的血量
	int		speed = 1;			//坦克的速度
	int		cold_time = 0;		//武器冷却时间，为零可以攻击
	int		cannot_go;			//坦克哪个方向不能走
public:
	TANK(
		int Iid,
		int Ix,
		int Iy,
		int Ifacing);
	TANK();
	bool	CanStand(int x, int y);
	void	Turning(int position);
	bool	Hurt(int hurt);
	void	Move();
	int		Speed() { return speed; }
	bool	CanMove();
	void 	Paint();
	void    TankClear();
	void	Shoot();
	bool	CanShoot();
	int		Getx();
	int		Gety();
	int		GetxEnd();
	int		GetyEnd();
	void	ChangeWeapon(int new_weapon_id);
	void	ChangeCannotGo(int new_cannot_go);
};

struct TANK_TYPE
{
	IMAGE	picture;			//坦克贴图
	int		size_x;				//坦克的x大小
	int		size_y;				//坦克的y大小
	int		blood;				//坦克的血量
	int		speed;				//坦克的速度
	TANK_TYPE(
		LPCTSTR	Lpictrue,
		int		Isize_x,
		int		Isize_y,
		int		Iblood,
		int		Ispeed
	)
	{
		loadimage(&picture, Lpictrue);
		size_x = Isize_x;
		size_y = Isize_y;
		blood = Iblood;
		speed = Ispeed;
	}
	TANK_TYPE()
	{
		picture = NULL;
		size_x = 0;
		size_y = 0;
		blood = 0;
		speed = 0;
	}
};


#endif