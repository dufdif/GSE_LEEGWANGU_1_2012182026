#include "stdafx.h"
#include "GameObject.h"
#include<time.h>
#include"Scene.h"
extern Scene* myscene;
CGameObject::CGameObject()
{
	Width = 0.01;
	Height = 0.01;
	Col = Color(1, 1, 1, 1);
	Pos.x = 0;
	Pos.y = 0;
	Pos.z = 0;
	size = 7;

	hp = 100;
	
	Speed.x = rand()%90-50;
	Speed.y = rand() % 90-50;

	if (Speed.x == 0 && Speed.y == 0)
		Speed.y = 30;

	

}

CGameObject::CGameObject(mVector p,mVector s,Color c,float sz)
{
	Width = 0.01;
	Height = 0.01;
	Col = Color(1, 1, 1, 1);
	Pos = p;
	size = 7;

	hp = 100;

	Speed.x = rand() % 90 - 50;
	Speed.y = rand() % 90 - 50;

	if (Speed.x == 0 && Speed.y == 0)
		Speed.y = 30;
}





CGameObject::~CGameObject()
{
}

void CGameObject::Tick(float dTime)
{
	totalDtime += dTime;
	if (totalDtime > 10)
		hp=0;

	if (hp > 0)
	{
		Pos = Pos + Speed*dTime;

		if (Pos.x > 250)
		{
			Col.r = 1;
			Speed.x = -Speed.x;
			Speed.y = rand() % 90 - 50;
		}

		if (Pos.x < -250)
		{
			Col.r = 1;
			Speed.x = -Speed.x;
			Speed.y = rand() % 90 - 50;
		}


		if (Pos.y > 250)
		{
			Col.r = 1;
			Speed.y = -Speed.y;
			Speed.x = rand() % 90 - 50;
		}

		if (Pos.y < -250)
		{
			Col.r = 1;
			Speed.y = -Speed.y;
			Speed.x = rand() % 90 - 50;
		}


		//오브젝트 끼리 충돌
		for (auto i =myscene->obj.begin()  ; i != myscene->obj.end(); ++i)
		{
			if (this !=( *i))
			{
				auto cx = (*i)->Pos.x - Pos.x;
				auto cy = (*i)->Pos.y - Pos.y;
				float d = sqrt(cx*cx + cy*cy);
				if (d < size * 2)
				{
					auto ts = (*i)->Speed;
					(*i)->Speed = Speed;
					Speed = ts;
					Pos = Pos + Speed*dTime * 3;
					(*i)->Pos = (*i)->Pos + (*i)->Speed*dTime * 3;
					Col.r -= 0.25;
					(*i)->Col.r -= 0.25;

					hp -= 25;
					(*i)->hp -= 10;

				}
			}
		}
	}
	else
		Delobj = true;
}

