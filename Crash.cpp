#include "basic_define.h"

using namespace std;
extern BLOCK block_type[MAX_BLOCK];

void ITankCrash(list<class TANK>::iterator i_tank) {
	int cell_x = i_tank->Getx / BLOCK_SIZE, cell_y = i_tank->Gety / BLOCK_SIZE;
	if (IsInMap(cell_x - 1, cell_y))
	{
		if (map[cell_x - 1][cell_y].fly->IsAlive()
			&& map[cell_x - 1][cell_y].fly->Getfacing() == RIGHT)
		{
			map[cell_x - 1][cell_y].fly->ClearIterator();
			if (!(i_tank->Hurt(1))) DeleteTank(i_tank);
		}
		if (map[cell_x - 1][cell_y].block->id && i_tank->Getfacing() == LEFT)
		{
			switch (map[cell_x - 1][cell_y].block->id)
			{
			case B_BASEMENT: i_tank->ChangeCannotGo(LEFT);
			case B_SHIELD: break;
			case B_BEDROCK: i_tank->ChangeCannotGo(LEFT); break;
			case B_TNT:
				map[cell_x - 1][cell_y].block->ChangeToSpace();
				DeleteTank(i_tank);
				break;
			case B_FIVE:
			case B_FOUR:
			case B_THREE:
			case B_TWO:
			case B_ONE: i_tank->ChangeCannotGo(LEFT);
			}
		}
		else i_tank->ChangeCanGo(LEFT);
	}
	if (IsInMap(cell_x + 1, cell_y))
	{
		if (map[cell_x + 1][cell_y].fly->IsAlive()
			&& map[cell_x + 1][cell_y].fly->Getfacing() == LEFT)
		{
			map[cell_x + 1][cell_y].fly->ClearIterator();
			if (!(i_tank->Hurt(1))) DeleteTank(i_tank);
		}
		if (map[cell_x + 1][cell_y].block->id && i_tank->Getfacing() == RIGHT)
		{
			switch (map[cell_x + 1][cell_y].block->id)
			{
			case B_BASEMENT: i_tank->ChangeCannotGo(RIGHT);
			case B_SHIELD: break;
			case B_BEDROCK: i_tank->ChangeCannotGo(RIGHT); break;
			case B_TNT:
				map[cell_x + 1][cell_y].block->ChangeToSpace();
				DeleteTank(i_tank);
				break;
			case B_FIVE:
			case B_FOUR:
			case B_THREE:
			case B_TWO:
			case B_ONE: i_tank->ChangeCannotGo(RIGHT);
			}
		}
		else i_tank->ChangeCanGo(RIGHT);
	}
	if (IsInMap(cell_x, cell_y - 1))
	{
		if (map[cell_x][cell_y - 1].fly->IsAlive()
			&& map[cell_x][cell_y - 1].fly->Getfacing() == DOWN)
		{
			map[cell_x][cell_y - 1].fly->ClearIterator();
			if (!(i_tank->Hurt(1))) DeleteTank(i_tank);
		}
		if (map[cell_x][cell_y - 1].block->id && i_tank->Getfacing() == UP)
		{
			switch (map[cell_x][cell_y - 1].block->id)
			{
			case B_BASEMENT: i_tank->ChangeCannotGo(UP);
			case B_SHIELD: break;
			case B_BEDROCK: i_tank->ChangeCannotGo(UP); break;
			case B_TNT:
				map[cell_x][cell_y - 1].block->ChangeToSpace();
				DeleteTank(i_tank);
				break;
			case B_FIVE:
			case B_FOUR:
			case B_THREE:
			case B_TWO:
			case B_ONE: i_tank->ChangeCannotGo(UP);
			}
		}
		else i_tank->ChangeCanGo(UP);
	}
	if (IsInMap(cell_x, cell_y + 1))
	{
		if (map[cell_x][cell_y + 1].fly->IsAlive()
			&& map[cell_x][cell_y + 1].fly->Getfacing() == UP)
		{
			map[cell_x][cell_y + 1].fly->ClearIterator();
			if (!(i_tank->Hurt(1))) DeleteTank(i_tank);
		}
		if (map[cell_x][cell_y + 1].block->id && i_tank->Getfacing() == DOWN)
		{
			switch (map[cell_x][cell_y + 1].block->id)
			{
			case B_BASEMENT: i_tank->ChangeCannotGo(DOWN);
			case B_SHIELD: break;
			case B_BEDROCK: i_tank->ChangeCannotGo(DOWN); break;
			case B_TNT:
				map[cell_x][cell_y + 1].block->ChangeToSpace();
				DeleteTank(i_tank);
				break;
			case B_FIVE:
			case B_FOUR:
			case B_THREE:
			case B_TWO:
			case B_ONE: i_tank->ChangeCannotGo(DOWN);
			}
		}
		else i_tank->ChangeCanGo(DOWN);
	}
}

