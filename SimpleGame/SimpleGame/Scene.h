#pragma once
#include"GameObject.h"
#include"Renderer.h"
#define Max 10

class Scene
{
public:
	Scene();
	int nObj;
	CGameObject* obj[Max];
	Renderer *g_Renderer = NULL;

	~Scene();

	void CreateObj(mVector Pos, mVector vel, Color col,float w);
	void DeleteObj();
	void CreateObj();
	void Tick(float dtime = 0);


	void RenderScene(void);
};

