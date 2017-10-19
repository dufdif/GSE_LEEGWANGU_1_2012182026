/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include"GameObject.h"
#include "Renderer.h"


CGameObject testobj[100];
int nObj = 0;

Renderer *g_Renderer = NULL;
int vx = 0;
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	
	// Renderer Test
	for(int i=0;i<nObj;++i)
		g_Renderer->DrawSolidRect(testobj[i].Pos.x, testobj[i].Pos.y, testobj[i].Pos.z, testobj[i].size,testobj[i].Col.r,testobj[i].Col.g,testobj[i].Col.b,testobj[i].Col.a);

	glutSwapBuffers();
}

void Update(float dTime)//매번 모든 오브젝트를 갱신한다.
{
	for ( int i=0;i<nObj;++i)
		testobj[i].Tick(dTime);

}
void CreateObj()//여기서 모든 오브젝트를 생성.
{
	testobj[nObj] = CGameObject(mVector(0, 0, 0), mVector(1, 0, 0), Color(1, 1, 0, 1), 60);
	nObj += 1;
}
void Idle(void)
{
	Update(1);//델타타임을 몰라서 일단 1로둠
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}


	//오브젝트 생성
	CreateObj();

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}



	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	
	glutMainLoop();

	delete g_Renderer;

    return 0;
}

