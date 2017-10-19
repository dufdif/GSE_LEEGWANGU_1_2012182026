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

			if (obj[i] != NULL)//이 뜻은 결국 하나의 오브젝트를 지우면 해당 인덱스를 널로 만들어야함
				delete obj[i];
		}

	}

}

void Scene::CreateObj(mVector Pos,mVector vel,Color col,float w)//여기서 모든 오브젝트를 생성.
{
	obj[nObj] = new  CGameObject(Pos,vel, col, w);
	obj[nObj]->number = nObj;
	nObj += 1;
}

void Scene::CreateObj()//여기서 모든 오브젝트를 생성.
{
	obj[nObj] = new  CGameObject();
	obj[nObj]->number = nObj;
	nObj += 1;
}