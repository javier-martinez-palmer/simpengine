#define WIN32_MEAN_AND_LEAN
#define WIN32_EXTRA_LEAN

/****************************************************************************
 Winmain.h 
 
 Author   :   Javier Palmer
 Date     :   2/3/2005

 Written for the FATMAN Game
*****************************************************************************/


#include <windows.h>

#include "oglwindow.h"		// the OpenGL window class
#include "vector.h"
#include "engine.h"			// the engine's main class
#include "simpengine.h"


WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	int loopRet;
	bool fscreen;
	char str[700];

	CoInitialize(NULL);

	if (!COGLWindow::RegisterWindow(hInst))
	{
		MessageBox(NULL, "Failed to register window class", "Error", MB_OK);
		return -1;
	}

	CSimpEngine *engine = NULL;

	sprintf(str, "Welcome to FATMAN's World!\n\nKeys:\nW - Walk\nD - Jump\n");
	strcat(str, "Press 'ESC' - to quit the game\n\n");
	strcat(str, "Use the mause to move around:\n");
	strcat(str, "Source code by:\nJavier Palmer\n");
		
	MessageBox(NULL, str, "Welcome!", MB_OK);

	sprintf(str, "Hello  FATMAN!\n\nYou have three minutes to kill all the goblins\n");
	strcat(str, "and eat all oranges. Good luck!");
	MessageBox(NULL, str, "All ready?", MB_OK);

	try
	{	
		//if (MessageBox(NULL,"", "Try Fullscreen?", MB_YESNO) == IDYES)
		//	fscreen = true;
		//else
			fscreen = false;

		engine = new CSimpEngine("FATMAN: OpenGL Game", fscreen, 800, 600, 16);

		loopRet = engine->EnterMessageLoop();

		delete engine;

		return loopRet;
	}
	catch(char *sz)
	{	
		MessageBox(NULL, sz, 0, 0);
		delete engine;
	}

	CoUninitialize();

	return -1;
}