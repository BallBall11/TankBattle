#pragma once
#ifndef BASIC_DEFINE_INCLUDED
#define BASIC_DEFINE_INCLUDED

#define MAX_MAP 100		//��ͼ�ߴ�
#define WIN_COL 30		//��������
#define WIN_ROW 30		//��������
#define FPS 10			//��Ļˢ����


#define BLOCK_SIZE 16
//һ�����ӵ����ؿ��

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

extern DIRECTION dir[4];	//��������
extern CELL map[MAX_MAP][MAX_MAP];
extern DWORD starttime;
extern DWORD START;
extern BLOCK block_type[MAX_BLOCK];
extern std::list<class TANK>		list_tank;
extern std::list<class ENTITY>		list_entity;
extern std::list<class FLY>		list_fly;

int	ChangeToScreen(int x);
int ChangeToPixel(int x);

void Gotoxy(int x, int y);	//��Ļx����Ϊ�����꣬y����Ϊ������

int Tick(int interVal);

bool IsInMap(int i, int j);

void End();
void Lose();
void Win();

void ChangeMap(int i, int j, int B_ID);

int ScreenX(int x);					//���ظ�����Ͻ�X����
int ScreenY(int y);					//���ظ�����Ͻ�Y����
int ScreenXPixel(int x);			//���ص�ͼ����Ļ����������X
int ScreenYPixel(int y);			//���ص�ͼ����Ļ����������Y


void LoadResources();

void list_setup();

void InsertTank(int id, int x, int y, int facing);
void InsertEntity(int id, int type, int x, int y);
void InsertFly(int id, int x, int y, int facing);

void DeleteTank(std::list<class TANK>::iterator tank_iterator);
void DeleteEntity(std::list<class ENTITY>::iterator entity_iterator);
void DeleteFly(std::list<class FLY>::iterator fly_iterator);

#endif