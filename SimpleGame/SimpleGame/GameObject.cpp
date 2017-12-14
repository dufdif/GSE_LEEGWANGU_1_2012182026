#include "stdafx.h"
#include "GameObject.h"
#include<time.h>
#include"Scene.h"
#include<timeapi.h>
#include<iostream>
using namespace std;
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

	tex = false;

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


CGameObject::CGameObject(Type t,mVector p,bool enemy, bool te,mVector s)
{
	Enemy = enemy;
	Width = 1;
	Height = 1;
	type = t;
	tex = te;
	if (s.x == s.y == s.z == 0)
	{
		if (Enemy)
		{
			srand(timeGetTime());
			if (type != character)
			{
				Speed.x = rand() % 10 - 5;
				Speed.y = -5;
			}
			else
			{
				Speed.x = rand() % 5 - 2.5;
				Speed.y = -0.25;

			}
		}
		else
		{
			if (type != character)
			{
				Speed.x = rand() % 5 - 2.5;
				Speed.y = 5;

			}
			else
			{
				Speed.x = rand() % 5 - 2.5;
				Speed.y = 0.25;

			}

		}
	}
	else
		Speed = s;
	

	auto sp = sqrt((Speed.x*Speed.x) + (Speed.y*Speed.y)) * 3;

	if (sp == 0)
	{
		Speed.x = 1;
		sp =1;
	}
	switch (t)
	{
	case character:
		hp = 100;
		maxhp = hp;
		size = 60;
		
		Speed.x /= sp;
		Speed.y /= sp;
		totalDtime = 10;
		Speed = Speed * 300;
		if (Enemy)
		{
			Col = Color(1, 0, 0, 1);
			maxanim =23;
			anitime = 0.5 / maxanim;
		}
		else
		{
			Col = Color(0, 0, 1, 1);
			maxanim = 3;
			anitime = 0.5 / maxanim;
		}
		orgCol = Col;
		Damage = 10;
		myscene->nCharacter += 1;
		Level = 0.2;
		curanim = 0;
		
		break;

	case building:
		hp = 500;
		maxhp = hp;
		size = 100;
		Col = Color(1, 1, 1, 1);
		orgCol = Col;
		Speed.x = 0;
		Speed.y = 0;
		Damage = 500;
		Level = 0.1;
		break;

	case bullet:
		hp = 15;
		maxhp = hp;
		size = 3;
		if(Enemy)
			Col = Color(1, 0, 0, 1);
		else
			Col = Color(0, 0, 1, 1);
		orgCol = Col;
		Speed.x /= sp;
		Speed.y /= sp;
		Level = 0.3;
		Speed = Speed * 600;

		Damage = 15;
		
		break;
	case arrow:
		hp = 10;
		maxhp = hp;
		size = 7;
		
		if(Enemy)
			Col = Color(0.5, 0.2, 0.7, 1);
		else
			Col = Color(1, 1, 0, 1);
		orgCol = Col;
		Speed.x /= sp;
		Speed.y /= sp;

		Speed = Speed * 100;
		Damage = 10;
		Level = 0.3;
		break;

	}

	Pos = p;

}




CGameObject::~CGameObject()
{
}

void CGameObject::Tick(float dTime)
{
	totalDtime += dTime;
	
	if (hp > 0)
	{
		Pos = Pos + Speed*dTime;
		// *-------------------------- 벽과의 충돌------------------------------*

		if (type == character)
		{
			if (Pos.x > 250)
			{
				Col.r = 1;
				Speed.x = -Speed.x;
				Pos.x = 250;
			}

			if (Pos.x < -250)
			{
				Col.r = 1;
				Speed.x = -Speed.x;
				Pos.x = -250;
			}


			if (Pos.y > 400)
			{
				Col.r = 1;
				Pos.y = 400;
				Speed.y = -Speed.y;
				Speed.x = rand() % 10 - 5;

			}

			if (Pos.y < -400)
			{
				Col.r = 1;
				Pos.y = -400;
				Speed.y = -Speed.y;
				Speed.x = rand() % 10 - 5;

			}
		}
		else
		{

			if (Pos.x > 250)
			{
				Delobj = true;
			}

			if (Pos.x < -250)
			{
				Delobj = true;
			}


			if (Pos.y > 400)
			{
				Delobj = true;
			}

			if (Pos.y < -400)
			{
				Delobj = true;

			}
		}
		//---------------------------------------------------------------------

		//오브젝트 끼리 충돌
		for (auto i =myscene->obj.begin()  ; i != myscene->obj.end(); ++i)
		{

			if ( type!=(*i)->type )//같은타입이 아니거나 
			{
				if ( Enemy != (*i)->Enemy)//타입이 화살일때 
					//소유자와 다른 오브젝트거나 서로 적대관계일때
				{
					
					
					auto cx = (*i)->Pos.x - Pos.x;
					auto cy = (*i)->Pos.y - Pos.y;
					float d = (cx*cx) + (cy*cy);
					d = sqrt(d);
					if (d * 2 < size + (*i)->size)
					{
						if ( type !=building &&(*i)->type==building)
						{ 
							float h1 = hp;
							float h2 = (*i)->hp;
							hp -= h2;

							if(type!=character)//캐릭터가 아니면 그냥 체력을깎지만
								(*i)->hp -= h1;
							else//캐릭터면 현재 속도에 비례해서 깎아버림
							{
								auto px = Speed.x;
								auto py = Speed.y;

								float l = sqrt(px*px + py*py);
								(*i)->hp -= l*0.7;

							}


							Col = Color(1, 0, 0, 1);
							(*i)->Col = Color(1, 0, 0, 1);
						}

						if ((type == bullet || type == arrow) && ((*i)->type == character))
						{
							float h1 = hp;
							float h2 = (*i)->hp;

							hp -= h2;

							if ((*i)->hp > (*i)->maxhp / 2)
								(*i)->hp -= h1;
							else
								(*i)->hp -= h1 / 2;

							Col = Color(1, 0, 0, 1);
							(*i)->Col = Color(1, 0, 0, 1);

						}


					}
				}
			}
			else
			{
				
				Col = orgCol;
				

			}
		}


		// ★오브젝트 타입별 이벤트

		switch (type)
		{
		case building:
			if (totalDtime > 1.5)
			{
				totalDtime = 0;
				myscene->CreateObj(bullet, Pos,this->Enemy);
			}

			break;

		case character:

			if (maxhp / 2 >= hp)
			{
				Speed.x = rand() % 10 - 5;
				if(Enemy)
					Speed.y = Speed.y-accel*dTime;
				else
					Speed.y = Speed.y + accel*dTime;

			}

			if (anitime > 0.1 / maxanim)
			{
				anitime = 0;
				if (curanim < maxanim)
					curanim += 1;
				else
					curanim = 0;


			}
			else
				anitime += dTime;
			if (totalDtime >0.8)
			{
				
				totalDtime = 0;
				if (myscene->nObj < Max)
				{
					auto d = new  CGameObject(arrow, Pos,this->Enemy);
					d->SetMaster(this);
					myscene->obj.push_back(d);
					myscene->nObj += 1;
				}
			}

			break;

		case arrow:	
			break;
			
		case bullet:
			particletime += dTime;
			break;


		}

	}
	else
		Delobj = true;
}

