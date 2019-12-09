#include<iostream>
#include "BLOCK.h"
#include "basic_define.h"

BLOCK block_type[MAX_BLOCK];
//{
//	{_T("resources\\block\\路.png"),	B_SPACE		, 1, 1, 0, 0, 0, false, true , false },
//	{_T("resources\\block\\墙1.png"),	B_ONE		, 1, 1, 0, 0, 0, false, false, false },
//	{_T("resources\\block\\墙2.png"),	B_TWO		, 1, 1, 0, 0, 1, false, false, false },
//	{_T("resources\\block\\墙3.png"),	B_THREE		, 1, 1, 0, 0, 2, false, false, false },
//	{_T("resources\\block\\墙4.png"),	B_FOUR		, 1, 1, 0, 0, 3, false, false, false },
//	{_T("resources\\block\\墙5.png"),	B_FIVE		, 1, 1, 0, 0, 4, false, false, false },
//	{_T("resources\\block\\TNT.png"),	B_TNT		, 1, 1, 3, 5, 0, true , false, false },
//	{_T("resources\\block\\基岩.png"),	B_BEDROCK	, 1, 1, 0, 0, 7, false, false, false },
//	{_T("resources\\block\\掩体.png"),	B_SHIELD	, 1, 1, 0, 0, 0, false, true , true  },
//	{_T("resources\\block\\路.png"),	B_BASEMENT	, 1, 1, 0, 0, 0, false, false, false }
//};

//BLOCK* map[MAX_MAP][MAX_MAP];

void BLOCK::Destroy(int x, int y, int harm)
{
	int ans = id;
	for (int i = 0; i < harm; i++)
		ans = block_type[ans].next_block_number;	//找harm次
	//map[x][y] = map[x][y] & MASK_BLOCK ^ block_type[ans].id;
	if (is_explosive) Explode(x, y, explosion_radium, explosion_forces);
}

void BLOCK::Explode(int x, int y, int r, int forces)
{
	int min_x = (x - r) > 0 ? x - r : 0;
	int min_y = (y - r) > 0 ? y - r : 0;
	int max_x = (x + r) < MAX_MAP ? x + r : MAX_MAP - 1;
	int max_y = (y + r) < MAX_MAP ? y + r : MAX_MAP - 1;
	for (int i = min_x; i <= max_x; i++)
		for (int j = min_y; j <= max_y; j++)
		{
			if (Check(i, j, x, y, r))
			{
				//map[i][j]->Destroy(i, j, forces);			
		//		block_type[map[i][j] & ~MASK_BLOCK].Destroy(i, j, forces);	//不简单递归
			}
		}
}

bool BLOCK::Check(int x1, int y1, int x2, int y2, int r)	//检查(x1,y1)和(x2,y2)之间的距离是不是<=r
{
	return r * r - (x1 - x2) * (x1 - x2) - (y1 - y2) * (y1 - y2) >= 0;
}

bool BLOCK::IsExplosive() { return is_explosive; }

bool BLOCK::IsPassable() { return is_passable; }

void BLOCK::Paint(int x, int y) { if(&picture!=NULL)putimage(ScreenX(x), ScreenY(y), &picture); }

BLOCK* FindBlock(int index)
{
	return &block_type[index & ~MASK_BLOCK];
}
BLOCK::BLOCK(
	LPCTSTR	Lway,
	int		Iid,
	int		Isize_x,
	int		Isize_y,
	int		Iexplosion_radium,
	int		Iexplosion_forces,
	int		Inext_block_number,
	bool	Bis_explosive,
	bool	Bis_passable,
	bool	Bis_cover
)
{
	loadimage(&picture, Lway);
	id = Iid;
	size_x = Isize_x;
	size_y = Isize_y;
	explosion_radium = Iexplosion_radium;
	explosion_forces = Iexplosion_forces;
	next_block_number = Inext_block_number;
	is_explosive = Bis_explosive;
	is_passable = Bis_passable;
	is_cover = Bis_cover;
}

void BLOCK::BlockClear(int x, int y) {
	clearrectangle(x * BLOCK_SIZE, y * BLOCK_SIZE, (x + size_x) * BLOCK_SIZE,
		(y + size_y) * BLOCK_SIZE);
}

int BLOCK::Getx(int x) { return x * BLOCK_SIZE; }
int BLOCK::Gety(int y) { return y * BLOCK_SIZE; }
int BLOCK::GetxEnd(int x) { return (x + size_x) * BLOCK_SIZE; }
int BLOCK::GetyEnd(int y) { return (y + size_y) * BLOCK_SIZE; }