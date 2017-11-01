#pragma once
typedef struct mVector
{
	float x = 0;
	float y = 0;
	float z = 0;
	mVector()
	{}
	mVector(float cx, float cy, float cz)
	{
		x = cx;
		y = cy;
		z = cz;
	}

	mVector operator*(float n)
	{
		mVector t=*this;
		t.x *= n;
		t.y*= n;
		t.z *= n;
		return t;
	}
	mVector operator+(mVector v)
	{
		mVector t=*this;
		t.x += v.x;
		t.y += v.y;
		t.z += v.z;
		return t;
	}

}mVector;

typedef struct Color
{
	float r = 0;
	float g = 0;
	float b = 0;
	float a = 1;
	Color()
	{}
	Color(float cr, float cg, float cb, float ca)
	{
		r = cr;
		g = cg;
		b = cb;
		a = ca;
	}

}Color;


class CGameObject
{
public:
	CGameObject();
	CGameObject(mVector p, mVector s, Color c, float sz);
	~CGameObject();
	int hp;
	void Tick(float dtime);
	mVector Pos;//위치 정보
	Color Col;//컬러 값.
	mVector Speed;//속도
	int number;
	float size;//둘중하나 쓰자 정사각형이면 사이즈 아니면 가로세로
	
	float Width;//오브젝트의 가로길이
	float Height;//오브젝트의 세로길이

	bool Delobj = false;

	float totalDtime = 0;

};
