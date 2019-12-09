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
	int		id;					//̹�˵�ID
	int		x;					//̹�˵�x����(��������)
	int		y;					//̹�˵�y����(��������)
	int		size_x;				//̹�˵�x��С
	int		size_y;				//̹�˵�y��С
	int		facing;				//̹�˵ĳ���
	int		weapon_id;			//̹�˵�����ID
	int		blood;				//̹�˵�Ѫ��
	int		speed = 1;			//̹�˵��ٶ�
	int		cannot_go;			//̹���ĸ���������
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