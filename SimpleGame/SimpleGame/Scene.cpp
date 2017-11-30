#include "stdafx.h"
#include "Scene.h"

GLuint testTexture = 0;//적팀
GLuint testTexture2 = 0;//우리팀
GLuint background = 0;//배경

GLuint anitex1 = 0;//적유닛
GLuint anitex2 = 0;//아군유닛

GLuint ptex1 = 0;//파티클
GLuint ptex2 = 0;//파티클2


Scene::Scene()
{
	nObj = 0;
	g_Renderer = new Renderer(500, 800);

	testTexture = g_Renderer->CreatePngTexture(".\\Texture\\Unit2.png");
	testTexture2 = g_Renderer->CreatePngTexture(".\\Texture\\Unit1.png");
	background= g_Renderer->CreatePngTexture(".\\Texture\\background.png");
	anitex1 = g_Renderer->CreatePngTexture(".\\Texture\\a1.png");
	anitex2 = g_Renderer->CreatePngTexture(".\\Texture\\a2.png");
	ptex1= g_Renderer->CreatePngTexture(".\\Texture\\p1.png");
	ptex2 = g_Renderer->CreatePngTexture(".\\Texture\\p2.png");

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

	//배경그리기
	g_Renderer->DrawTexturedRect(0, 0,0 , 800, 1, 1, 1, 1, background,0.9);
	for (auto i = obj.begin(); i != obj.end(); ++i)
	{	
		if ((*i)->tex == true)
			if ((*i)->Enemy)
				g_Renderer->DrawTexturedRect((*i)->Pos.x, (*i)->Pos.y, (*i)->Pos.z, (*i)->size, (*i)->Col.r, (*i)->Col.g, (*i)->Col.b, (*i)->Col.a, testTexture, (*i)->Level);
			else
				g_Renderer->DrawTexturedRect((*i)->Pos.x, (*i)->Pos.y, (*i)->Pos.z, (*i)->size, (*i)->Col.r, (*i)->Col.g, (*i)->Col.b, (*i)->Col.a, testTexture2, (*i)->Level);
		else if ((*i)->type == character)
			if ((*i)->Enemy)
				g_Renderer->DrawTexturedRectSeq((*i)->Pos.x, (*i)->Pos.y, (*i)->Pos.z, (*i)->size, 1, 1, 1, 1, anitex1, (*i)->curanim, 0, (*i)->maxanim, 1, (*i)->Level);
			else
				g_Renderer->DrawTexturedRectSeq((*i)->Pos.x, (*i)->Pos.y, (*i)->Pos.z, (*i)->size, 1, 1, 1, 1, anitex2, (*i)->curanim, 0, (*i)->maxanim, 1, (*i)->Level);
		else if ((*i)->type == bullet)
			if ((*i)->Enemy)
				g_Renderer->DrawParticle((*i)->Pos.x, (*i)->Pos.y, (*i)->Pos.z, (*i)->size, 1, 1, 1, 1, 0, 1, ptex1, (*i)->particletime);
			else
				g_Renderer->DrawParticle((*i)->Pos.x, (*i)->Pos.y, (*i)->Pos.z, (*i)->size, 1, 1, 1, 1, 0, -1, ptex2, (*i)->particletime);
		else
			g_Renderer->DrawSolidRect((*i)->Pos.x, (*i)->Pos.y, (*i)->Pos.z, (*i)->size, (*i)->Col.r, (*i)->Col.g, (*i)->Col.b, (*i)->Col.a,(*i)->Level);
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