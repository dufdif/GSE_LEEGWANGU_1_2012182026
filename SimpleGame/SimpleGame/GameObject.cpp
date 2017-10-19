#include "stdafx.h"
#include "GameObject.h"
#include<time.h>
#include"Scene.h"
extern Scene myscene;
CGameObject::CGameObject()
{
	Width = 0.01;
	Height = 0.01;
	Col = Color(1, 1, 1, 1);
	Pos.x = 0;
	Pos.y = 0;
	Pos.z = 0;
	size = 7;
	
	Speed.x = rand()%9-5;
	Speed.y = rand() % 9-5;

	if (Speed.x == 0 && Speed.y == 0)
		Speed.y = 3;

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

	if (Pos.x > 250)
	{
		Col.r = 1;
		Speed.x = -Speed.x;
		Speed.y = rand() % 9 - 5;
	}

	if (Pos.x < -250)
	{
		Col.r = 1;
		Speed.x = -Speed.x;
		Speed.y = rand() % 9 - 5;
	}
	

	if (Pos.y > 250)
	{
		Col.r = 1;
		Speed.y = -Speed.y;
		Speed.x = rand() % 9 - 5;
	}

	if (Pos.y < -250)
	{
		Col.r =1;
		Speed.y = -Speed.y;
		Speed.x = rand() % 9 - 5;
	}


	//오브젝트 끼리 충돌
	for (int i = 0; i < Max; ++i)
	{
		if (i != number)
		{
			auto cx = myscene.obj[i]->Pos.x - Pos.x;
			auto cy = myscene.obj[i]->Pos.y - Pos.y;
			float d = sqrt(cx*cx + cy*cy);
			if (d < size)
			{
				auto ts = myscene.obj[i]->Speed;
				myscene.obj[i]->Speed = Speed;
				Speed = ts;
				Pos = Pos + Speed;
				myscene.obj[i]->Pos = myscene.obj[i]->Pos + myscene.obj[i]->Speed;
				Col.r -= 0.25;
				myscene.obj[i]->Col.r -= 0.25;
			}
		}
	}
}

