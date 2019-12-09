#include "ENTITY.h"
#include <graphics.h>

void ENTITY::GetEntity(TANK* tank)
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

void ENTITY::EntityClear() {
	clearrectangle(x, y, x + size_x, y + size_y);
}

int ENTITY::Getid() { return id; }
int ENTITY::Gettype() { return type; }
int ENTITY::Getx() { return x; }
int ENTITY::Gety() { return y; }
int ENTITY::GetxEnd() { return x + size_x; }
int ENTITY::GetyEnd() { return y + size_y; }