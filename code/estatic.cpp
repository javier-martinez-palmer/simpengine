#include "player.h"
#include "camera.h"
#include "fruta.h"
#include "estatic.h"
#include <gl/glut.h>
#include "texture.h"


void CObj::OnDraw(CCamera *camera)
{

	glGenTextures(1, &murtex->texID);
	glBindTexture(GL_TEXTURE_2D, murtex->texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	//or GL_CLAMP
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	//or GL_CLAMP

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, murtex->width, murtex->height,
					GL_RGB, GL_UNSIGNED_BYTE, murtex->data);

    glEnable(GL_TEXTURE_2D);

glPushMatrix();
	//generamos la pared izq.
	glTranslatef(340, 0 ,120);//
	glRotatef(-90, 0.0, 1.0, 0.0);
	glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
	glScalef(37.0, 2.0,1.5);	//longitud,
	CreaPared();

glPopMatrix();

glPushMatrix();
	//generamos la pared der.	
	glTranslatef(120, 0 ,340);
	glRotatef(-direction, 0.0, 1.0, 0.0);
	glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
	glScalef(37.0, 2.0,1.5);	
	CreaPared();

glPopMatrix();

glPushMatrix();
	//generamos la pared izq_ant.	
	glTranslatef(120, 0 ,58);
	glRotatef(-direction, 0.0, 1.0, 0.0);
	glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
	glScalef(48.0, 2.0,1.5);	
//	CreaPared();
	glTranslatef(5, 5,15);
	glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
	CreaPared();

glPopMatrix();

glPushMatrix();
	//generamos la pared der_ant.	
	glTranslatef(58, 0 ,120);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
	glScalef(48.3, 2.0,1.5);	
//	CreaPared();
	glTranslatef(5, 5,15);
	glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
	CreaPared();

glPopMatrix();

//    glDisable(GL_TEXTURE_2D);
  	glEnable(GL_FOG);

}


void CObj::CreaPared()
{
	glBindTexture(GL_TEXTURE_2D,murtex->texID);
glPushMatrix();
  	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0);	
  	// tamaño.

  	GLfloat x= -10.0, z = -5.0;
  	// necesitamos crear el plano con muchos "quads" si queremos ver el efecto de la niebla
  	for (GLint i = 0; i < 8; i++, x += 2)
  	{
    	for (GLint j = 0; j < 8; j++, z += 2)
    	{
      	glTexCoord2f(0.0f, 0.0f); 
		glVertex3f(x, 0, z);
      	glTexCoord2f(-15.0f, 0.0f); 
		glVertex3f(x + 2.0, 0, z);
      	glTexCoord2f(-15.0f, 0.5f); 
		glVertex3f(x + 2.0, 0, z + 2.0);
     	glTexCoord2f(0.0f, 0.5f); 
		glVertex3f(x, 0, z + 2.0);
    	}
    	z = -5.0;
  	}
	
  	glEnd();
glPopMatrix();

}