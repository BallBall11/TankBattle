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
	IMAGE	picture;			//̹�˵���ͼ
	int		id;					//̹�˵�ID
	int		x;					//̹�˵�x����(��������)
	int		y;					//̹�˵�y����(��������)
	int		size_x;				//̹�˵�x��С
	int		size_y;				//̹�˵�y��С
	int		facing;				//̹�˵ĳ���
	int		weapon_id;			//̹�˵�����ID
	int		blood;				//̹�˵�Ѫ��
	int		speed = 1;			//̹�˵��ٶ�
	int		cold_time = 0;		//������ȴʱ�䣬Ϊ����Թ���
	int		cannot_go;			//̹���ĸ���������
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
	IMAGE	picture;			//̹����ͼ
	int		size_x;				//̹�˵�x��С
	int		size_y;				//̹�˵�y��С
	int		blood;				//̹�˵�Ѫ��
	int		speed;				//̹�˵��ٶ�
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