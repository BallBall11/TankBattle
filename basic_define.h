#pragma once
#ifndef BASIC_DEFINE_INCLUDED
#define BASIC_DEFINE_INCLUDED

#define MAX_MAP 100		//地图尺寸
#define WIN_COL 30		//窗口行数
#define WIN_ROW 30		//窗口列数
#define FPS 10			//屏幕刷新率

#define MASK_BLOCK	0xFFFFFFF0
#define MASK_TANK	0xFFFFF00F
#define MASK_ENTITY	0xFFFF0FFF
#define MASK_FLY	0xF000FFFF


#define BLOCK_SIZE 16
//一个格子的像素宽度

#include <graphics.h>
#include <list>
#include "BLOCK.h"
#include "TANK.h"
#include "ENTITY.h"
#include "FLY.h"

#define UP		0
#define DOWN	1
#define LEFT	2
#define RIGHT	3
struct DIRECTION
{
	int y, x;
};

struct CELL
{
	BLOCK* block;
	std::list<TANK>::iterator tank;
	std::list<ENTITY>::iterator entity;
	std::list<FLY>::iterator fly;
};

extern DIRECTION dir[4];	//方向数组，
extern CELL map[MAX_MAP][MAX_MAP];
extern DWORD starttime;
extern DWORD START;
extern std::list<TANK> list_tank;
extern std::list<ENTITY> list_entity;
extern std::list<FLY> list_fly;
extern BLOCK block_type[MAX_BLOCK];

int	ChangeToScreen(int x);
void Gotoxy(int x, int y);	//屏幕x坐标为列坐标，y坐标为行坐标
int Tick(int interVal);
bool IsInMap(int i, int j);
void End();
void Lose();
void Win();
void ChangeMap(int i, int j, int B_ID);
int ScreenX(int x);					//返回格点左上角X坐标
int ScreenY(int y);					//返回格点左上角Y坐标
void LoadResources();
#endif