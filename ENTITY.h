#pragma once
#ifndef ENTITY_INCLUDED
#define ENTITY_INCLUDED

#define MAX_ENTITY 6
#include "basic_define.h"

class ENTITY
{
private:
	IMAGE	picture;			//��ͼ
	IMAGE	picture_cover;		//��ͼ
	int		id;					//ʵ���id
	int		type;				//ʵ�������
	int		x;					//ʵ���x����(��������)
	int		y;					//ʵ���y����(��������)
	bool	clearable = false;	//�ж��Ƿ�����
public:
	ENTITY(
		int		Iid,
		int		Itype,
		int		Ix,
		int		Iy);
	ENTITY();
	void	GetEntity(std::list<class TANK>::iterator tank);
													//̹�˻�õ���
	bool	Clearable() { return clearable; }		//�ж��Ƿ�����

	int		Getid();								//��ȡʵ��id
	int		Gettype();								//��ȡʵ������
	int		Getx();
	int		Gety();									//���������x,yֵ
	int		GetxEnd();
	int		GetyEnd();								//���������x,yֵ
	void	SetIterator(std::list<class ENTITY>::iterator ite_entity);
	void	ClearIterator(std::list<class ENTITY>::iterator ite_entity);
													//����map
};

struct ENTITY_TYPE
{
	IMAGE	picture;		//��ͼ
	IMAGE	picture_cover;	//��ͼ
	int		id;
	int		type;
};

#endif