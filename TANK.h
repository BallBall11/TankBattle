#pragma once
#ifndef TANK_INCLUDED
#define TANK_INCLUDED

#define MAX_TANK 1

#define WEAPON 0

#define WE_BASIC 0
#define WE_LASER 1
#define WE_EXPLOSION 2

#define HEAL 1

#define HE_SMALL 0
#define SMALL_HEALING_BLOOD 1
#define HE_BIG 1
#define BIG_HEALING_BLOOD 2

#include "FLY.h"

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
	char	shape;
	int		id;					//坦克的ID
	int		x;					//坦克的x坐标(像素坐标)
	int		y;					//坦克的y坐标(像素坐标)
	int		size_x;				//坦克的x大小
	int		size_y;				//坦克的y大小
	int		facing;				//坦克的朝向
	int		weapon_id;			//坦克的武器ID
	int		blood;				//坦克的血量
	int		speed = 1;			//坦克的速度
	int		cannot_go;			//坦克哪个方向不能走
	bool	CanStand(int x, int y);
public:
	int		Setup(int Iid, int Ix, int Iy, int Ifacing);
	void	Turning(int position);
	bool	Hurt(int hurt);
	void	Move();
	int		Speed() { return speed; }
	bool	CanMove();
	void 	Show();
	void    TankClear();
	int		Getx();
	int		Gety();
	int		GetxEnd();
	int		GetyEnd();
	void	ChangeWeapon(int new_weapon_id);
	void	ChangeCannotGo(int new_cannot_go);
};

#endif