#include "basic_define.h"
using namespace std;

void ITankCrash(list<class TANK>::iterator i_tank) { //我的坦克碰到子弹或方块
	int cell_x = i_tank->Getx() / BLOCK_SIZE, cell_y = i_tank->Gety() / BLOCK_SIZE;
	int cell_xe = i_tank->GetxEnd() / BLOCK_SIZE, cell_ye = i_tank->GetyEnd() / BLOCK_SIZE;
	int i;
	for (i = 0; i < cell_xe - cell_x; i++) {
		if (IsInMap(cell_x - 1, cell_y + i))
		{
			if (map[cell_x - 1][cell_y + i].fly != list_fly_null.end()
				&& map[cell_x - 1][cell_y + i].fly->IsAlive()
				&& map[cell_x - 1][cell_y + i].fly->Getfacing() == RIGHT)
			{
				DeleteFly(map[cell_x - 1][cell_y + i].fly);
				if (!(i_tank->Hurt(1))) {
					DeleteTank(i_tank);
					Lose();
				}
			}
			if (map[cell_x - 1][cell_y + i].block->Getid() && i_tank->Getfacing() == LEFT)
			{
				switch (map[cell_x - 1][cell_y + i].block->Getid())
				{
				case B_BASEMENT: i_tank->ChangeCannotGo(LEFT);
				case B_SHIELD: break;
				case B_BEDROCK: i_tank->ChangeCannotGo(LEFT); break;
				case B_TNT:
					map[cell_x - 1][cell_y + i].block->Explode(cell_x - 1, cell_y + i, 3, 5);
					DeleteTank(i_tank);
					Lose();
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
 		if (IsInMap(cell_x + 1, cell_y + i))
		{
			if (map[cell_x + 1][cell_y + i].fly != list_fly_null.end()
				&& map[cell_x + 1][cell_y + i].fly->IsAlive()
				&& map[cell_x + 1][cell_y + i].fly->Getfacing() == LEFT)
			{
				DeleteFly(map[cell_x + 1][cell_y + i].fly);
				if (!(i_tank->Hurt(1))) {
					DeleteTank(i_tank);
					Lose();
				}
			}
			if (map[cell_x + 1][cell_y + i].block->Getid() && i_tank->Getfacing() == RIGHT)
			{
				switch (map[cell_x + 1][cell_y + i].block->Getid())
				{
				case B_BASEMENT: i_tank->ChangeCannotGo(RIGHT);
				case B_SHIELD: break;
				case B_BEDROCK: i_tank->ChangeCannotGo(RIGHT); break;
				case B_TNT:
					map[cell_x + 1][cell_y + i].block->Explode(cell_x + 1, cell_y + i, 3, 5);
					DeleteTank(i_tank);
					Lose();
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
	}
	for (i = 0; i < cell_ye - cell_y; i++) {
		if (IsInMap(cell_x + i, cell_y - 1))
		{
			if (map[cell_x + i][cell_y - 1].fly != list_fly_null.end()
				&& map[cell_x + i][cell_y - 1].fly->IsAlive()
				&& map[cell_x + i][cell_y - 1].fly->Getfacing() == DOWN)
			{
				DeleteFly(map[cell_x + i][cell_y - 1].fly);
				if (!(i_tank->Hurt(1))) {
					DeleteTank(i_tank);
					Lose();
				}
			}
			if (map[cell_x + i][cell_y - 1].block->Getid() && i_tank->Getfacing() == UP)
			{
				switch (map[cell_x + i][cell_y - 1].block->Getid())
				{
				case B_BASEMENT: i_tank->ChangeCannotGo(UP);
				case B_SHIELD: break;
				case B_BEDROCK: i_tank->ChangeCannotGo(UP); break;
				case B_TNT:
					map[cell_x + i][cell_y - 1].block->Explode(cell_x + i, cell_y - 1, 3, 5);
					DeleteTank(i_tank);
					Lose();
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
  		if (IsInMap(cell_x + i, cell_y + 1))
		{
			if (map[cell_x + i][cell_y + 1].fly != list_fly_null.end()
				&& map[cell_x + i][cell_y + 1].fly->IsAlive()
				&& map[cell_x + i][cell_y + 1].fly->Getfacing() == UP)
			{
				DeleteFly(map[cell_x + i][cell_y + 1].fly);
				if (!(i_tank->Hurt(1))) {
					DeleteTank(i_tank);
					Lose();
				}
			}
			if (map[cell_x + i][cell_y + 1].block->Getid() && i_tank->Getfacing() == DOWN)
			{
				switch (map[cell_x + i][cell_y + 1].block->Getid())
				{
				case B_BASEMENT: i_tank->ChangeCannotGo(DOWN);
				case B_SHIELD: break;
				case B_BEDROCK: i_tank->ChangeCannotGo(DOWN); break;
				case B_TNT:
					map[cell_x + i][cell_y + 1].block->Explode(cell_x + i, cell_y + 1, 3, 5);
					DeleteTank(i_tank);
					Lose();
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
}

void EnemyTankCrash(list<class TANK>::iterator enemy_tank) { //敌方坦克碰到子弹或方块
	int cell_x = enemy_tank->Getx() / BLOCK_SIZE, cell_y = enemy_tank->Gety() / BLOCK_SIZE;
	int cell_xe = enemy_tank->GetxEnd() / BLOCK_SIZE, cell_ye = enemy_tank->GetyEnd() / BLOCK_SIZE;
	int i;
	for (i = 0; i < cell_xe - cell_x; i++) {
		if (IsInMap(cell_x - 1, cell_y + i))
		{
			if (map[cell_x - 1][cell_y + i].fly != list_fly_null.end()
				&& map[cell_x - 1][cell_y + i].fly->IsAlive()
				&& map[cell_x - 1][cell_y + i].fly->Getfacing() == RIGHT)
			{
				switch (map[cell_x - 1][cell_y + i].fly->Getid())
				{
				case WE_EXPLOSION: DeleteTank(enemy_tank); break;
				case WE_LASER:
					if (!(enemy_tank->Hurt(2))) DeleteTank(enemy_tank);
					break;
				case WE_BASIC:
					if (!(enemy_tank->Hurt(1))) DeleteTank(enemy_tank);
				}
				DeleteFly(map[cell_x - 1][cell_y + i].fly);
			}
			if (map[cell_x - 1][cell_y + i].block->Getid() && enemy_tank->Getfacing() == LEFT)
			{
				switch (map[cell_x - 1][cell_y + i].block->Getid())
				{
				case B_BASEMENT: enemy_tank->ChangeCannotGo(LEFT);
				case B_SHIELD: break;
				case B_BEDROCK: enemy_tank->ChangeCannotGo(LEFT); break;
				case B_TNT:
					map[cell_x - 1][cell_y + i].block->Explode(cell_x - 1, cell_y + i, 3, 5);
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
		if (IsInMap(cell_x + 1, cell_y + i))
		{
			if (map[cell_x + 1][cell_y + i].fly != list_fly_null.end()
				&& map[cell_x + 1][cell_y + i].fly->IsAlive()
				&& map[cell_x + 1][cell_y + i].fly->Getfacing() == LEFT)
			{
				switch (map[cell_x + 1][cell_y + i].fly->Getid())
				{
				case WE_EXPLOSION: DeleteTank(enemy_tank); break;
				case WE_LASER:
					if (!(enemy_tank->Hurt(2))) DeleteTank(enemy_tank);
					break;
				case WE_BASIC:
					if (!(enemy_tank->Hurt(1))) DeleteTank(enemy_tank);
				}
				DeleteFly(map[cell_x + 1][cell_y + i].fly);
			}
			if (map[cell_x + 1][cell_y + i].block->Getid() && enemy_tank->Getfacing() == RIGHT)
			{
				switch (map[cell_x + 1][cell_y + i].block->Getid())
				{
				case B_BASEMENT: enemy_tank->ChangeCannotGo(RIGHT);
				case B_SHIELD: break;
				case B_BEDROCK: enemy_tank->ChangeCannotGo(RIGHT); break;
				case B_TNT:
					map[cell_x + 1][cell_y + i].block->Explode(cell_x + 1, cell_y + i, 3, 5);
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
	}
	for (i = 0; i < cell_ye - cell_y; i++) {
		if (IsInMap(cell_x + i, cell_y - 1))
		{
			if (map[cell_x + i][cell_y - 1].fly != list_fly_null.end()
				&& map[cell_x + i][cell_y - 1].fly->IsAlive()
				&& map[cell_x + i][cell_y - 1].fly->Getfacing() == DOWN)
			{
				switch (map[cell_x + i][cell_y - 1].fly->Getid())
				{
				case WE_EXPLOSION: DeleteTank(enemy_tank); break;
				case WE_LASER:
					if (!(enemy_tank->Hurt(2))) DeleteTank(enemy_tank);
					break;
				case WE_BASIC:
					if (!(enemy_tank->Hurt(1))) DeleteTank(enemy_tank);
				}
				DeleteFly(map[cell_x + i][cell_y - 1].fly);
			}
			if (map[cell_x + i][cell_y - 1].block->Getid() && enemy_tank->Getfacing() == UP)
			{
				switch (map[cell_x + i][cell_y - 1].block->Getid())
				{
				case B_BASEMENT: enemy_tank->ChangeCannotGo(UP);
				case B_SHIELD: break;
				case B_BEDROCK: enemy_tank->ChangeCannotGo(UP); break;
				case B_TNT:
					map[cell_x + i][cell_y - 1].block->Explode(cell_x + i, cell_y - 1, 3, 5);
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
		if (IsInMap(cell_x + i, cell_y + 1))
		{
			if (map[cell_x + i][cell_y + 1].fly != list_fly_null.end()
				&& map[cell_x + i][cell_y + 1].fly->IsAlive()
				&& map[cell_x + i][cell_y + 1].fly->Getfacing() == UP)
			{
				switch (map[cell_x + i][cell_y + 1].fly->Getid())
				{
				case WE_EXPLOSION: DeleteTank(enemy_tank); break;
				case WE_LASER:
					if (!(enemy_tank->Hurt(2))) DeleteTank(enemy_tank);
					break;
				case WE_BASIC:
					if (!(enemy_tank->Hurt(1))) DeleteTank(enemy_tank);
				}
				DeleteFly(map[cell_x + i][cell_y + 1].fly);
			}
			if (map[cell_x + i][cell_y + 1].block->Getid() && enemy_tank->Getfacing() == DOWN)
			{
				switch (map[cell_x + i][cell_y + 1].block->Getid())
				{
				case B_BASEMENT: enemy_tank->ChangeCannotGo(DOWN);
				case B_SHIELD: break;
				case B_BEDROCK: enemy_tank->ChangeCannotGo(DOWN); break;
				case B_TNT:
					map[cell_x + i][cell_y + 1].block->Explode(cell_x + i, cell_y + 1, 3, 5);
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
}

void BlockCrash(BLOCK* block) { //方块碰到子弹
	int x = block->Getx(), y = block->Gety(), xe = block->GetxEnd(), ye = block->GetyEnd();
	int i;
	for (i = 0; i < xe - x; i++) {
		if (IsInMap(x - 1, y + i))
		{
			if (map[x - 1][y + i].fly->IsAlive() && map[x - 1][y + i].fly->Getfacing() == RIGHT)
				switch (block->Getid())
				{
				case B_BASEMENT:
					DeleteFly(map[x - 1][y + i].fly);
					if (map[x - 1][y + i].fly->IsFromI()) Win();
				case B_SHIELD: break;
				case B_BEDROCK: 
					DeleteFly(map[x - 1][y + i].fly);
					break;
				case B_TNT: break;
				case B_FIVE:
				case B_FOUR:
				case B_THREE:
				case B_TWO:
				case B_ONE:
					block = &block_type[block->Getid() - 1];
					DeleteFly(map[x - 1][y + i].fly);
				}
		}
		if (IsInMap(x + 1, y + i))
		{
			if (map[x + 1][y + i].fly->IsAlive() && map[x + 1][y + i].fly->Getfacing() == LEFT)
				switch (block->Getid())
				{
				case B_BASEMENT:
					DeleteFly(map[x + 1][y + i].fly);
					if (map[x + 1][y + i].fly->IsFromI()) Win();
				case B_SHIELD: break;
				case B_BEDROCK: 
					DeleteFly(map[x + 1][y + i].fly);
					break;
				case B_TNT: break;
				case B_FIVE:
				case B_FOUR:
				case B_THREE:
				case B_TWO:
				case B_ONE:
					block = &block_type[block->Getid() - 1];
					DeleteFly(map[x + 1][y + i].fly);
				}
		}
	}
	for (i = 0; i < ye - y; i++) {
		if (IsInMap(x + i, y - 1))
		{
			if (map[x + i][y - 1].fly->IsAlive() && map[x + i][y - 1].fly->Getfacing() == DOWN)
				switch (block->Getid())
				{
				case B_BASEMENT:
					DeleteFly(map[x + i][y - 1].fly);
					if (map[x + i][y - 1].fly->IsFromI()) Win();
				case B_SHIELD: break;
				case B_BEDROCK: 
					DeleteFly(map[x + i][y - 1].fly);
					break;
				case B_TNT: break;
				case B_FIVE:
				case B_FOUR:
				case B_THREE:
				case B_TWO:
				case B_ONE:
					block = &block_type[block->Getid() - 1];
					DeleteFly(map[x + i][y - 1].fly);
				}
		}
		if (IsInMap(x + i, y + 1))
		{
			if (map[x + i][y + 1].fly->IsAlive() && map[x + i][y + 1].fly->Getfacing() == UP)
				switch (block->Getid())
				{
				case B_BASEMENT:
					DeleteFly(map[x + i][y + 1].fly);
					if (map[x + i][y + 1].fly->IsFromI()) Win();
				case B_SHIELD: break;
				case B_BEDROCK: 
					DeleteFly(map[x + i][y + 1].fly);
				case B_TNT: break;
				case B_FIVE:
				case B_FOUR:
				case B_THREE:
				case B_TWO:
				case B_ONE:
					block = &block_type[block->Getid() - 1];
					DeleteFly(map[x + i][y + 1].fly);
				}
		}
	}
}