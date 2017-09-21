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

	Vector Pos;//위치 정보
	Color Col;//컬러 값.
	float Width;//오브젝트의 가로길이
	float Height;//오브젝트의 세로길이


};
