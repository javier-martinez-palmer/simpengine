#include "player.h"
#include "camera.h"
#include <gl/glut.h>



void CPlayer::OnPrepare() 
{
     //OnProcessAI();
	 if (camara)
		{
			position = camara->position;		// the player stays with the camera
			position.x = camara->position.x;  // down de camera.(se puede eliminar???)
			direction = camara->yaw;
			pitch = camara->pitch;
		}

     switch (aiState)
     {
	 case AI_OPERATIV:
		 modelState = MODEL_RUN;	
		  break;
     case AI_UNCARING:
         modelState = MODEL_IDLE;
         velocity = CVector(0.0, 0.0, 0.0);
          break;
     case AI_DEAD:
		 // grito = audioSys->Create("data\\music\\gri.wav",0);
		 // audioSys->Play(grito,0);
           velocity = CVector(0.0, 0.0, 0.0);
		   modelState = MODEL_DIE;
          if (nextFrame == stateStart)
          {
               // time to kill the monster
               bDelete = true;
          }

          break;
	 case AI_JUMP:
		 if (nextFrame >= 109){
			 modelState = MODEL_IDLE;
		     aiState = AI_UNCARING;
		 }
		 else
			 modelState = MODEL_JUMP;
		 break;
     default:
          break;
     }

     // do prep for MD2 Model states
     CEntity::OnPrepare();
}

void CPlayer::Load()
{
	// load model
	CMD2Model::Load("data\\model\\tris.md2", "data\\model\\ogrobase.pcx");
}

void CPlayer::SetShadowMatrix( GLfloat destMat[16])
{
	GLfloat dot;
	float plane[4] = {0.0, 1.0, 0.0, 0.0};
	float lightPos[4] = {position.x - 4.0,position.y + 20.0, position.z + 3.0, 1.0};
	//dot product nos permite averiguar el angulo entre dos vectores
	dot = plane[0] * lightPos[0] +	plane[1] * lightPos[1] + plane[2] * lightPos[2] + plane[3] * lightPos[3];
	
	//first column
	destMat[0]= dot - lightPos[0] * plane[0];
	destMat[4]= 0.0f - lightPos[0] * plane[1];
	destMat[8]= 0.0f - lightPos[0] * plane[2];
	destMat[12]= 0.0f - lightPos[0] * plane[3];
	//second column
	destMat[1]= 0.0f - lightPos[1] * plane[0];
	destMat[5]= dot - lightPos[1] * plane[1];
	destMat[9]= 0.0f - lightPos[1] * plane[2];
	destMat[13]= 0.0f - lightPos[1] * plane[3];
	//third column
	destMat[2]= 0.0f - lightPos[2] * plane[0];
	destMat[6]= 0.0f - lightPos[2] * plane[1];
	destMat[10]= dot - lightPos[2] * plane[2];
	destMat[14]= 0.0f - lightPos[2] * plane[3];
	//fourth column
	destMat[3]= 0.0f - lightPos[3] * plane[0];
	destMat[7]= 0.0f - lightPos[3] * plane[1];
	destMat[11]= 0.0f - lightPos[3] * plane[2];
	destMat[15]= dot - lightPos[3] * plane[3];
}

void CPlayer::OnDraw(CCamera *camera)
{

glEnable(GL_STENCIL_TEST);
glPushMatrix();
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glStencilFunc(GL_EQUAL,1,1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);

	// Projection
	SetShadowMatrix(g_shadowMatrix);
	glMultMatrixf(g_shadowMatrix);

	// Draw 
	glTranslatef(position.x, position.y, position.z);
	glRotatef(-direction, 0.0, 1.0, 0.0);
	glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
	glScalef(0.2, 0.2, 0.2);

	AnimateModel(stateStart, stateEnd, deltaT*animSpeed,1); //shadow
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
glPopMatrix();
	glDisable(GL_STENCIL_TEST);

	glTranslatef(position.x, position.y, position.z);
	glRotatef(-direction, 0.0, 1.0, 0.0);
	glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
	glScalef(0.2, 0.2, 0.20);
	AnimateModel(stateStart, stateEnd, deltaT*animSpeed); //model


}

