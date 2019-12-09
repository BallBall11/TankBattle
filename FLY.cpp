#include "FLY.h"
#include "BLOCK.h"
#include "basic_define.h"
#include <graphics.h>

extern BLOCK* FindBlock(int index);

static struct FLY_TYPE
{
	int		size_x;				//子弹的x大小
	int		size_y;				//子弹的y大小
	int		speed;				//子弹的速度
};

static FLY_TYPE fly_type[MAX_FLY] =
{
	{1,1,2}
};

int FLY::Setup(int Iid, int Ix, int Iy, int Ifacing)
{
	if (Iid >= MAX_FLY) return -1;
	id = Iid;
	x = Ix;
	y = Iy;
	facing = Ifacing;
	size_x = fly_type[id].size_x;
	size_y = fly_type[id].size_y;
	speed = fly_type[id].speed;
	return 0;
}

void FLY::Turning(int position) { facing = position; }

void FLY::Move()
{
	int t_x = x, t_y = y;
	int move_x = 0, move_y = 0;
	switch (facing)
	{
	case UP:	move_x = -1; break;
	case DOWN:	move_x = +1; break;
	case LEFT:	move_y = -1; break;
	case RIGHT:	move_y = +1; break;
	}
	for (int i = 0; i < speed; i++)
	{
		t_x += move_x;
		t_y += move_y;
		if (!CanStand(t_x, t_y)) break;
		x = t_x;
		y = t_y;
	}
}

bool FLY::CanStand(int x, int y)
{
	int min_x = ChangeToScreen(x);
	int min_y = ChangeToScreen(y);
	int max_x = ChangeToScreen(x + size_x * BLOCK_SIZE - 1);
	int max_y = ChangeToScreen(y + size_y * BLOCK_SIZE - 1);
	for (int i = min_x; i <= max_x; i++)
		for (int j = min_y; j <= max_y; j++)
		{
			if (map[i][j].block->IsPassable()) return 0;
		}
	return 1;
}

void FLY::FlyClear() {
	switch (facing) {
	case DOWN: 
	case UP: clearrectangle(x, y, x + size_y, y + size_x); break;
	case RIGHT:
	case LEFT:clearrectangle(x, y, x + size_x, y + size_y);
	}
}

int FLY::Getx() { return x; }
int FLY::Gety() { return y; }
int FLY::GetxEnd() { return x + size_x; }
int FLY::GetyEnd() { return y + size_y; }
int FLY::Getid() { return id; }