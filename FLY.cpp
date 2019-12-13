#include "FLY.h"
#include "BLOCK.h"
#include <graphics.h>

extern std::list<class FLY>	list_fly_null;

FLY_TYPE fly_type[MAX_FLY];

FLY::FLY(
	int Iid,
	int Ix,
	int Iy,
	int Ifacing
)
{
	id = Iid;
	x = Ix;
	y = Iy;
	facing = Ifacing;

	picture = fly_type[id].picture;
	picture_cover = fly_type[id].picture_cover;

	size_x = fly_type[id].size_x;
	size_y = fly_type[id].size_y;
	speed = fly_type[id].speed;
	explosion_radium = fly_type[id].explosion_radium;
}
FLY::FLY()
{
	id = -1;
	x = y = facing = size_x = size_y = speed = explosion_radium = 0;
	picture = picture_cover = NULL;
}

void FLY::Turning(int position) { facing = position; }

void FLY::Move(std::list<class FLY>::iterator ite_fly)
{
	std::list<class FLY>::iterator fly_iterator;
	fly_iterator = map[ChangeToScreen(x)][ChangeToScreen(y)].fly;
	ClearIterator(ite_fly);
	for (int i = 0; i < speed; i++)
	{
		int t_x = x + dir[facing].x;
		int t_y = y + dir[facing].y;
		if (!CanStand(t_x, t_y)) break;
		x = t_x;
		y = t_y;
	}
	SetIterator(fly_iterator);
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

void FLY::FlyClear(std::list<class FLY>::iterator ite_fly)
{
	/*switch (facing) 
	{
	case DOWN: 
	case UP: clearrectangle(x, y, x + size_y, y + size_x); break;
	case RIGHT:
	case LEFT:clearrectangle(x, y, x + size_x, y + size_y); break;
	}*/
	DeleteFly(ite_fly);
	ClearIterator(ite_fly);
}

void FLY::Paint()
{
#define PI 3.14159265
	IMAGE print_picture = NULL;
	IMAGE print_cover = NULL;
	switch (facing)
	{
	case UP:
		print_picture = picture;
		print_cover = picture_cover;
		break;
	case DOWN:
		rotateimage(&print_picture, &picture, PI, BLACK);
		rotateimage(&print_cover, &picture_cover, PI, WHITE);
		break;
	case LEFT:
		rotateimage(&print_picture, &picture, PI / 2, BLACK);
		rotateimage(&print_cover, &picture_cover, PI / 2, WHITE);
		break;
	case RIGHT:
		rotateimage(&print_picture, &picture, -PI / 2, BLACK);
		rotateimage(&print_cover, &picture_cover, -PI / 2, WHITE);
		break;
	}
	putimage(ScreenXPixel(x), ScreenYPixel(y), &print_cover, SRCAND);
	putimage(ScreenXPixel(x), ScreenYPixel(y), &print_picture, SRCPAINT);
#undef PI
}

int FLY::Getx() { return x; }
int FLY::Gety() { return y; }
int FLY::GetxEnd() { return x + size_x; }
int FLY::GetyEnd() { return y + size_y; }
int FLY::Getid() { return id; }

void FLY::SetIterator(std::list<class FLY>::iterator ite_fly)
{
	int min_x = ChangeToScreen(x);
	int min_y = ChangeToScreen(y);
	int max_x = ChangeToScreen(x + size_x * BLOCK_SIZE - 1);
	int max_y = ChangeToScreen(y + size_y * BLOCK_SIZE - 1);
	for (int i = min_x; i <= max_x; i++)
		for (int j = min_y; j <= max_y; j++)
			map[i][j].fly = ite_fly;
}

void FLY::ClearIterator(std::list<class FLY>::iterator ite_fly)
{
	int min_x = ChangeToScreen(x);
	int min_y = ChangeToScreen(y);
	int max_x = ChangeToScreen(x + size_x * BLOCK_SIZE - 1);
	int max_y = ChangeToScreen(y + size_y * BLOCK_SIZE - 1);
	for (int i = min_x; i <= max_x; i++)
		for (int j = min_y; j <= max_y; j++)
			if (map[i][j].fly == ite_fly) map[i][j].fly = list_fly_null.end();
}