void EnemyTankCrash(list<class TANK>::iterator enemy_tank) {
	int cell_x = enemy_tank->Getx / BLOCK_SIZE, cell_y = enemy_tank->Gety / BLOCK_SIZE;
	if (IsInMap(cell_x - 1, cell_y))
	{
		if (map[cell_x - 1][cell_y].fly->IsAlive()
			&& map[cell_x - 1][cell_y].fly->Getfacing() == RIGHT)
		{
			switch (map[cell_x - 1][cell_y].fly->Getid())
			{
			case WE_EXPLOSION: DeleteTank(enemy_tank); break;
			case WE_LASER:
				if (!(enemy_tank->Hurt(2))) DeleteTank(enemy_tank);
				break;
			case WE_BASIC:
				if (!(enemy_tank->Hurt(1))) DeleteTank(enemy_tank);
			}
			map[cell_x - 1][cell_y].fly->ClearIterator();
		}
		if (map[cell_x - 1][cell_y].block->id && enemy_tank->Getfacing() == LEFT)
		{
			switch (map[cell_x - 1][cell_y].block->id)
			{
			case B_BASEMENT: enemy_tank->ChangeCannotGo(LEFT);
			case B_SHIELD: break;
			case B_BEDROCK: enemy_tank->ChangeCannotGo(LEFT); break;
			case B_TNT:
				map[cell_x - 1][cell_y].block->ChangeToSpace();
				DeleteTank(enemy_tank);
				break;
			case B_FIVE:
			case B_FOUR:
			case B_THREE:
			case B_TWO:
			case B_ONE: enemy_tank->ChangeCannotGo(LEFT);
			}
		}
		else enemy_tank->ChangeCanGo(LEFT);
	}
	if (IsInMap(cell_x + 1, cell_y))
	{
		if (map[cell_x + 1][cell_y].fly->IsAlive()
			&& map[cell_x + 1][cell_y].fly->Getfacing() == LEFT)
		{
			switch (map[cell_x + 1][cell_y].fly->Getid())
			{
			case WE_EXPLOSION: DeleteTank(enemy_tank); break;
			case WE_LASER:
				if (!(enemy_tank->Hurt(2))) DeleteTank(enemy_tank);
				break;
			case WE_BASIC:
				if (!(enemy_tank->Hurt(1))) DeleteTank(enemy_tank);
			}
			map[cell_x + 1][cell_y].fly->ClearIterator();
		}
		if (map[cell_x + 1][cell_y].block->id && enemy_tank->Getfacing() == RIGHT)
		{
			switch (map[cell_x + 1][cell_y].block->id)
			{
			case B_BASEMENT: enemy_tank->ChangeCannotGo(RIGHT);
			case B_SHIELD: break;
			case B_BEDROCK: enemy_tank->ChangeCannotGo(RIGHT); break;
			case B_TNT:
				map[cell_x + 1][cell_y].block->ChangeToSpace();
				DeleteTank(enemy_tank);
				break;
			case B_FIVE:
			case B_FOUR:
			case B_THREE:
			case B_TWO:
			case B_ONE: enemy_tank->ChangeCannotGo(RIGHT);
			}
		}
		else enemy_tank->ChangeCanGo(RIGHT);
	}
	if (IsInMap(cell_x, cell_y - 1))
	{
		if (map[cell_x][cell_y - 1].fly->IsAlive()
			&& map[cell_x][cell_y - 1].fly->Getfacing() == DOWN)
		{
			switch (map[cell_x][cell_y - 1].fly->Getid())
			{
			case WE_EXPLOSION: DeleteTank(enemy_tank); break;
			case WE_LASER:
				if (!(enemy_tank->Hurt(2))) DeleteTank(enemy_tank);
				break;
			case WE_BASIC:
				if (!(enemy_tank->Hurt(1))) DeleteTank(enemy_tank);
			}
			map[cell_x][cell_y - 1].fly->ClearIterator();
		}
		if (map[cell_x][cell_y - 1].block->id && enemy_tank->Getfacing() == UP)
		{
			switch (map[cell_x][cell_y - 1].block->id)
			{
			case B_BASEMENT: enemy_tank->ChangeCannotGo(UP);
			case B_SHIELD: break;
			case B_BEDROCK: enemy_tank->ChangeCannotGo(UP); break;
			case B_TNT:
				map[cell_x][cell_y - 1].block->ChangeToSpace();
				DeleteTank(enemy_tank);
				break;
			case B_FIVE:
			case B_FOUR:
			case B_THREE:
			case B_TWO:
			case B_ONE: enemy_tank->ChangeCannotGo(UP);
			}
		}
		else enemy_tank->ChangeCanGo(UP);
	}
	if (IsInMap(cell_x, cell_y + 1))
	{
		if (map[cell_x][cell_y + 1].fly->IsAlive()
			&& map[cell_x][cell_y + 1].fly->Getfacing() == UP)
		{
			switch (map[cell_x][cell_y + 1].fly->Getid())
			{
			case WE_EXPLOSION: DeleteTank(enemy_tank); break;
			case WE_LASER:
				if (!(enemy_tank->Hurt(2))) DeleteTank(enemy_tank);
				break;
			case WE_BASIC:
				if (!(enemy_tank->Hurt(1))) DeleteTank(enemy_tank);
			}
			map[cell_x][cell_y + 1].fly->ClearIterator();
		}
		if (map[cell_x][cell_y + 1].block->id && enemy_tank->Getfacing() == DOWN)
		{
			switch (map[cell_x][cell_y + 1].block->id)
			{
			case B_BASEMENT: enemy_tank->ChangeCannotGo(DOWN);
			case B_SHIELD: break;
			case B_BEDROCK: enemy_tank->ChangeCannotGo(DOWN); break;
			case B_TNT:
				map[cell_x][cell_y + 1].block->ChangeToSpace();
				DeleteTank(enemy_tank);
				break;
			case B_FIVE:
			case B_FOUR:
			case B_THREE:
			case B_TWO:
			case B_ONE: enemy_tank->ChangeCannotGo(DOWN);
			}
		}
		else enemy_tank->ChangeCanGo(DOWN);
	}
}