#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject()
{
	Width = 2;
	Height = 2;
	Col.r = 1;
	Pos.x = 0;
	Pos.y = 0;
	Pos.z = 0;
	size = 70;
	Speed.x = 1;
}

CGameObject::CGameObject(mVector p,mVector s,Color c,float sz)
{
	Width = 2;
	Height = 2;
	Col = c;
		Pos = p;
	size = sz;
	Speed = s;
}





CGameObject::~CGameObject()
{
}

void CGameObject::Tick(float dTime)
{
	Pos = Pos+Speed*dTime;

	if (Pos.x > 300)
		Pos.x = -300;
	Col.r = (float)(rand() % 101) / 100;
	Col.g = (float)(rand() % 201) / 200;
	Col.b = (float)(rand() % 301) / 300;

}

