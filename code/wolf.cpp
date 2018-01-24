#include "wolf.h"
#define pop_limit 85
/****************************************************************************
Wolf.CPP
The CWolfEnemy class implementation: 

 Author   :   Javier Palmer
 Date     :   2/3/2005

 Written for the FATMAN Game
*****************************************************************************/
void CWolfEnemy::OnPrepare() 
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
          direction = dirToPlayer+90;          // set the direction of the enemy
                                                                      // -90 to 90 degrees
          modelState = MODEL_RUN;
          velocity = CVector(0.0, 0.0, 15.0);
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
               velocity = CVector(0.0, 0.0, 15.0);
               modelState = MODEL_RUN;
          }
          break;
     case AI_MUERE:
          modelState = MODEL_DIE;
          velocity = CVector(0.0, 0.0, 0.0);
          if (nextFrame == stateStart)
          {
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
				//aullido = audioSys->Create("data\\music\\aw.wav",1);
				//audioSys->Play(aullido,0);
			    isExplosion = true;
			    explosion = new CExplosion(500, position, 12.0, explosionTex->texID, 0.6, 0.9, 0.7);
                
			 }
          }
          break;
     default:
          break;
     }

     // do prep for MD2 Model states
     CEntity::OnPrepare();
}



void CWolfEnemy::OnProcessAI()
{
     // calculate distance from player
     CVector diff = player->position - position;

      if (aiState != AI_MUERE)
     {
         // if the player is close enough, the enemy
          distFromPlayer = sqrt(diff.x*diff.x + diff.y*diff.y + diff.z*diff.z);
          if (distFromPlayer < 50.0)
               aiState = AI_ATACA;
          else
               aiState = AI_VIGILA;
    } 
}

void CWolfEnemy::Load()
{
	// load model
	CMD2Model::Load("data\\model\\wolf.md2", "data\\model\\wolfskin.pcx");
	// load particulas
	explosionTex->LoadTexture("data\\texture\\explosion2.bmp");
	SetupExplosionTexture();
}

void CWolfEnemy::OnDraw(CCamera *camera)
{
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

void CWolfEnemy::SetupExplosionTexture()
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


void CWolfEnemy::OnAnimate(float deltaTime)
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
