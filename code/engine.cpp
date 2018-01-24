#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
/****************************************************************************
Engine.cpp
 
 Author   :   Javier Palmer
 Date     :   2/3/2005

 Written for the FATMAN Game
*****************************************************************************/
#include <stdlib.h>

#include "engine.h"
#include "HiResTimer.h"
#include "camera.h"
#include "world.h"

void CEngine::CheckInput(float deltaTime)
{
	static float buttonDelta = 0.0f;

	int mouseDeltaX, mouseDeltaY;	// changes in the mouse position

	// decrease amount of time until next possible recognized button pressing
	buttonDelta -= deltaTime;

	if (buttonDelta < 0.0f)
		buttonDelta = 0.0f;

	// update devices
	inputSystem->Update();
	
	// informa de los eventos de teclado.
	if (inputSystem->KeyDown(DIK_W))
		OnKeyDown(VK_UP);
	if (inputSystem->KeyDown(DIK_J))
		OnKeyDown(VK_DOWN);
	if (inputSystem->KeyDown(DIK_A))
		OnKeyDown(VK_LEFT);
	if (inputSystem->KeyDown(DIK_D))
		OnKeyDown(VK_SPACE);
	if (inputSystem->KeyDown(DIK_S))
		OnKeyDown(VK_RIGHT);
	if (inputSystem->KeyDown(DIK_ADD))
		OnKeyDown(VK_ADD);
	if (inputSystem->KeyDown(DIK_SUBTRACT))
		OnKeyDown(VK_SUBTRACT);
	if (inputSystem->KeyDown(DIK_ESCAPE))
		OnKeyDown(VK_ESCAPE);
	if (inputSystem->ButtonDown(0))
	{
		if (buttonDelta == 0.0f)
		{
			OnMouseDownL(0,0);
			buttonDelta = 0.5f;
		}
	}
	if(inputSystem->KeyUp(DIK_W))
	    OnKeyUp(VK_UP);
	if (inputSystem->KeyUp(DIK_D))
		OnKeyUp(VK_SPACE);

	// retrieve the latest mouse movements.
	inputSystem->GetMouseMovement(mouseDeltaX, mouseDeltaY);
	OnMouseMove(mouseDeltaX, mouseDeltaY);

}

void CEngine::GameCycle(float deltaTime)
{
	CCamera *camera = OnGetCamera();	// get the camera
	CWorld *world = OnGetWorld();		// get the world

	if (useDInput)
		CheckInput(deltaTime);

	// setup opengl for frame (clear, identity)
	OnPrepare();

	// prepare objects and perform collisions
	world->Prepare();

	// move/orient camera
	camera->Animate(deltaTime);

	// move/orient objects
	world->Animate(deltaTime);

	// draw objects
	world->Draw(camera);

	// swap buffers
	SwapBuffers(hDC);
}

// EnterMessageLoop()
// desc: the Windows message loop
LRESULT CEngine::EnterMessageLoop()
{
	//	Message loop
	MSG msg;
	timer = new CHiResTimer;

	timer->Init();

	for (;;)
	{	
		GameCycle(timer->GetElapsedSeconds(1));
		while (PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			// we always update if there are any events, even if we're paused
			if (!GetMessage (&msg, NULL, 0, 0))
			{
				delete timer;
				return msg.wParam;
			}

			TranslateMessage (&msg);
    			DispatchMessage (&msg);
		}
	}

	delete timer;

	return msg.wParam;
}