#include "basic_define.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <easyx.h>

extern BLOCK		block_type[MAX_BLOCK];
extern TANK_TYPE	tank_type[MAX_TANK];
extern FLY_TYPE		fly_type[MAX_FLY];
extern WEAPON_DATA	weapon_data[MAX_WEAPON];

extern std::list<class TANK>	list_tank;
extern std::list<class ENTITY>	list_entity;
extern std::list<class FLY>		list_fly;
extern std::list<class TANK>	list_tank_null;
extern std::list<class ENTITY>	list_entity_null;
extern std::list<class FLY>		list_fly_null;

DWORD starttime;
DWORD START;

DIRECTION dir[4] = { {-1,0},{1,0},{0,-1},{0,1} };

CELL map[MAX_MAP][MAX_MAP];

extern int scr_x, scr_y;

int	ChangeToScreen(int x) { return x / BLOCK_SIZE; }
int ChangeToPixel(int x) { return x * BLOCK_SIZE; }

void End() 
{
	cleardevice();
	outtextxy(((WIN_COL + 20) / 2 - 2) * BLOCK_SIZE, (WIN_ROW / 3) * BLOCK_SIZE, _T("��Ϸ����"));
	_getch();
}

bool IsInMap(int i, int j)
{
	return i >= 0 && i < MAX_MAP && j >= 0 && j < MAX_MAP;
}

void Gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x; pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

int Tick(int interVal)
{
	DWORD time = GetTickCount();
	if (START - time % interVal == 0)
		return 1;
	else
		return 0;
}

int ScreenX(int x)
{
	return x * BLOCK_SIZE - scr_x + WIN_COL * BLOCK_SIZE / 2;
}

int ScreenY(int y)
{
	return y * BLOCK_SIZE - scr_y + WIN_ROW * BLOCK_SIZE / 2;
}

int ScreenXPixel(int x)
{
	return x - scr_x + WIN_COL * BLOCK_SIZE / 2;
}

int ScreenYPixel(int y)
{
	return y - scr_y + WIN_ROW * BLOCK_SIZE / 2;
}

void LoadResources()
{
	block_type[0] = BLOCK(_T("resources\\block\\·.gif"),  _T("resources\\block\\mask.gif"),		B_SPACE,	1, 1, 0, 0, 0, false, true , false);
	block_type[1] = BLOCK(_T("resources\\block\\ǽ1.gif"), _T("resources\\block\\mask.gif"),		B_ONE,		1, 1, 0, 0, 0, false, false, false);
	block_type[2] = BLOCK(_T("resources\\block\\ǽ2.gif"), _T("resources\\block\\mask.gif"),		B_TWO,		1, 1, 0, 0, 1, false, false, false);
	block_type[3] = BLOCK(_T("resources\\block\\ǽ3.gif"), _T("resources\\block\\mask.gif"),		B_THREE,	1, 1, 0, 0, 2, false, false, false);
	block_type[4] = BLOCK(_T("resources\\block\\ǽ4.gif"), _T("resources\\block\\mask.gif"),		B_FOUR,		1, 1, 0, 0, 3, false, false, false);
	block_type[5] = BLOCK(_T("resources\\block\\ǽ5.gif"), _T("resources\\block\\mask.gif"),		B_FIVE,		1, 1, 0, 0, 4, false, false, false);
	block_type[6] = BLOCK(_T("resources\\block\\TNT.gif"), _T("resources\\block\\mask.gif"),		B_TNT,		1, 1, 3, 5, 0, true , false, false);
	block_type[7] = BLOCK(_T("resources\\block\\����.gif"),_T("resources\\block\\mask.gif"),		B_BEDROCK,	1, 1, 0, 0, 7, false, false, false);
	block_type[8] = BLOCK(_T("resources\\block\\����.gif"),_T("resources\\block\\����_mask.gif"),	B_SHIELD,	1, 1, 0, 0, 0, false, true , true );
	block_type[9] = BLOCK(_T("resources\\block\\����.gif"),_T("resources\\block\\mask.gif"),		B_BASEMENT, 1, 1, 0, 0, 0, false, false, false);
	////////////////
	tank_type[0] = TANK_TYPE(_T("resources\\tank\\����̹��.gif"), _T("resources\\tank\\����̹��_mask.gif"), 3, 3, 1, 2);
	tank_type[1] = TANK_TYPE(_T("resources\\tank\\�з�̹��.gif"), _T("resources\\tank\\�з�̹��_mask.gif"), 3, 3, 1, 2);
	////////////////
	fly_type[0] = FLY_TYPE(_T("resources\\fly\\��ͨ.gif"), _T("resources\\fly\\��ͨ_mask.gif"), 1, 1, 5, 0);
	fly_type[1] = FLY_TYPE(_T("resources\\fly\\����.gif"), _T("resources\\fly\\����_mask.gif"), 1, 1, 3, 1);
	fly_type[2] = FLY_TYPE(_T("resources\\fly\\����.gif"), _T("resources\\fly\\����_mask.gif"), 1, 1, -1, 0);	//-1��ʾ˲ʱ
	////////////////
	////////////////
	weapon_data[0] = WEAPON_DATA(-1, 40, 1);
	weapon_data[1] = WEAPON_DATA(5, 80, 2);
	weapon_data[2] = WEAPON_DATA(3, 80, 1);

	ListSetup();
}

void Lose() {
	cleardevice();
	outtextxy(((WIN_COL + 20) / 2 - 2) * BLOCK_SIZE, (WIN_ROW / 3) * BLOCK_SIZE, _T("�����ˣ�"));
	_getch();
}

void Win() {
	cleardevice();
	outtextxy(((WIN_COL + 20) / 2 - 2) * BLOCK_SIZE, (WIN_ROW / 3) * BLOCK_SIZE, _T("��Ӯ�ˣ�"));
	_getch();
}

void LoadMap(const char* way)
{
	std::ifstream fp;
	fp.open(way, std::ios::in);
	int x, y, max_basement;
	fp >> y >> x >> max_basement;
	for (int i = 0; i < x; i++)
		for (int j = 0; j < y; j++)
		{
			int block_id;
			fp >> block_id;
			map[j][i].block = &block_type[block_id];
			map[j][i].entity = list_entity_null.end();
			map[j][i].fly = list_fly_null.end();
			map[j][i].tank = list_tank_null.end();
		}
	fp.close();
}
