// TankBettle.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<cstdio>
#include<windows.h>
#include<conio.h>
#include<cstdlib>
#include<ctime>
#include<cstring>
#include"BLOCK.h"
#include"TANK.h"
#include"ENTITY.h"
#include"FLY.h"
#include"basic_define.h"

using namespace std;
int scr_x, scr_y;
extern BLOCK block_type[MAX_BLOCK];
static struct DATA
{
	int score;
	int num_enemy;
	int num_entity;
	int num_destroyed_basement;
}data;

void Print();
bool DataChange(TANK* a);
void Init();
void GenerateRandomMap();
void Begin();
void GenerateEnemy();
bool IsBase(int i, int j);
void PaintBackground(int i, int j);

int main()
{
	//DWORD mytime = 0;
	srand((unsigned int)time(NULL));
	initgraph((WIN_COL + 20) * BLOCK_SIZE, WIN_ROW * BLOCK_SIZE);
	Init();
	_getch();
	Begin();
	TANK me;
	me.Setup(0, MAX_MAP / 2, MAX_MAP - 2, UP);
	bool flash;
	while (1)
	{
		if (GetKeyState(VK_F2) < 0)
		{
			cleardevice();
			clearcliprgn();
			outtextxy(((WIN_COL + 20) / 2 - 2) * BLOCK_SIZE, (WIN_ROW / 3) * BLOCK_SIZE, _T("暂停"));
			
			while (1)
			{
				if (GetKeyState(VK_F2) > 0)
				{
					cleardevice();
					setlinecolor(RED);
					line((WIN_COL * 2 + 1) * BLOCK_SIZE / 2, 0, (WIN_COL * 2 + 1) * BLOCK_SIZE / 2, WIN_ROW * BLOCK_SIZE);
					setlinecolor(BLACK);
					outtextxy((WIN_COL + 1) * BLOCK_SIZE, (WIN_ROW / 4 - 2) * BLOCK_SIZE, _T("游戏状态："));
					outtextxy((WIN_COL + 1) * BLOCK_SIZE, (WIN_ROW / 4) * BLOCK_SIZE, _T("开始！"));
					outtextxy((WIN_COL + 1) * BLOCK_SIZE, (WIN_ROW / 4 + 3) * BLOCK_SIZE, _T("操作方法："));
					outtextxy((WIN_COL + 1) * BLOCK_SIZE, (WIN_ROW / 4 + 4) * BLOCK_SIZE, _T("方向键操作坦克"));
					outtextxy((WIN_COL + 1) * BLOCK_SIZE, (WIN_ROW / 4 + 5) * BLOCK_SIZE, _T("空格开火"));
					outtextxy((WIN_COL + 1) * BLOCK_SIZE, (WIN_ROW / 4 + 6) * BLOCK_SIZE, _T("F2暂停"));
					Print();
					break;
				}
			}
		}
		starttime = GetTickCount();
		static DWORD mytime = GetTickCount();
		if (mytime - starttime < 1000 / FPS) //帧率控制  20FPS
		{
			Sleep(1000 / FPS - (mytime - starttime));
		}
		flash = DataChange(&me);
		if (flash)
			Print();
		//moveshoot(&start, &dat);
		if (0)
		{
			Lose();
			break;
		}
		if (GetKeyState(VK_ESCAPE) < 0)
		{
			End();
			break;
		}
	}
	
	return 0;
}

void Init()
{
	//IMAGE test_picture;
	//loadimage(&test_picture, _T("resources\\block\\墙1.bmp"));
	LoadResources();
	setfillcolor(BLACK);
	TCHAR s1[] = _T("坦克大战");
	TCHAR s2[] = _T("开始游戏");

	settextstyle(BLOCK_SIZE, 0, _T("宋体"));
	outtextxy(((WIN_COL + 20) / 2 - 2) * BLOCK_SIZE, (WIN_ROW / 3) * BLOCK_SIZE, s1);
	outtextxy(((WIN_COL + 20) / 2 - 2) * BLOCK_SIZE, (WIN_ROW / 3 + 2) * BLOCK_SIZE, s2);

	//putimage(0, 0, &test_picture);
}

