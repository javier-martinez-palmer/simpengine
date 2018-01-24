#ifndef __SIMPENGINE
#define __SIMPENGINE

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
/****************************************************************************
SIMPENGINE.H
 COGLWindow class:The SimpEngine class is the main interface for SimpEngine.
			   Derived from CEngine, it provides the camera and world objects.
 
 Author   :   Javier Palmer
 Date     :   2/3/2005

 Written for the FATMAN Game
*****************************************************************************/
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "engine.h"
#include "object.h"
#include "camera.h"
#include "terrain.h"
#include "world.h"

class CSimpEngine : public CEngine
{
private:
	CCamera *gameCamera;
	CWorld *gameWorld;

protected:
	CCamera *OnGetCamera() { return gameCamera; }
	CWorld *OnGetWorld() { return gameWorld; }

	void OnPrepare();
	void OnMouseDownL(float x, float y);
	void OnMouseMove(int deltaX, int deltaY);
	void OnMouseMove(int x, int y, int centerX, int centerY);
	void OnKeyDown(int nVirtKey);
	void OnKeyUp(int nVirtKey);

public:
	CSimpEngine() 
	{
		gameCamera = new CCamera;
		gameWorld = new CWorld;
	}

	CSimpEngine(const char *szName, bool fscreen, int w, int h, int b) :
		CEngine(szName, fscreen, w, h, b) 
	{
		gameCamera = new CCamera;
		gameWorld = new CWorld(gameCamera);
		gameCamera->yaw=45.0;
	}

	~CSimpEngine() 
	{
		delete gameWorld;
		delete gameCamera;
		gameWorld = NULL;
		gameCamera = NULL;
	}
};


#endif