#include "stdafx.h"
#include "Scene.h"


Scene::Scene()
{
	nObj = 0;
}
void Scene::Tick(float dtime)
{
	for (int i = 0; i<nObj; ++i)
		obj[i]->Tick(dtime);
}

Scene::~Scene()
{
	if (nObj > 0)
	{
		for (int i = 0; i < Max; ++i)
		{

			if (obj[i] != NULL)//�� ���� �ᱹ �ϳ��� ������Ʈ�� ����� �ش� �ε����� �η� ��������
				delete obj[i];
		}

	}

}

void Scene::CreateObj(mVector Pos,mVector vel,Color col,float w)//���⼭ ��� ������Ʈ�� ����.
{
	obj[nObj] = new  CGameObject(Pos,vel, col, w);
	obj[nObj]->number = nObj;
	nObj += 1;
}

void Scene::CreateObj()//���⼭ ��� ������Ʈ�� ����.
{
	obj[nObj] = new  CGameObject();
	obj[nObj]->number = nObj;
	nObj += 1;
}