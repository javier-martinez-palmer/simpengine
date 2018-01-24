#ifndef __WORLD_H
#define __WORLD_H
/****************************************************************************
WORLD.H
The CWorld class: The CWorld class represents the game world
			   of the engine. All objects, the terrain,
			   audio system, ambient world music and sound,
			   and the camera are held here.
 Author   :   Javier Palmer
 Date     :   2/3/2005

 Written for the FATMAN Game
*****************************************************************************/
#include <dmusicc.h>               // DirectMusic includes
#include <dmusici.h>
#include <d3d8types.h>             // for D3DVECTOR
#include <cguid.h>                 // for GUID_NULL

#include "entity.h"
#include "md2.h"
#include "object.h"
#include "camera.h"
#include "terrain.h"
#include "audiosystem.h"
#include "tree.h"
#include "player.h"
#include "fruta.h"
#include "estatic.h"
#include "wolf.h"
#include "goblin.h"
#include "gui.h"
#include "arb1.h"
#include "arb2.h"

#define MAX_OBJS 15

class CWorld
{
private:
	int screenWidth, screenHeight;
protected:
	 bool gameDone;
	 int LoadRest;
     void OnAnimate(float deltaTime);
     void OnDraw(CCamera *camera);
     void OnPrepare();

public:
     HWND hwnd;

     CTerrain *terrain;            // the terrain
     CCamera *camera;              // the camera
	 CPlayer *player;
     CAudioSystem *audioSystem;    // the audio system
     CAudio *worldSound;           // the world ambient sound
     CAudio *gameMusic;            // the game's music
	 CFruta *orange;
	 CObj *objeto;					// objetos paredes.
	 CArb1 *arboles;               //objetos con colisiones
	 CArb2 *templos;
	 CEntity *obj;                  //objetos sin colisiones
	 CEntity *obj2;
	 CWolfEnemy *wolf;
	 CGoblinEnemy *goblin;
	 CGUI *gui;
     
	 float timeStart;
	 float timeElapsed;
     int numgoblins;
     int numoranges;
	 
	 CWorld();
     CWorld(CCamera *c);
     ~CWorld();


     // initialize terrain, load objects and put in container
     inline void LoadWorld();
     void UnloadWorld();

     // do physics calculations for all objects in the world
     // including collisions
     void Animate(float deltaTime);
	 int CountObjectTypes(const type_info &classID);

     // render all objects in the world
     void Draw(CCamera *camera);     
	 void Prepare() { OnPrepare(); }
	 inline void LoadRestOranges_1();
	 inline void LoadRestOranges_2();

	 //beendet alle objects im welt, und vorbereitung davor
	 bool IsGameDone() { return gameDone; }
	 void QuitGame() { gameDone = true; }
	 inline void FadeScreen();
	 void SetScreen(int width, int height);

};


#endif