#pragma once
typedef struct Vector
{
	float x = 0;
	float y = 0;
	float z = 0;
}Vector;

typedef struct Color
{
	float r = 0;
	float g = 0;
	float b = 0;
	float a = 1;
}Color;


class CGameObject
{
public:
	CGameObject();
	~CGameObject();

	Vector Pos;//��ġ ����
	Color Col;//�÷� ��.
	float Width;//������Ʈ�� ���α���
	float Height;//������Ʈ�� ���α���


};
