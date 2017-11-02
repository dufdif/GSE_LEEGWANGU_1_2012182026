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
#include<time.h>

float t = 0;
Scene* myscene=NULL;

auto Time = clock();

void RenderScene(void)
{
	myscene->RenderScene();
	
}

void Update(float dTime)//매번 모든 오브젝트를 갱신한다.
{

	myscene->Tick(dTime);
	
}

void Idle(void)
{
	float dtime = clock() - Time;
	Time +=dtime;
	//t += dtime;
	
	//std::cout << t/1000 << std::endl;
	Update(dtime/1000);//델타타임을 몰라서 일단 1로둠
	RenderScene();
	glutSwapBuffers();
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
					if(myscene->nCharacter<CharacterMax)
						myscene->CreateObj(character,mVector(x - 250, 250 - y, 0));
					
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
	glutSwapBuffers();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
	glutSwapBuffers();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
	glutSwapBuffers();
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
	myscene = new Scene;

	//오브젝트 생성
	
	// Initialize Renderer
	
	myscene->CreateObj(building, mVector(0, 0, 0));


	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	
	glutMainLoop();

	

    return 0;
}

