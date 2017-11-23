#pragma once
#define LEVEL_GOD 0
#define LEVEL_SKY 0.1
#define LEVEL_GROUND 0.2
#define LEVEL_UNDERGROUND 0.3

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



enum Type
{
	character,building,bullet,arrow
};

class CGameObject
{
public:
	float Level;//����
	CGameObject();
	CGameObject(Type type,mVector p,bool enemy,  bool t = false,mVector s=mVector(0,0,0));
	CGameObject(mVector p, mVector s, Color c, float sz);
	~CGameObject();
	CGameObject* Master;
	float hp;
	float maxhp;
	void Tick(float dtime);
	mVector Pos;//��ġ ����
	Color Col;//�÷� ��.
	Color orgCol;//���� �÷���
	mVector Speed;//�ӵ�
	int number;
	float size;//�����ϳ� ���� ���簢���̸� ������ �ƴϸ� ���μ���
	
	float Width;//������Ʈ�� ���α���
	float Height;//������Ʈ�� ���α���

	bool Delobj = false;

	float totalDtime = 0;

	float Damage;

	bool Enemy;

	

	Type type;
	void SetMaster(CGameObject* m) { Master = m; }
	bool tex;
	

};
