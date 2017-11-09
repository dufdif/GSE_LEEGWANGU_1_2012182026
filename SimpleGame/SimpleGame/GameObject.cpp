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


CGameObject::CGameObject(Type t,mVector p, bool te,mVector s)
{
	Width = 1;
	Height = 1;
	type = t;
	tex = te;
	if (s.x == s.y == s.z == 0)
	{
		Speed.x = rand() % 10 - 5;
		Speed.y = rand() % 10 - 5;
	}
	else
		Speed = s;
	

	auto sp = sqrt((Speed.x*Speed.x) + (Speed.y*Speed.y));

	if (sp == 0)
	{
		Speed.x = 1;
		sp =1;
	}
	switch (t)
	{
	case character:
		hp = 10;
		maxhp = hp;
		size = 10;
		
		Speed.x /= sp;
		Speed.y /= sp;

		Speed = Speed * 300;
		
		Col = Color(1, 1, 1, 1);
		orgCol = Col;
		Damage = 100;
		myscene->nCharacter += 1;
		Enemy = false;
		break;

	case building:
		hp = 500;
		maxhp = hp;
		size = 50;
		Col = Color(1, 1, 0, 1);
		orgCol = Col;
		Speed.x = 0;
		Speed.y = 0;
		Damage = 100;
		Enemy = true;
		break;

	case bullet:
		hp = 5;
		maxhp = hp;
		size = 4;
		Col = Color(1, 0, 0, 1);
		orgCol = Col;
		Speed.x /= sp;
		Speed.y /= sp;

		Speed = Speed * 600;

		Damage = 10;
		Enemy = true;
		break;
	case arrow:
		hp = 10;
		maxhp = hp;
		size = 4;
		Col = Color(0, 1, 0, 1);
		orgCol = Col;
		Speed.x /= sp;
		Speed.y /= sp;

		Speed = Speed * 300;
		Damage = 10;
		Enemy = false;
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
		// *-------------------------- ������ �浹------------------------------*
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


		if (Pos.y > 250)
		{
			Col.r = 1;
			Pos.y = 250;
			Speed.y = -Speed.y;
			
		}

		if (Pos.y < -250)
		{
			Col.r = 1;
			Pos.y = -250;
			Speed.y = -Speed.y;
			
		}

		//---------------------------------------------------------------------

		//������Ʈ ���� �浹
		for (auto i =myscene->obj.begin()  ; i != myscene->obj.end(); ++i)
		{

			if ( type!=(*i)->type )//����Ÿ���� �ƴϰų� 
			{
				if (type == arrow && Master!=(*i)  || Enemy != (*i)->Enemy)//Ÿ���� ȭ���϶� 
					//�����ڿ� �ٸ� ������Ʈ�ų� ���� ��������϶�
				{


					auto cx = (*i)->Pos.x - Pos.x;
					auto cy = (*i)->Pos.y - Pos.y;
					float d = (cx*cx) + (cy*cy);
					d = sqrt(d);
					if (d * 2 < size + (*i)->size)
					{


						hp -= (*i)->Damage;

						(*i)->hp -= Damage;


						Col = Color(1, 0, 0, 1);
						(*i)->Col = Color(1, 0, 0, 1);

					}
				}
			}
			else
			{
				
				Col = orgCol;
				

			}
		}


		// �ڿ�����Ʈ Ÿ�Ժ� �̺�Ʈ

		switch (type)
		{
		case building:
			if (totalDtime > 0.5)
			{
				totalDtime = 0;
				myscene->CreateObj(bullet, Pos);
			}

			break;

		case character:
			if (totalDtime > 0.5)
			{
				totalDtime = 0;
				if (myscene->nObj < Max)
				{
					auto d = new  CGameObject(arrow, Pos);
					d->SetMaster(this);
					myscene->obj.push_back(d);
					myscene->nObj += 1;
				}
			}

			break;

		case arrow:	//ȭ���� �ʹ� ���� �����ʿ�� ���� �����Ǽ� �ð��� ������ ���������
			if (totalDtime > 5)
				Delobj = true;


		}

	}
	else
		Delobj = true;
}

