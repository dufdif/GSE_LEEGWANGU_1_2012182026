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
	mVector Pos;//��ġ ����
	Color Col;//�÷� ��.
	mVector Speed;//�ӵ�
	int number;
	float size;//�����ϳ� ���� ���簢���̸� ������ �ƴϸ� ���μ���
	
	float Width;//������Ʈ�� ���α���
	float Height;//������Ʈ�� ���α���

	bool Delobj = false;

	float totalDtime = 0;

};
