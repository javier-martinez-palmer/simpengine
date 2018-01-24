#ifndef __OBJ_H
#define __OBJ_H



#include <typeinfo.h>
#include "audiosystem.h"
#include "camera.h"
#include "entity.h"
#include "terrain.h"
#include "vector.h"
#include "player.h"



class CObj : public CEntity
{
private:
	CTexture *murtex;

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
				murtex->LoadTexture("data\\texture\\muro.tga");
			}

	~CObj() {} //destruir.

	void CreaPared();
};

#endif  
     