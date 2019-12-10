#include "ENTITY.h"
#include <graphics.h>

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

void ENTITY::EntityClear()
{
	//clearrectangle(x, y, x + size_x, y + size_y);
}

int ENTITY::Getid() { return id; }
int ENTITY::Gettype() { return type; }
int ENTITY::Getx() { return x; }
int ENTITY::Gety() { return y; }
int ENTITY::GetxEnd() { return x + BLOCK_SIZE; }
int ENTITY::GetyEnd() { return y + BLOCK_SIZE; }