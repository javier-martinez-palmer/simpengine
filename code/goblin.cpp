#include "goblin.h"
#define pop_limit 85
/****************************************************************************
Goblin.CPP
 The CGoblinEnemy class implementation:
 Author   :   Javier Palmer
 Date     :   2/3/2005

 Written for the FATMAN Game
*****************************************************************************/
void CGoblinEnemy::OnProcessAI()
{
     // calculate distance from player
     CVector diff = player->position - position;

     if (aiState != AI_MUERE)
     {
         // if the player is close enough, the enemy should become scared
          distFromPlayer = sqrt(diff.x*diff.x + diff.y*diff.y + diff.z*diff.z);
          if (distFromPlayer < 80.0)
               aiState = AI_ATACA;
          else
               aiState = AI_VIGILA;
	 } 
}

void CGoblinEnemy::OnPrepare() 
{
     float dirToPlayer;  // the angle of the enemy-player vector

     CVector diff;       // the vector from the enemy to the player
     diff.x = position.x - player->position.x;
     diff.z = position.z - player->position.z;
     diff.Normalize();

   // find the angle in the world of the vector from the enemy to the player
     // in relation the negative z-axis
     dirToPlayer = RAD2DEG(diff.Angle(CVector(0,0,-1)));

     // seed random generator
     srand((unsigned int)time(NULL));

     OnProcessAI();
     // now do Wolf prep
     // set modelState based on AIstate
     switch (aiState)
     {
     case AI_ATACA:
          direction = (dirToPlayer - 90) + ((rand()%90)-45);          // set the direction of the enemy
                                                                      // -90 to 90 degrees
          modelState = MODEL_RUN;
          velocity = CVector(0.0, 0.0, 20.0);
          break;
     case AI_VIGILA:
          direction = float(rand() % 360);
          if ((rand() % 4) != 0)
          {
               modelState = MODEL_IDLE;
               velocity = CVector(0.0, 0.0, 0.0);
          }
          else
          {
               velocity = CVector(0.0, 0.0, 20.0);
               modelState = MODEL_RUN;
          }
          break;
     case AI_MUERE:
          modelState = MODEL_DIE;
          velocity = CVector(0.0, 0.0, 0.0);
			 // si está en explosion -> comprobamos si termina.
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
			    isExplosion = true;
			    explosion = new CExplosion(200, position, 6.0, explosionTex->texID, 0.2, 0.2, 0.9);
			    //PlaySound();
                // time to kill the monster
                
			 }
		  break;
     default:
          break;
     }

     // do prep for MD2 Model states
     CEntity::OnPrepare();
}

void CGoblinEnemy::Load()
{
	// load model
	CMD2Model::Load("data\\model\\mas.md2", "data\\model\\mas.pcx"); 
	// load particulas
	explosionTex->LoadTexture("data\\texture\\explosion.bmp");
	SetupExplosionTexture();
}

void CGoblinEnemy::OnDraw(CCamera *camera)
{

	if(!isExplosion && (distFromPlayer < pop_limit)){
		glTranslatef(position.x, position.y, position.z);
		glRotatef(-direction, 0.0, 1.0, 0.0);
		glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
		glScalef(0.2, 0.2, 0.2);		
		AnimateModel(stateStart, stateEnd, deltaT*animSpeed);
	}
	if(isExplosion){
		glDisable(GL_FOG);
		explosion->Render();
		glEnable(GL_FOG);
	}
}

void CGoblinEnemy::SetupExplosionTexture()
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


void CGoblinEnemy::OnAnimate(float deltaTime)
{
	if(!isExplosion){
		float cosYaw = (float)cos(DEG2RAD(direction));
		float sinYaw = (float)sin(DEG2RAD(direction)); 

		float speed = velocity.z * deltaTime;

		if ((direction >= 360.0f) || (direction <= -360.0f))
			direction = 0.0f;

		position.x += float(cosYaw)*speed;
		position.z += float(sinYaw)*speed;
		if(currentFrame < 100 && currentFrame > 90) // añadido para que salte más alto!!!.
			position.y += 7.0;

		deltaT = deltaTime;	// used for interpolation
	}
	if(isExplosion)
		explosion->Update(deltaTime);
		
}