void Begin()
{
	GenerateRandomMap();
	//system("cls");
	cleardevice();
	scr_y = (MAX_MAP - 2) * BLOCK_SIZE + BLOCK_SIZE / 2;
	scr_x = (MAX_MAP / 2) * BLOCK_SIZE + BLOCK_SIZE / 2;
	//for (int i = 1; i < WIN_ROW ; i++)//界面搭建
	//{
	//	Gotoxy( WIN_COL, i);
	//	printf("|");
	//}
	setlinecolor(RED);
	line((WIN_COL * 2 + 1) * BLOCK_SIZE / 2, 0, (WIN_COL * 2 + 1) * BLOCK_SIZE / 2, WIN_ROW * BLOCK_SIZE);
	setlinecolor(BLACK);
	/*Gotoxy(WIN_COL + 1, WIN_ROW / 4 - 2); printf("游戏状态：");
	Gotoxy(WIN_COL + 1, WIN_ROW / 4); printf("开始！");
	Gotoxy(WIN_COL + 1, WIN_ROW / 4 + 3); printf("操作方法：");
	Gotoxy(WIN_COL + 1, WIN_ROW / 4 + 6); printf("方向键操作坦克");
	Gotoxy(WIN_COL + 1, WIN_ROW / 4 + 7); printf("空格开火");
	Gotoxy(WIN_COL + 1, WIN_ROW / 4 + 8); printf("@是你的坦克");
	Gotoxy(WIN_COL + 1, WIN_ROW / 4 + 9); printf("%%是墙体，你不能穿过，但可以破坏");
	Gotoxy(WIN_COL + 1, WIN_ROW / 4 + 10); printf("#是基岩，你不能穿过，且不能破坏");
	Gotoxy(WIN_COL + 1, WIN_ROW / 4 + 11); printf("T是TNT方块，破坏时会爆炸");
	Gotoxy(WIN_COL + 1, WIN_ROW / 4 + 12); printf("&是掩体，你可以穿过，且会被隐藏");
	Gotoxy(WIN_COL + 1, WIN_ROW / 4 + 13); printf("F2暂停");*/
	outtextxy((WIN_COL + 1) * BLOCK_SIZE, (WIN_ROW / 4 - 2) * BLOCK_SIZE, _T("游戏状态："));
	outtextxy((WIN_COL + 1) * BLOCK_SIZE, (WIN_ROW / 4) * BLOCK_SIZE, _T("开始！"));
	outtextxy((WIN_COL + 1) * BLOCK_SIZE, (WIN_ROW / 4 + 3) * BLOCK_SIZE, _T("操作方法："));
	outtextxy((WIN_COL + 1) * BLOCK_SIZE, (WIN_ROW / 4 + 4) * BLOCK_SIZE, _T("方向键操作坦克"));
	outtextxy((WIN_COL + 1) * BLOCK_SIZE, (WIN_ROW / 4 + 5) * BLOCK_SIZE, _T("空格开火"));
	outtextxy((WIN_COL + 1) * BLOCK_SIZE, (WIN_ROW / 4 + 6) * BLOCK_SIZE, _T("F2暂停"));
	//Resize(&show.before, WIN_COL * BLOCK_SIZE, WIN_ROW * BLOCK_SIZE);
	//Resize(&show.now, WIN_COL * BLOCK_SIZE, WIN_ROW * BLOCK_SIZE);
	

	Print();
}

