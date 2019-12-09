#pragma once

#ifndef BLOCK_INCLUDED
#define BLOCK_INCLUDED

#include<easyx.h>
#include<graphics.h>
#include<conio.h>

#define B_SPACE		0x00000000
#define B_ONE		0x00000001
#define B_TWO		0x00000002
#define B_THREE		0x00000003
#define B_FOUR		0x00000004
#define B_FIVE		0x00000005
#define B_TNT		0x00000006
#define B_BEDROCK	0x00000007
#define B_SHIELD	0x00000008
#define B_BASEMENT	0x00000009
#define MAX_BLOCK	0x0000000A

class BLOCK
{
private:
	IMAGE	picture;
	int		size_x;						//x�����С
	int		size_y;						//y�����С
	int		explosion_radium;			//��ը�뾶
	int		explosion_forces;			//��ը����
	int		next_block_number;			//�ݻٺ��Ϊ�ķ���
	bool	is_explosive;				//�Ƿ�ɱ�ը
	bool	is_passable;				//��ͨ��
	bool	is_cover;					//�Ƿ������巽��

	void	Explode(int x, int y, int r, int forces);
	bool	Check(int x1, int y1, int x2, int y2, int r);
public:
	int		id;							//����ID
	void	Destroy(int x, int y, int harm = 1);
	bool	IsExplosive();
	bool	IsPassable();
	bool	IsCover() { return is_cover; }
	void	Paint(int x, int y);
	int		Getx(int x);
	int		Gety(int y);
	int		GetxEnd(int x);
	int		GetyEnd(int y);
	void	BlockClear(int x, int y);
	BLOCK(
		LPCTSTR	Lway,
		int		Iid,
		int		Isize_x,
		int		Isize_y,
		int		Iexplosion_radium,
		int		Iexplosion_forces,
		int		Inext_block_number,
		bool	Bis_explosive,
		bool	Bis_passable,
		bool	Bis_cover
	);
	BLOCK() {}
	
};

#endif