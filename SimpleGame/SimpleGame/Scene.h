#pragma once
#include"GameObject.h"
#include"Renderer.h"
#include<vector>
#include<list>

using namespace std;

#define Max 100
#define CharacterMax 10
class Scene
{
public:
	Scene();
	int nObj;
	int nCharacter = 0;
	
	list<CGameObject*> obj;
	
	Renderer *g_Renderer = NULL;

	~Scene();

	void CreateObj(mVector Pos, mVector vel, Color col,float w);
	void CreateObj(Type t,mVector Pos,bool te=false,mVector s=mVector(0,0,0));
	void DeleteObj();
	void CreateObj();
	void Tick(float dtime = 0);


	void RenderScene(void);
};

