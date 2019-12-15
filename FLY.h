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
	void	FillingFly();		//专门针对激光的Move函数的辅助函数

	bool	from_i;				//子弹是否来自我的坦克

public:
	FLY(
		int		Iid,
		int		Ix,
		int		Iy,
		int		Ifacing,
		bool	Bdisappearable = false);
	FLY();
	bool	CanStand(int x, int y);						//是否卡墙
	void	Turning(int position);						//转向
	void	Move(std::list<class FLY>::iterator ite_fly);
														//移动
	void	Paint();									//绘图
	bool	Clearable();								//是否可清除

	int		Getx();
	int		Gety();										//左上坐标的x,y值
	int		GetxEnd();
	int		GetyEnd();									//右下坐标的x,y值
	int		Getid();									//获取子弹id
	int		Getfacing();								//获取子弹方向
	bool	IsAlive();									//子弹是否存在
	bool	IsFromI();
	void	SetIterator(std::list<class FLY>::iterator ite_fly);
	void	ClearIterator(std::list<class FLY>::iterator ite_fly);
														//更新map
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