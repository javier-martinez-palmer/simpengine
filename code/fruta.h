#ifndef __FRUTA_H
#define __FRUTA_H
/****************************************************************************
FRUTA.H
The CFruta class: The CFruta class loads the oranges
 
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
#include "Particles.h"
#include "explosion.h"



enum AIFruta
{
	AI_FRESH,	// enemy is not scared and does not care
	AI_EATED
};

class CPlayer;

class CFruta : public CEntity
{
private:
	void SetupExplosionTexture();
	CAudioSystem *audioSys;		// Nos hace falta una variable común a los enemigos(para saber 							// cuando va a morir).
	float distFromPlayer;
protected:
	
	void OnCollision(CObject *collisionObject)
	{
		if (typeid(*collisionObject) == typeid(CTerrain)) // siempre
		{
			position.y = size;
		}
		if (typeid(*collisionObject) == typeid(CPlayer)) // eated
		{
			aiState = AI_EATED;
		}
	}

	void OnProcessAI();
	void OnAnimate(scalar_t deltaTime);
	void OnPrepare(); 
	void OnDraw(CCamera *camera);

	
public:
	CTexture * explosionTex;
	bool isExplosion;
	CExplosion * explosion;
	CPlayer* playerInf;


	float pitch;		// pitch of player's lookAt vector
	AIFruta aiState;       // state of the player thought

	CFruta() {  size = 6.25f; 	  // " terreno. 
				audioSys = NULL;	  // "

				// LAS PARTICULAS
				isExplosion = false;
				explosion = NULL;
				explosionTex = new CTexture;


				// EL MODELO
				pitch = 30.0;
				bDelete = false;     // player starts off alive
				velocity = CVector(0.0, 0.0, 0.0); // speed of the player
				aiState = AI_FRESH;
				Load(); 
			}
	CFruta(int x, int z) { 
				position.x = x;
				position.z = z;
				size = 6.25f; 	  // " terreno. 
				audioSys = NULL;	  // "
				
				// LAS PARTICULAS
				isExplosion = false;
				explosion = NULL;
				explosionTex = new CTexture;

				// EL MODELO
				Load(); 
				pitch = 30.0;
				bDelete = false;     // player starts off alive
				velocity = CVector(0.0, 0.0, 0.0); // speed of the player
				aiState = AI_FRESH;
			}

	~CFruta() {
		if (explosion != NULL)
		{
			explosion->KillSystem();
			delete [] explosion;
			explosion = NULL;
		}

		if (explosionTex != NULL)
		{
			delete explosionTex;
			explosionTex = NULL;
		}
	} //destruir.

	void Load(); //cargar el modelo protagonista
	void SetAudioSystem(CAudioSystem *aSys) { audioSys = aSys; } //averiguar audio.
	void SetPlayer(CPlayer* pl) { playerInf = pl;}
};

#endif  
     