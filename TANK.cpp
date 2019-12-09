#include "TANK.h"
#include "BLOCK.h"
#include "basic_define.h"
#include <graphics.h>

extern BLOCK* FindBlock(int index);

static struct TANK_TYPE
{
	int		size_x;				//坦克的x大小
	int		size_y;				//坦克的y大小
	int		blood;				//坦克的血量
	int		speed;				//坦克的速度
};

const TANK_TYPE tank_type[MAX_TANK] =
{
	{3,3,1,1}
};


int TANK::Setup(int Iid, int Ix, int Iy, int Ifacing)
{
	if (id >= MAX_TANK) return -1;
	id = Iid;
	x = Ix;
	y = Iy;
	facing = Ifacing;
	size_x = tank_type[id].size_x;
	size_y = tank_type[id].size_y;
	blood = tank_type[id].blood;
	speed = tank_type[id].speed;
	return 0;
}

void TANK::Turning(int position) { facing = position; }

bool TANK::Hurt(int hurt)
{
	blood -= hurt;
	return blood > 0;
}

void TANK::Move()
{
	x += dir[facing].x * speed;
	y += dir[facing].y * speed;
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

void TANK::TankClear() {
	clearrectangle(x, y, x + size_x, y + size_y);
}

int TANK::Getx() { return x; }
int TANK::Gety() { return y; }
int TANK::GetxEnd() { return x + size_x; }
int TANK::GetyEnd() { return y + size_y; }
void TANK::ChangeWeapon(int new_weapon_id) { weapon_id = new_weapon_id; }
void TANK::ChangeCannotGo(int new_cannot_go) { cannot_go = new_cannot_go; }