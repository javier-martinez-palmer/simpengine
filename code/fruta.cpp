#include "player.h"
#include "camera.h"
#include "fruta.h"
#define pop_limit 85
/****************************************************************************
FRUTA.CPP

 Author   :   Javier Palmer
 Date     :   2/3/2005

 Written for the FATMAN Game
*****************************************************************************/


//DEFINICION SOBRE LOS CAMBIOS DE ESTADO
void CFruta::OnProcessAI()
{
    if (aiState != AI_EATED)
     {
         // Si ha pasado bastante tiempo desde que se interaccionó con el personaje,
		 // podemos pasar el player a AI_FRESH
		  if (aiState == AI_FRESH)
		  {
			aiState = AI_FRESH;
		  }
/* 		  if (aiState == AI_EATED)
		  {
			isExplosion = true;
		  }
          else
            aiState = AI_FRESH;
*/	 }
}

void CFruta::OnPrepare() 
{

     switch (aiState)
     {
     case AI_FRESH:

		  modelState = MODEL_IDLE;
          velocity = CVector(0.0, 0.0, 0.0);
          break;
     case AI_EATED:		 
		  // si está en explosion   -> comprobamos cuando termina
		  if (isExplosion)
		  {
			if (explosion->IsDead() )//&& !audioSys->GetPerformance()->IsPlaying(entitySound->GetSegment(), NULL))
			{
				explosion->KillSystem();
				delete explosion;
				explosion = NULL;
				isExplosion = false;
				bDelete = true;
			}
		  }
		  // si NO está en explosion   ->  lo inicializamos
		  if(!isExplosion)
		  {
			//Explosion
			isExplosion = true;
			explosion = new CExplosion(50, position, 8.0, explosionTex->texID, 1.0, 0.01, 1.0);

		  }
         break;
     default:
          break;
     }

     // do prep for MD2 Model states
     CEntity::OnPrepare();
}

void CFruta::Load()
{
	// load model
	CMD2Model::Load("data\\world\\naranja2.md2", "data\\world\\fruta8.pcx");
	CMD2Model::SetState(MODEL_IDLE); 
	// load particulas
	explosionTex->LoadTexture("data\\texture\\explosion.bmp");
	SetupExplosionTexture();
}


void CFruta::OnDraw(CCamera *camera)
{	
         CVector diff;       // the vector from the enemy to the player
         diff.x = position.x - playerInf->position.x;
         diff.z = position.z - playerInf->position.z;
         //diff.Normalize();
         distFromPlayer = sqrt(diff.x*diff.x + diff.z*diff.z);

	if(!isExplosion && (distFromPlayer < pop_limit)){
		glTranslatef(position.x, position.y, position.z);
		glRotatef(-direction, 0.0, 1.0, 0.0);
		glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
		glScalef(0.25, 0.25, 0.25);
	    AnimateModel(stateStart, stateEnd, deltaT*animSpeed);
	}
	if(isExplosion){
		glDisable(GL_FOG);
		explosion->Render();
		glEnable(GL_FOG);
	}
}


void CFruta::SetupExplosionTexture()
{
	glGenTextures(1, &explosionTex->texID);
	glBindTexture(GL_TEXTURE_2D, explosionTex->texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, explosionTex->width, explosionTex->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, explosionTex->data);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, explosionTex->width, explosionTex->height, GL_RGBA, GL_UNSIGNED_BYTE, explosionTex->data);
}


void CFruta::OnAnimate(float deltaTime)
{
	if(!isExplosion){
		deltaT = deltaTime;	// used for interpolation
	}
	if(isExplosion)
		explosion->Update(deltaTime);
		
}
