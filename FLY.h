#pragma once
#ifndef FLY_INCLUDED
#define FLY_INCLUDED

#define MAX_FLY 1

class FLY
{
private:
	int		id;					//�ӵ���ID
	int		x;					//�ӵ���x����(��������)
	int		y;					//�ӵ���y����(��������)
	int		size_x;				//�ӵ���x��С
	int		size_y;				//�ӵ���y��С
	int		facing;				//�ӵ��ĳ���
	int		speed;				//�ӵ����ٶ�
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