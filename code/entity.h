#ifndef __ENTITY_H
#define __ENTITY_H
/****************************************************************************
ENTITY.H
The CEntity class:  The CEntity class is derived from CMD2Model and
		         provides the functionality of an entity in the
			   game world. It holds the current MD2 animation
			   state, the entity angle heading, and the entity's
			   primary sound.

 Author   :   Javier Palmer
 Date     :   2/1/2005

 Written for the FATMAN Game
*****************************************************************************/
#include <stdlib.h>
#include <time.h>
#include <typeinfo.h>

#include "md2.h"
#include "object.h"
#include "camera.h"
#include "audiosystem.h"
#include "terrain.h"
#include "explosion.h"
#include "Particles.h"

class CEntity : public CMD2Model
{
protected:
	// funciones de las entidades
	 void OnAnimate(float deltaTime);
     void OnDraw(CCamera *camera);
     void OnCollision(CObject *collisionObject);
     void OnPrepare();

public:
     float direction;         // angle the entity is facing (in radians)
     CAudio *entitySound;     // the sound the entity makes
                              // currently only supports one sound
							  // per entity
	 CAudioSystem *audioSys;	// a pointer to the audio system                          

     CEntity();
     ~CEntity();

     int stateStart, stateEnd;     // state keyframe start/end
     float deltaT;
     float animSpeed;

     void LoadAudio(CAudioSystem *audioSystem, char *filename, bool is3DSound);
};

#endif