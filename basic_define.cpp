#include "basic_define.h"
#include"BLOCK.h"
#include <cstdio>
#include <cstdlib>
#include<graphics.h>
#include<easyx.h>

extern BLOCK block_type[MAX_BLOCK];
DWORD starttime;
DWORD START;
DIRECTION dir[4] = { {-1,0},{1,0},{0,-1},{0,1} };
CELL map[MAX_MAP][MAX_MAP];
extern int scr_x, scr_y;

int	ChangeToScreen(int x) { return x / BLOCK_SIZE; }

void End() {
	cleardevice();
	outtextxy(((WIN_COL + 20) / 2 - 2) * BLOCK_SIZE, (WIN_ROW / 3) * BLOCK_SIZE, _T("游戏结束"));
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
	return x * BLOCK_SIZE - scr_x + WIN_COL * BLOCK_SIZE/2;
}

int ScreenY(int y)
{
	return y * BLOCK_SIZE - scr_y + WIN_ROW * BLOCK_SIZE/2;
}

void LoadResources()
{
	block_type[0] = BLOCK(_T("resources\\block\\路.bmp"), B_SPACE, 1, 1, 0, 0, 0, false, true, false);
	block_type[1] = BLOCK(_T("resources\\block\\墙1.bmp"), B_ONE, 1, 1, 0, 0, 0, false, false, false);
	block_type[2] = BLOCK(_T("resources\\block\\墙2.bmp"), B_TWO, 1, 1, 0, 0, 1, false, false, false);
	block_type[3] = BLOCK(_T("resources\\block\\墙3.bmp"), B_THREE, 1, 1, 0, 0, 2, false, false, false);
	block_type[4] = BLOCK(_T("resources\\block\\墙4.bmp"), B_FOUR, 1, 1, 0, 0, 3, false, false, false);
	block_type[5] = BLOCK(_T("resources\\block\\墙5.bmp"), B_FIVE, 1, 1, 0, 0, 4, false, false, false);
	block_type[6] = BLOCK(_T("resources\\block\\TNT.bmp"), B_TNT, 1, 1, 3, 5, 0, true, false, false);
	block_type[7] = BLOCK(_T("resources\\block\\基岩.bmp"), B_BEDROCK, 1, 1, 0, 0, 7, false, false, false);
	block_type[8] = BLOCK(_T("resources\\block\\掩体.bmp"), B_SHIELD, 1, 1, 0, 0, 0, false, true, true);
	block_type[9] = BLOCK(_T("resources\\block\\基地.bmp"), B_BASEMENT, 1, 1, 0, 0, 0, false, false, false);
}

void Lose() {
	cleardevice();
	outtextxy(((WIN_COL + 20) / 2 - 2) * BLOCK_SIZE, (WIN_ROW / 3) * BLOCK_SIZE, _T("你输了！"));
	_getch();
}

void Win() {
	cleardevice();
	outtextxy(((WIN_COL + 20) / 2 - 2) * BLOCK_SIZE, (WIN_ROW / 3) * BLOCK_SIZE, _T("你赢了！"));
	_getch();
}
