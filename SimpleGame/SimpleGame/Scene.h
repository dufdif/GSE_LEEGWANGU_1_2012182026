#pragma once
#include"GameObject.h"
#define Max 50

class Scene
{
public:
	Scene();
	int nObj;
	CGameObject* obj[Max];
	

	~Scene();

	void CreateObj(mVector Pos, mVector vel, Color col,float w);
	void CreateObj();
	void Tick(float dtime = 0);
};

