#include "stdafx.h"
#include "Scene.h"

GLuint testTexture = 0;//적팀
GLuint testTexture2 = 0;//우리팀

Scene::Scene()
{
	nObj = 0;
	g_Renderer = new Renderer(500, 800);

	testTexture = g_Renderer->CreatePngTexture(".\\Texture\\Unit2.png");
	testTexture2 = g_Renderer->CreatePngTexture(".\\Texture\\Unit1.png");

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
	for (auto i = obj.begin(); i != obj.end(); ++i)
	{	
		if ((*i)->tex == true)
			if((*i)->Enemy)
				g_Renderer->DrawTexturedRect((*i)->Pos.x, (*i)->Pos.y, (*i)->Pos.z, (*i)->size, (*i)->Col.r, (*i)->Col.g, (*i)->Col.b, (*i)->Col.a, testTexture,(*i)->Level);
			else
				g_Renderer->DrawTexturedRect((*i)->Pos.x, (*i)->Pos.y, (*i)->Pos.z, (*i)->size, (*i)->Col.r, (*i)->Col.g, (*i)->Col.b, (*i)->Col.a, testTexture2, (*i)->Level);
		else
			g_Renderer->DrawSolidRect((*i)->Pos.x, (*i)->Pos.y, (*i)->Pos.z, (*i)->size, (*i)->Col.r, (*i)->Col.g, (*i)->Col.b, (*i)->Col.a, (*i)->Level);

		if ((*i)->type == building )
		{
			if ((*i)->Enemy == true)
				g_Renderer->DrawSolidRectGauge((*i)->Pos.x, (*i)->Pos.y+55, (*i)->Pos.z, (*i)->size, 4, 1, 0, 0, 1, (*i)->hp / (*i)->maxhp, 0.2);
			else
				g_Renderer->DrawSolidRectGauge((*i)->Pos.x, (*i)->Pos.y+55, (*i)->Pos.z, (*i)->size, 4, 0, 0, 1, 1, (*i)->hp / (*i)->maxhp, 0.2);
		}
		if ((*i)->type == character)
		{
			if ((*i)->Enemy == true)
				g_Renderer->DrawSolidRectGauge((*i)->Pos.x, (*i)->Pos.y + 20, (*i)->Pos.z, (*i)->size, 2, 1, 0, 0, 1, (*i)->hp / (*i)->maxhp, 0.2);
			else
				g_Renderer->DrawSolidRectGauge((*i)->Pos.x, (*i)->Pos.y + 20, (*i)->Pos.z, (*i)->size, 2, 0, 0, 1, 1, (*i)->hp / (*i)->maxhp, 0.2);

		}

	}

	

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

void Scene::CreateObj(Type t,mVector p,bool enemy,bool te,mVector s)//여기서 모든 오브젝트를 생성.
{
	if (nObj < Max)
	{
		obj.push_back(new  CGameObject(t,p,enemy,te,s));


		nObj += 1;
	}

}


void Scene::DeleteObj()
{
	for (auto i = obj.begin(); i != obj.end();)
	{
		if ((*i)->Delobj == true)
		{
			if((*i)->type==character)
				nCharacter -= 1;

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