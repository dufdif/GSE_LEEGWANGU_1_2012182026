#include "stdafx.h"
#include "Scene.h"


Scene::Scene()
{
	nObj = 0;
	g_Renderer = new Renderer(500, 500);
	for (int i = 0; i < Max; ++i)
		obj[i] = NULL;
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

}

void Scene::RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);


	// Renderer Test
	for (int i = 0; i<Max; ++i)
		if(obj[i]!=NULL)
			g_Renderer->DrawSolidRect(obj[i]->Pos.x, obj[i]->Pos.y, obj[i]->Pos.z, obj[i]->size, obj[i]->Col.r, obj[i]->Col.g, obj[i]->Col.b, obj[i]->Col.a);



}


void Scene::Tick(float dtime)
{
	

	for (int i = 0; i<Max; ++i)
		if(obj[i]!=NULL)
		obj[i]->Tick(dtime);
	DeleteObj();

	
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
	delete g_Renderer;
}

void Scene::CreateObj(mVector Pos,mVector vel,Color col,float w)//���⼭ ��� ������Ʈ�� ����.
{
	if (nObj < Max)
	{
		obj[nObj] = new  CGameObject(Pos, vel, col, w);
		obj[nObj]->number = nObj;
		nObj += 1;
	}
}

void Scene::CreateObj()//���⼭ ��� ������Ʈ�� ����.
{
	if (nObj < Max)
	{
		obj[nObj] = new  CGameObject();
		obj[nObj]->number = nObj;
		nObj += 1;
	}
}

void Scene::DeleteObj()
{
	for (int i = 0; i < Max; ++i)
	{
		if (obj[i] != NULL)
		{
			if (obj[i]->Delobj == true)
			{
				delete obj[i];
				obj[i] = NULL;
				nObj -= 1;
			}
		}
	}
}