/****************************************************************************
 Arb1.h  tree model loader and function definition classe.
 
 Author   :   Javier Palmer
 Date     :   2/3/2005

 Written for the FATMAN Game
*****************************************************************************/
#ifndef __ARB1_H
#define __ARB1_H


#include <typeinfo.h>
#include "camera.h"
#include "entity.h"
#include "terrain.h"
#include "vector.h"
#include "player.h"



class CPlayer;

class CArb1 : public CEntity
{
protected:
	
	void OnCollision(CObject *collisionObject)
	{
		if (typeid(*collisionObject) == typeid(CTerrain)) //(siempre)
		{
			position.y = 0;
		}
		if (typeid(*collisionObject) == typeid(CPlayer)) //comido
		{

		}
	}
	float distFromPlayer;
	void OnProcessAI(){};
	void OnPrepare(){}; 
	void OnDraw(CCamera *camera);
	void Load(); //cargar el modelo protagonista

	
public:
	CPlayer* playerInf;
	CArb1() {   size = 3.25f; 	  // " terreno. (colision bound sphere)
				velocity = CVector(0.0, 0.0, 0.0); // speed of the player
				bDelete = false; 
				Load(); 
			}
	CArb1(int x, int z) { 
				position.x = x;
				position.z = z;

				velocity = CVector(0.0, 0.0, 0.0); // speed of the player
				size = 3.25f; 	  // " terreno. (colision bound sphere)	
				bDelete = false; 
				Load(); 
			}

	~CArb1() {}
	void SetPlayer(CPlayer* pl) { playerInf = pl;}

};

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

#endif  
     