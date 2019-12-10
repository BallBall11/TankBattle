#include "BLOCK.h"
#include "ENTITY.h"
#include "FLY.h"
#include "TANK.h"
#include "basic_define.h"
#include <rpc.h>

int TankCrashBlock(TANK* tank, BLOCK* block, int block_x, int block_y) {
	int x = -1;
	if (tank->Gety() <= block->GetyEnd(block_y) && tank->Getx() <= block->GetxEnd(block_x)
		&& tank->GetxEnd() >= block->Getx(block_x)) 
	{
		x++;
	}
	if (tank->GetyEnd() >= block->Gety(block_y) && tank->Getx() <= block->GetxEnd(block_x)
		&& tank->GetxEnd() >= block->Getx(block_x)) 
	{
		x += 2;
	}
	if (tank->Getx() <= block->GetxEnd(block_x) && tank->Gety() <= block->GetyEnd(block_y)
		&& tank->GetyEnd() >= block->Gety(block_y)) 
	{
		x += 4;
	}
	if (tank->GetxEnd() >= block->Getx(block_x) && tank->Gety() <= block->GetyEnd(block_y)
		&& tank->GetyEnd() >= block->Gety(block_y)) 
	{
		x += 8;
	}
	switch (x) 
	{
	case 14:
	case 13: break;
	case 11: x = LEFT_RIGHT; break;
	case 10: x = UP_DOWN_RIGHT; break;
	case 9: x = DOWN_RIGHT; break;
	case 8: x = UP_RIGHT; break;
	case 7: x = RIGHT; break;
	case 6: x = UP_DOWN_LEFT; break;
	case 5: x = DOWN_LEFT; break;
	case 4: x = UP_LEFT; break;
	case 3: x = LEFT; break;
	case 2: x = UP_DOWN;
	}
	return x;
}

void TankCrashEntity(TANK* tank, ENTITY* entity) {
	if (tank->Getx() <= entity->GetxEnd() && tank->Gety() <= entity->GetyEnd() 
		&& tank->GetxEnd() >= entity->Getx() && tank->GetyEnd() >= entity->Gety())
	{
		switch (entity->Gettype())
		{
		case HEAL:
			switch (entity->Getid())
			{
			case BIG_HEALING_BLOOD: tank->Hurt(-2); break;
			case SMALL_HEALING_BLOOD: tank->Hurt(-1);
			}
			break;
		case WEAPON:
			tank->ChangeWeapon(entity->Getid());
		}
		entity->EntityClear();
	}
}

void ITankCrashEnemyFly(TANK* i_tank, FLY* enemy_fly) {
	if (i_tank->Getx() <= enemy_fly->GetxEnd() && i_tank->Gety() <= enemy_fly->GetyEnd() 
		&& i_tank->GetxEnd() >= enemy_fly->Getx() && i_tank->GetyEnd() >= enemy_fly->Gety())
	{
		enemy_fly->FlyClear();
		if (!(i_tank->Hurt(1))) 
		{
			i_tank->TankClear();
			Sleep(1000);
			Lose();
		}
	}
}

void ITankCrashBlock(TANK* i_tank, BLOCK* block, int block_x, int block_y) {
	int x = TankCrashBlock(i_tank, block, block_x, block_y);
	if (x != -1) 
	{
		switch (block->id) 
		{
		case B_BASEMENT: i_tank->ChangeCannotGo(x);
		case B_SHIELD: break;
		case B_BEDROCK: i_tank->ChangeCannotGo(x); break;
		case B_TNT:
			block->BlockClear(block_x, block_y);
			i_tank->TankClear();
			Sleep(1000);
			Lose();
			break;
		case B_FIVE:
		case B_FOUR:
		case B_THREE:
		case B_TWO:
		case B_ONE: i_tank->ChangeCannotGo(x);
		}
	}
	else i_tank->ChangeCannotGo(-1);
}

void IFlyCrashBlock(FLY* i_fly, BLOCK* block, int block_x, int block_y) {
	if (block->Getx(block_x) <= i_fly->GetxEnd() 
		&& block->Gety(block_y) <= i_fly->GetyEnd() 
		&& block->GetxEnd(block_x) >= i_fly->Getx() 
		&& block->GetyEnd(block_y) >= i_fly->Gety())
	{
		switch (block->id) 
		{
		case B_BASEMENT:
			i_fly->FlyClear();
			block->BlockClear(block_x, block_y);
			Sleep(1000);
			Win();
		case B_SHIELD: break;
		case B_BEDROCK: i_fly->FlyClear(); break;
		case B_TNT: break;
		case B_FIVE: 
		case B_FOUR:
		case B_THREE:
		case B_TWO:
		case B_ONE: 
			block = &block_type[block->id - 1];
			i_fly->FlyClear();
		}
	}
}

void EnemyTankCrashIFly(FLY* i_fly, TANK* enemy_tank) {
	if (enemy_tank->Getx() <= i_fly->GetxEnd() && enemy_tank->Gety() <= i_fly->GetyEnd() 
		&& enemy_tank->GetxEnd() >= i_fly->Getx() && enemy_tank->GetyEnd() >= i_fly->Gety())
	{
		switch (i_fly->Getid()) 
		{
		case WE_EXPLOSION: enemy_tank->TankClear(); break;
		case WE_LASER:
			if (!(enemy_tank->Hurt(2))) enemy_tank->TankClear();
			break;
		case WE_BASIC:
			if (!(enemy_tank->Hurt(1))) enemy_tank->TankClear();
		}
		i_fly->FlyClear();
	}
}

void EnemyTankCrashBlock(TANK* enemy_tank, BLOCK* block, int block_x, int block_y) {
	int x = TankCrashBlock(enemy_tank, block, block_x, block_y);
	if (x != -1)
	{
		switch (block->id)
		{
		case B_BASEMENT: enemy_tank->ChangeCannotGo(x);
		case B_SHIELD: break;
		case B_BEDROCK: enemy_tank->ChangeCannotGo(x); break;
		case B_TNT:
			block->BlockClear(block_x, block_y);
			enemy_tank->TankClear();
			break;
		case B_FIVE:
		case B_FOUR:
		case B_THREE:
		case B_TWO:
		case B_ONE: enemy_tank->ChangeCannotGo(x);
		}
	}
	else enemy_tank->ChangeCannotGo(-1);
}

void EnemyFlyCrashBlock(FLY* enemy_fly, BLOCK* block, int block_x, int block_y) {
	if (block->Getx(block_x) <= enemy_fly->GetxEnd() 
		&& block->Gety(block_y) <= enemy_fly->GetyEnd() 
		&& block->GetxEnd(block_x) >= enemy_fly->Getx() 
		&& block->GetyEnd(block_y) >= enemy_fly->Gety())
	{
		switch (block->id) 
		{
		case B_BASEMENT:
		case B_SHIELD: break;
		case B_BEDROCK: enemy_fly->FlyClear(); break;
		case B_TNT: break;
		case B_FIVE:
		case B_FOUR:
		case B_THREE:
		case B_TWO:
		case B_ONE:
			block = &block_type[block->id - 1];
			enemy_fly->FlyClear();
		}
	}
}