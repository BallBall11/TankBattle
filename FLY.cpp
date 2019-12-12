#include "FLY.h"
#include "BLOCK.h"
#include <graphics.h>

extern BLOCK* FindBlock(int index);

FLY_TYPE fly_type[MAX_FLY];

FLY::FLY(
	int Iid,
	int Ix,
	int Iy,
	int Ifacing
)
{
	id = Iid;
	picture = fly_type[id].picture;
	x = Ix;
	y = Iy;
	facing = Ifacing;
	size_x = fly_type[id].size_x;
	size_y = fly_type[id].size_y;
	speed = fly_type[id].speed;
	explosion_radium = fly_type[id].explosion_radium;
}
FLY::FLY()
{
	id = -1;
	x = y = facing = size_x = size_y = speed = 0;
}

void FLY::Turning(int position) { facing = position; }

void FLY::Move()
{
	int t_x = x, t_y = y;
	for (int i = 0; i < speed; i++)
	{
		t_x += dir[facing].x;
		t_y += dir[facing].y;
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
			if (!map[i][j].block->IsPassable()) return 0;
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

void FLY::Paint()
{
#define PI 3.14159265
	IMAGE print_picture ;
	switch (facing)
	{
	case UP:
		print_picture = picture;
		break;
	case DOWN:
		rotateimage(&print_picture, &picture, PI);
		break;
	case LEFT:
		rotateimage(&print_picture, &picture, PI / 2);
		break;
	case RIGHT:
		rotateimage(&print_picture, &picture, -PI / 2);
		break;
	}
	putimage(ScreenXPixel(x), ScreenYPixel(y), &print_picture);
#undef PI
}