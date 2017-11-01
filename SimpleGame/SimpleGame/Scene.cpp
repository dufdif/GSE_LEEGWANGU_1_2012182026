#include "stdafx.h"
#include "Scene.h"


Scene::Scene()
{
	nObj = 0;
	g_Renderer = new Renderer(500, 500);

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
	for (auto i=obj.begin(); i!=obj.end(); ++i)
		g_Renderer->DrawSolidRect((*i)->Pos.x, (*i)->Pos.y, (*i)->Pos.z, (*i)->size, (*i)->Col.r, (*i)->Col.g, (*i)->Col.b, (*i)->Col.a);



}


void Scene::Tick(float dtime)
{
	

	for (auto i = obj.begin();i!=obj.end() ;i++)
		(*i)->Tick(dtime);
	DeleteObj();

	
}

Scene::~Scene()
{
	if (nObj > 0)
	{
		for (auto i = obj.begin(); i != obj.end(); i++)
		{
			delete *i;
			nObj -= 1;
		}
		
	}
	obj.clear();
	delete g_Renderer;
}

void Scene::CreateObj(mVector Pos,mVector vel,Color col,float w)//여기서 모든 오브젝트를 생성.
{
	if (nObj < Max)
	{
		obj.push_back(new  CGameObject(Pos, vel, col, w));
		
		
		nObj += 1;
	}
}

void Scene::CreateObj()//여기서 모든 오브젝트를 생성.
{
	if (nObj < Max)
	{
		obj.push_back(new  CGameObject());


		nObj += 1;
	}
	
}

void Scene::DeleteObj()
{
	for (auto i = obj.begin(); i != obj.end();)
	{
		if ((*i)->Delobj == true)
		{

			delete (*i);
			auto t = i;

			i++;
			obj.erase(t);
			nObj--;

		}
		else
			i++;
		

	}
}