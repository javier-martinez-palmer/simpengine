#include "arb1.h"
/****************************************************************************
 Arb1.h 
 
 Author   :   Javier Palmer
 Date     :   2/3/2005

 Written for the FATMAN Game
*****************************************************************************/
#define pop_limit 80


void CArb1::Load()
{
	// load model
	CMD2Model::Load("data\\world\\evileye.md2", "data\\world\\evileye.pcx");
	CMD2Model::SetState(MODEL_IDLE); 
}


void CArb1::OnDraw(CCamera *camera)
{	
         CVector diff;       // the vector from the enemy to the player
         diff.x = position.x - playerInf->position.x;
         diff.z = position.z - playerInf->position.z;
         //diff.Normalize();
         distFromPlayer = sqrt(diff.x*diff.x + diff.z*diff.z);
		 if(distFromPlayer < pop_limit){
		glEnable(GL_TEXTURE);
		glTranslatef(position.x, position.y-1.0, position.z);
		glRotatef(-direction, 0.0, 1.0, 0.0);
		glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
		//glScalef(0.25, 0.25, 0.25);
	    AnimateModel(0, 1, deltaT*animSpeed);
		 }
}
