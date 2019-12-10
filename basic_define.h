#pragma once
#ifndef BASIC_DEFINE_INCLUDED
#define BASIC_DEFINE_INCLUDED

#define MAX_MAP 100		//地图尺寸
#define WIN_COL 30		//窗口行数
#define WIN_ROW 30		//窗口列数
#define FPS 10			//屏幕刷新率


#define BLOCK_SIZE 16
//一个格子的像素宽度

#include <graphics.h>
#include <list>
#include "BLOCK.h"
#include "TANK.h"
#include "ENTITY.h"
#include "FLY.h"

struct DIRECTION
{
	int y, x;
};

struct CELL
{
	BLOCK* block;
	std::list<class TANK>::iterator tank;
	std::list<class ENTITY>::iterator entity;
	std::list<class FLY>::iterator fly;
};

extern DIRECTION dir[4];	//方向数组
extern CELL map[MAX_MAP][MAX_MAP];
extern DWORD starttime;
extern DWORD START;
extern BLOCK block_type[MAX_BLOCK];
extern std::list<class TANK>		list_tank;
extern std::list<class ENTITY>		list_entity;
extern std::list<class FLY>		list_fly;

int	ChangeToScreen(int x);
int ChangeToPixel(int x);

void Gotoxy(int x, int y);	//屏幕x坐标为列坐标，y坐标为行坐标

int Tick(int interVal);

bool IsInMap(int i, int j);

void End();
void Lose();
void Win();

void ChangeMap(int i, int j, int B_ID);

int ScreenX(int x);					//返回格点左上角X坐标
int ScreenY(int y);					//返回格点左上角Y坐标
int ScreenXPixel(int x);			//返回地图到屏幕的像素坐标X
int ScreenYPixel(int y);			//返回地图到屏幕的像素坐标Y


void LoadResources();

void list_setup();

void InsertTank(int id, int x, int y, int facing);
void InsertEntity(int id, int type, int x, int y);
void InsertFly(int id, int x, int y, int facing);

void DeleteTank(std::list<class TANK>::iterator tank_iterator);
void DeleteEntity(std::list<class ENTITY>::iterator entity_iterator);
void DeleteFly(std::list<class FLY>::iterator fly_iterator);

#endif