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
#include "list.h"

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
int ScreenXPixel(int x);
int ScreenYPixel(int y);

void LoadResources();

void list_setup();

#endif