bool DataChange(TANK * me)
{
	bool ans = 0;
	if (GetAsyncKeyState(VK_UP)   ) 
	{ 
		me->Turning(UP);
		//if (me->CanMove())
		{
			me -> Move();
			scr_y -= me->Speed();
		}
		ans = 1; 
	}
	if (GetAsyncKeyState(VK_LEFT) ) 
	{ 
		me->Turning(LEFT);
		//if (me->CanMove())
		{
			me->Move();
			scr_x -= me->Speed();
		}
		ans = 1;
	}
	if (GetAsyncKeyState(VK_DOWN) ) 
	{ 
		me->Turning(DOWN);
		//if (me->CanMove())
		{
			me->Move();
			scr_y += me->Speed();
		}
		ans = 1;
	}
	if (GetAsyncKeyState(VK_RIGHT) ) 
	{ 
		me->Turning(RIGHT);
		//if (me->CanMove())
		{
			me->Move();
			scr_x += me->Speed();
		}
		ans = 1;
	}
	return ans;
}

void Print()
{
	//system("cls");
	/*show.before = show.now;
	SetWorkingImage(&show.now);*/
	HRGN rgn = CreateRectRgn(0, 0, WIN_COL * BLOCK_SIZE, WIN_ROW * BLOCK_SIZE);
	setcliprgn(rgn);
	DeleteObject(rgn);	
	BeginBatchDraw();
	//cleardevice();

	int up		= scr_y / BLOCK_SIZE - WIN_ROW / 2;
	int down	= scr_y / BLOCK_SIZE + WIN_ROW / 2;
	int left	= scr_x / BLOCK_SIZE - WIN_COL / 2;
	int right	= scr_x / BLOCK_SIZE + WIN_COL / 2;
	for (int i = left; i <= right; i++)
		for (int j = up; j <= down; j++)
			if (IsInMap(i, j))
				map[i][j].block->Paint(i, j);
			else PaintBackground(i,j);
	EndBatchDraw();
	setcliprgn(NULL);
}

void GenerateRandomMap()
{
	for (int i = 0; i < MAX_MAP; i++)
	{
		map[i][0].block = &block_type[B_BEDROCK];
		map[i][MAX_MAP - 1].block = &block_type[B_BEDROCK];
		map[MAX_MAP - 1][i].block = &block_type[B_BEDROCK];
		map[0][i].block = &block_type[B_BEDROCK];
	}
	
	for(int i=1;i<MAX_MAP-1;i++)
		for (int j = 1; j < MAX_MAP - 1; j++)
		{
			if (IsBase(i, j)) { map[i][j].block = &block_type[B_BASEMENT]; continue; }
			int a = rand() % 40, b = 0;
			switch (a)
			{
			case 8:
			case 9:
				b = 1; break;
			case 10:
			case 11:
				b = 2; break;
			case 12:
			case 13:
				b = 3; break;
			case 14:
				b = 4; break;
			case 15:b = 5; break;
			case 16:
				b = 6; break;
			case 17:
			case 18:
				b = 7; break;
			case 19:
				b = 8; break;
			default:
				b = 0;
			}
			map[i][j].block = &block_type[b];
			//map[i][j] = map[i][j] & MASK_BLOCK ^ block_type[b].id;
		}
}

bool IsBase(int i, int j)
{
	if (j == 1 && (i == MAX_MAP / 4 || i == MAX_MAP / 2 || i == MAX_MAP * 3 / 4))return 1;
	if (i == 1 && (j == MAX_MAP / 4 || j == MAX_MAP / 2 || j == MAX_MAP * 3 / 4))return 1;
	if (i == MAX_MAP - 2 && (j == MAX_MAP / 4 || j == MAX_MAP / 2 || j == MAX_MAP * 3 / 4))return 1;
	return 0;
}

void GenerateEnemy()
{
	int tx = rand() / MAX_MAP, ty = rand() / MAX_MAP;

}

void PaintBackground(int i, int j)
{
	int top = ScreenY(j);
	int left = ScreenX(i);
	int right = max(ScreenX(i), (WIN_COL * 2 + 1) * BLOCK_SIZE / 2 - 1);
	fillrectangle(left, top, right, top + BLOCK_SIZE);
}
