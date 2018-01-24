#ifndef __GOBLINENEMY_H
#define __GOBLINENEMY_H
/****************************************************************************
GOBLIN.H
enemy model computation and ai class.
 
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
#include "fruta.h"
#include "wolf.h"


class CPlayer;
class CTerrain;

class CGoblinEnemy : public CEntity
{
private:
	void SetupExplosionTexture();
	CAudioSystem *audioSys;	
protected:

	CPlayer *player;
	CTerrain *terrain;
	float runSpeed;          // speed of enemy when running,->CEntity
    float distFromPlayer;    // distance this enemy is from player	
	float pitch;		// pitch of Enemy's lookAt vector
	bool isDead;
	AIEnemy aiState;       // state of the Enemy thought

	void OnCollision(CObject *collisionObject)
	{
		if (typeid(*collisionObject) == typeid(CTerrain)) //(siempre)
		{
			position.y = size;
		}
		if (typeid(*collisionObject) == typeid(CPlayer)) //(siempre)
		{
		  if((player->aiState == AI_JUMP) || (aiState == AI_DEAD))
			 aiState = AI_MUERE;
		  else
			 player->aiState = AI_DEAD;
		}
		if (typeid(*collisionObject) == typeid(CGoblinEnemy)) 
		{
          direction += float(rand() % 180);;          // set the direction oposite.
		}
		if ( position.x <= terrain->GetScanDepth()){
			 position.x = terrain->GetScanDepth();
			 direction += float(rand() % 180);
		}
		if ( position.x >= terrain->GetWidth()*terrain->GetMul() - terrain->GetScanDepth()){
			 position.x = terrain->GetWidth()*terrain->GetMul() - terrain->GetScanDepth();
		     direction += float(rand() % 180);
		}
		if ( position.z <= terrain->GetScanDepth()){
			 position.z = terrain->GetScanDepth();
	          direction += float(rand() % 180);	
		}
		if ( position.z >= terrain->GetWidth()*terrain->GetMul() - terrain->GetScanDepth()){
			 position.z = terrain->GetWidth()*terrain->GetMul() - terrain->GetScanDepth();
	          direction += float(rand() % 180);	
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

	CGoblinEnemy() {
				// LAS PARTICULAS
				isExplosion = false;
				explosion = NULL;
				explosionTex = new CTexture;

		size = 6.25f; 
		pitch = 30.0;
		bDelete = false;     // Enemy starts off aliv
		velocity = CVector(0.0, 0.0, 0.0); // speed of the Enemy
		runSpeed = velocity.z;
		aiState = AI_VIGILA;
		Load(); 
	}
	CGoblinEnemy(float x, float z) { 
				// LAS PARTICULAS
				isExplosion = false;
				explosion = NULL;
				explosionTex = new CTexture;

		position.x = x; position.z = z; 
		
		size = 6.0f; 
		pitch = 30.0;
		bDelete = false;     // Enemy starts off aliv
		velocity = CVector(0.0, 0.0, 0.0); // speed of the Enemy
		runSpeed = velocity.z;
		aiState = AI_VIGILA;
		Load();
	}
	~CGoblinEnemy() {}

	void Load();
	void SetPlayer(CPlayer *c) { player = c; } //para averiguar el estado del player
	void SetTerrain(CTerrain *t){terrain = t;}
	void SetAudioSystem(CAudioSystem *aSys) { audioSys = aSys; } //averiguar audio.

};


#endif
