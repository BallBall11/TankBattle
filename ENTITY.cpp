#include "ENTITY.h"
#include <graphics.h>

ENTITY_TYPE entity_type[MAX_ENTITY];
extern std::list<class ENTITY> list_entity_null;

void ENTITY::GetEntity(std::list<TANK>::iterator tank)
{
	switch (type)
	{
	case WEAPON:
		tank->ChangeWeapon(id);
		break;
	case HEAL:
		switch (id)
		{
		case HE_SMALL:
			tank->Hurt(-SMALL_HEALING_BLOOD);
			break;
		case HE_BIG:
			tank->Hurt(-BIG_HEALING_BLOOD);
			break;
		}
		break;
	}
	clearable = true;
}

ENTITY::ENTITY(
	int		Iid,
	int		Itype,
	int		Ix,
	int		Iy)
{
	id = Iid;
	type = Itype;
	x = Ix;
	y = Iy;
}
ENTITY::ENTITY()
{
	id = -1;
	type = -1;
	x = 0;
	y = 0;
}

int ENTITY::Getid() { return id; }
int ENTITY::Gettype() { return type; }
int ENTITY::Getx() { return x; }
int ENTITY::Gety() { return y; }
int ENTITY::GetxEnd() { return x + BLOCK_SIZE; }
int ENTITY::GetyEnd() { return y + BLOCK_SIZE; }

void ENTITY::SetIterator(std::list<class ENTITY>::iterator ite_entity)
{
	int min_x = ChangeToScreen(x);
	int min_y = ChangeToScreen(y);
	int max_x = ChangeToScreen(x + BLOCK_SIZE - 1);
	int max_y = ChangeToScreen(y + BLOCK_SIZE - 1);
	for (int i = min_x; i <= max_x; i++)
		for (int j = min_y; j <= max_y; j++)
			map[i][j].entity = ite_entity;
}

void ENTITY::ClearIterator(std::list<class ENTITY>::iterator ite_entity)
{
	int min_x = ChangeToScreen(x);
	int min_y = ChangeToScreen(y);
	int max_x = ChangeToScreen(x + BLOCK_SIZE - 1);
	int max_y = ChangeToScreen(y + BLOCK_SIZE - 1);
	for (int i = min_x; i <= max_x; i++)
		for (int j = min_y; j <= max_y; j++)
			/*if (map[i][j].entity == ite_entity) */map[i][j].entity = list_entity_null.end();
}