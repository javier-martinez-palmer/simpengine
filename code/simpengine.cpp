#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include "simpengine.h"

/*
	SIMPENGINE.CPP

	The SimpEngine implementation

	Author: Kevin Hawkins
	Date: 4/9/2001
	Description:

*/


void CSimpEngine::OnPrepare()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SMOOTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
}

void CSimpEngine::OnMouseDownL(float x, float y) 
{
//	if (!gameWorld->IsGameDone())
//		gameWorld->player->FireWeapon();  //not this time
}


void CSimpEngine::OnMouseMove(int deltaX, int deltaY)
{
		gameCamera->yaw += deltaX*mouseSensitivity;
		gameCamera->pitch -= deltaY*mouseSensitivity;
		if(gameWorld->player->aiState == AI_OPERATIV)
			gameWorld->player->direction += deltaX*mouseSensitivity;
}

void CSimpEngine::OnMouseMove(int x, int y, int centerX, int centerY)
{
	static float oldX;
	static float oldY;
	static float yaw = 0.0f;
	static float pitch = 0.0f;

	float mX, mY;

	mX = (float)x;
	mY = (float)y;

	if (mX < centerX/2)
		gameCamera->yaw -= 0.1f*mouseSensitivity;
	if (mX > centerX/2)
		gameCamera->yaw += 0.1f*mouseSensitivity;

	if (mY < centerY/2)
		gameCamera->pitch += 0.1f*mouseSensitivity;
	if (mY > centerY/2)
		gameCamera->pitch -= 0.1f*mouseSensitivity;

	oldX = mX;
	oldY = mY;
}


void CSimpEngine::OnKeyDown(int nVirtKey)
{
	char str[700];
//	if (!gameWorld->IsGameDone())
//	{
		switch (nVirtKey)
		{
		case VK_UP:
			if(gameWorld->player->currentFrame < 46){
				gameWorld->player->aiState = AI_OPERATIV;
				gameWorld->player->velocity += CVector(0,0,1.0); 
				if ( gameWorld->player->velocity.z > 30) 
					gameWorld->player->velocity.z = 30;
			}
			break;
		case VK_DOWN:
			gameWorld->player->aiState = AI_OPERATIV;
			gameWorld->player->velocity -= CVector(0,0,-1.0);
			if ( gameWorld->player->velocity.z < -20)
				gameWorld->player->velocity.z = -20;
			break;
		case VK_RIGHT:
			gameWorld->player->aiState = AI_OPERATIV;
			gameWorld->player->velocity += CVector(1.0, 0.0, 0.0);
			break;
		case VK_LEFT:
			gameWorld->player->aiState = AI_OPERATIV;
			gameWorld->player->velocity += CVector(-1.0, 0.0, 0.0);
			break;
		case VK_SPACE:
			gameWorld->player->aiState = AI_JUMP;			
			break;
		case VK_ESCAPE:
	        sprintf(str, "quit the game?\n");
	        if(MessageBox(NULL, str, "quit the game?",MB_YESNO) == IDYES)
	           PostQuitMessage(0);
			break;
		case VK_ADD:
			mouseSensitivity += 0.05f;
			break;
		case VK_SUBTRACT:
			mouseSensitivity -= 0.05f;
			if (mouseSensitivity < 0.05)
				mouseSensitivity = 0.05f;
			break;
		default:
			gameWorld->player->aiState = AI_UNCARING;
			break;
		}
/*	}
	else
	{
		if ((nVirtKey) == VK_ESCAPE)
			PostQuitMessage(0);
	}*/
}

void CSimpEngine::OnKeyUp(int nVirtKey)
{
	switch (nVirtKey)
	{
		case VK_UP:
			if(gameWorld->player->aiState == AI_OPERATIV)
		    gameWorld->player->aiState = AI_UNCARING;
			break;
		case VK_SPACE:
			if(gameWorld->player->currentFrame > 100) //player management
				gameWorld->player->velocity = CVector(0.0, 0.0, 0.0);
			if(gameWorld->player->currentFrame == 111) 
				gameWorld->player->aiState = AI_UNCARING;
			break;
	}
}

