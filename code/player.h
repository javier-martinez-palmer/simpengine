#ifndef __PLAYER_H
#define __PLAYER_H
/****************************************************************************
PLAYER.H
The CPlayer class: Player model functions and
                             methodes.

 Author   :   Javier Palmer
 Date     :   27/3/2005

 Written for the FATMAN Game
*****************************************************************************/
#include <typeinfo.h>

#include "audiosystem.h"
#include "camera.h"
#include "entity.h"
#include "terrain.h"
#include "vector.h"
#include "fruta.h"
#include "estatic.h"



enum AIPlayer
{
	AI_UNCARING,	// enemy is not scared and does not care
	AI_OPERATIV,	// enemy is scared and running away
	AI_DEAD,
	AI_JUMP,
};

class CFruta;

class CPlayer : public CEntity
{
private:
	CCamera *camara;
	CTerrain *terrain;
	CObj* objeto;
	CAudioSystem *audioSys;						// Nos hace falta una variable común a los enemigos(para saber 
                    							// cuando va a morir).
	CAudio *grito;
	GLfloat g_shadowMatrix[16];
protected:
	float runSpeed;          // speed of enemy when running,->CEntity
	
	void OnCollision(CObject *collisionObject)
	{
		if (typeid(*collisionObject) == typeid(CTerrain)) //(siempre)
		{
			position.y = size+1;
		}
		if (typeid(*collisionObject) == typeid(CFruta)) //(siempre)
		{
			//cogemos puntos
		}
		if (typeid(*collisionObject) == typeid(CObj))
		{
/*			velocity = CVector(0.0, 0.0, 0.0);
			if(direction > 90){	
			position.x--;
			position.z--;
			}
			else{
			position.x++;
			position.z++;
			}
*/		}
	}

	void OnProcessAI(){};
	void OnPrepare(); 
	void OnDraw(CCamera *camera);

	
public:

	float pitch;		// pitch of player's lookAt vector
	bool isDead;
	AIPlayer aiState;       // state of the player thought

	CPlayer() { size = 5.25f; 
				camara = NULL;        //para averiguar la camara.
				terrain = NULL;		  // " terreno. 
				audioSys = NULL;      // "
				grito = NULL;
				// EL MODELO
				Load(); 
				pitch = 30.0;
				bDelete = false;     // player starts off alive
				velocity = CVector(0.0, 0.0, 0.0); // speed of the player
				runSpeed = velocity.z;
				aiState = AI_UNCARING;
			}

	~CPlayer() {} //destruir.
	void Load(); //cargar el modelo protagonista

	void SetShadowMatrix( GLfloat destMat[16]);
	void SetCamera(CCamera *c) { camara = c; } //para averiguar los parámetros de cámara
	void DetachCamera() { camara = NULL; } //la camara cambia,...
	void SetTerrain(CTerrain *t) { terrain = t; } //averiguar terreno.
	void SetAudioSystem(CAudioSystem *aSys) { audioSys = aSys; } //averiguar audio.
};

#endif  
     