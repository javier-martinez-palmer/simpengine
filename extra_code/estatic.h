#ifndef __OBJ_H
#define __OBJ_H
/****************************************************************************
Estatic.h  another class to load models in the world.
 
 Author   :   Javier Palmer
 Date     :   2/3/2005

 Written for the FATMAN Game
*****************************************************************************/
#include <typeinfo.h>
#include "audiosystem.h"
#include "camera.h"
#include "entity.h"
#include "terrain.h"
#include "vector.h"
#include "player.h"
#include <Cg/cg.h>
#include <Cg/cgGL.h>



class CObj : public CEntity
{
private:

	CTexture *murtex;

	CGprogram program,tprog;
	CGcontext context;
	CGprofile profile,tprof;
	CGparameter	wave;	

protected:
	
	void OnCollision(CObject *collisionObject){};
	void OnProcessAI(){};
	void OnPrepare(){}; 
	void OnDraw(CCamera *camera);
	
public:

	CObj() {	position.x = 100;
				position.y = 0;
				position.z = 100;
				size = 3.0f; 	
				//Load(); 
				velocity = CVector(0.0, 0.0, 0.0); // speed of the player
				murtex = new CTexture;	
				murtex->LoadTexture("data\\texture\\muro2.tga");
				context = cgCreateContext();
				ChooseProfiles();
				LoadCgPrograms();
			}

	~CObj() 
	{
		cgDestroyProgram(program);
		cgDestroyProgram(tprog);
		cgDestroyContext(context);
	} //destruir.

	void CreaPared();
	void CreaPared_s();
	void CheckCgError(void)
	{
		CGerror err = cgGetError();
		if(err != CG_NO_ERROR)
		{
			exit(3);
		}
	}
	void ChooseProfiles(void);
	void LoadCgPrograms(void);

};

#endif  
     