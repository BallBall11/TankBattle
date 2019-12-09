#pragma once
#ifndef FLY_INCLUDED
#define FLY_INCLUDED

#define MAX_FLY 1

class FLY
{
private:
	int		id;					//子弹的ID
	int		x;					//子弹的x坐标(像素坐标)
	int		y;					//子弹的y坐标(像素坐标)
	int		size_x;				//子弹的x大小
	int		size_y;				//子弹的y大小
	int		facing;				//子弹的朝向
	int		speed;				//子弹的速度
public:
	bool	CanStand(int x, int y);
	int		Setup(int Iid, int Ix, int Iy, int Ifacing);
	void	Turning(int position);
	void	Move();
	void    FlyClear();
	int		Getx();
	int		Gety();
	int		GetxEnd();
	int		GetyEnd();
	int		Getid();
};

#endif