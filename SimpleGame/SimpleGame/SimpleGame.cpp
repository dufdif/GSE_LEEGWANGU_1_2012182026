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
#include"Scene.h"


Scene myscene;
Renderer *g_Renderer = NULL;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	
	// Renderer Test
	for(int i=0;i<myscene.nObj;++i)
		g_Renderer->DrawSolidRect(myscene.obj[i]->Pos.x, myscene.obj[i]->Pos.y, myscene.obj[i]->Pos.z, myscene.obj[i]->size,myscene.obj[i]->Col.r,myscene.obj[i]->Col.g,myscene.obj[i]->Col.b,myscene.obj[i]->Col.a);

	glutSwapBuffers();
	
}

void Update(float dTime)//매번 모든 오브젝트를 갱신한다.
{
	myscene.Tick(dTime);

}

void Idle(void)
{
	Update(1);//델타타임을 몰라서 일단 1로둠
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	//button GLUT_LEFT_BUTTON , GLUT_MIDLE_BUTTON, GLUT_RIGHT_BUTTON
	//state GLUT_UP,GLUT_DOWN
	static bool click = false;
	switch(button)
	{
		case GLUT_LEFT_BUTTON:
			
			switch (state)
			{
			case GLUT_UP:
				if (click == true)
				{
					//myscene.CreateObj(mVector(x - 250, 250 - y, 0), mVector(1, 0, 0), Color(1, 1, 1, 1), rand() % 50 + 30);
					
					click = false;
				}
				break;

			case GLUT_DOWN:
				click = true;
				break;
			}

			break;

		case GLUT_MIDDLE_BUTTON:
			switch (state)
			{
			case GLUT_UP:
				break;

			case GLUT_DOWN:

				break;
			}
			break;

		case GLUT_RIGHT_BUTTON:
			switch (state)
			{
			case GLUT_UP:
				break;

			case GLUT_DOWN:

				break;
			}
			break;

	}


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
	for(int i=0;i<Max;++i)
		myscene.CreateObj();
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

