#include "TANK.h"

extern BLOCK* FindBlock(int index);

TANK_TYPE tank_type[MAX_TANK];
extern FLY_TYPE fly_type[MAX_FLY];

TANK::TANK(int Iid, int Ix, int Iy, int Ifacing)
{
	id = Iid;
	x = Ix;
	y = Iy;
	facing = Ifacing;
	picture = tank_type[id].picture;
	size_x = tank_type[id].size_x;
	size_y = tank_type[id].size_y;
	blood = tank_type[id].blood;
	speed = tank_type[id].speed;
	weapon_id = 0;
}
TANK::TANK()
{
	id = -1;
	x = y = facing = size_x = size_y = blood = speed = weapon_id = 0;
	picture = NULL;
}

void TANK::Turning(int position) { facing = position; }

bool TANK::Hurt(int hurt)
{
	blood -= hurt;
	return blood > 0;
}

void TANK::Move()
{
	/*x += dir[facing].x * speed;
	y += dir[facing].y * speed;*/
	for (int i = 0; i < speed; i++)		//我还是坚持我自己的Move函数
	{
		int xx = x + dir[facing].x;
		int yy = y + dir[facing].y;
		if (!CanStand(xx, yy)) break;
		x = xx;
		y = yy;
	}
}

void TANK::Paint()
{
#define PI 3.14159265
	IMAGE print_picture = NULL;
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

bool TANK::CanStand(int x, int y)
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

bool TANK::CanMove()
{
	return map[y + dir[facing].y][x + dir[facing].x].block->IsPassable();
}

void TANK::TankClear()
{
	clearrectangle(x, y, x + size_x, y + size_y);
}

void TANK::Shoot()
{
	int fly_x, fly_y;
	int fly_size_x = fly_type[weapon_id].size_x;
	int fly_size_y = fly_type[weapon_id].size_y;
	switch (facing)
	{
	case UP:
		fly_x = x + ChangeToPixel(size_x) / 2 - ChangeToPixel(fly_size_x) / 2;
		fly_y = y - ChangeToPixel(fly_size_y);
		break;
	case DOWN:
		fly_x = x + ChangeToPixel(size_x) / 2 - ChangeToPixel(fly_size_x) / 2;
		fly_y = y + ChangeToPixel(size_y);
		break;
	case LEFT:
		fly_x = x - ChangeToPixel(fly_size_x);
		fly_y = y + ChangeToPixel(size_y) / 2 - ChangeToPixel(fly_size_y) / 2;
		break;
	case RIGHT:
		fly_x = x + ChangeToPixel(size_x);
		fly_y = y + ChangeToPixel(size_y) / 2 - ChangeToPixel(fly_size_y) / 2;
		break;
	}
	InsertFly(weapon_id, fly_x, fly_y, facing);
}

bool TANK::CanShoot() { return !cold_time; }

int TANK::Getx() { return x; }
int TANK::Gety() { return y; }
int TANK::GetxEnd() { return x + size_x; }
int TANK::GetyEnd() { return y + size_y; }
void TANK::ChangeWeapon(int new_weapon_id) { weapon_id = new_weapon_id; }
void TANK::ChangeCannotGo(int new_cannot_go) { cannot_go = new_cannot_go; }