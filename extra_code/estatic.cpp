/****************************************************************************
ESTATIC.CPP
In this class is were Cg operates.
 
 Author   :   Javier Palmer
 Date     :   2/3/2005

 Written for the FATMAN Game
*****************************************************************************/
#include "player.h"
#include "camera.h"
#include "fruta.h"
#include "estatic.h"
#include <gl/glut.h>
#include "texture.h"

#ifndef CWD
# define CWD ""
#endif

#define		TWO_PI 6.2831853071	
GLfloat		wave_movement = 0.0f;	

void CObj::OnDraw(CCamera *camera)
{
	cgGLEnableProfile(profile);
	cgGLBindProgram(program);
	cgGLEnableProfile(tprof);
	cgGLBindProgram(tprog);
	CheckCgError();


glPushMatrix();
	//generamos la pared izq.
	glTranslatef(340, 0 ,120);//
	glRotatef(-90, 0.0, 1.0, 0.0);
	glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
	glScalef(44.1, 2.0,1.5);	//longitud,
	CreaPared();

glPopMatrix();

glPushMatrix();
	//generamos la pared der.	
	glTranslatef(120, 0 ,340);
	glRotatef(-direction, 0.0, 1.0, 0.0);
	glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
	glScalef(44.1, 2.0,1.5);	
	CreaPared();
glPopMatrix();
//comenta las dos lineas siguientes para añadir efectos a las paredes anteriores
   cgGLDisableProfile(profile);
   cgGLDisableProfile(tprof);

glPushMatrix();
	//generamos la pared izq_ant.	
	glTranslatef(120, 0 ,58);
	glRotatef(-direction, 0.0, 1.0, 0.0);
	glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
	glScalef(48.0, 2.0,1.5);	
//	CreaPared();
	glTranslatef(5,5,15);
	glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
	CreaPared_s();

glPopMatrix();

glPushMatrix();
	//generamos la pared der_ant.	
	glTranslatef(58, 0 ,120);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
	glScalef(48.0, 2.0,1.5);	
//	CreaPared();
	glTranslatef(5, 5,15);
	glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
	CreaPared_s();

glPopMatrix();

    glDisable(GL_TEXTURE_2D);
  	glEnable(GL_FOG);
   cgGLDisableProfile(profile);
   cgGLDisableProfile(tprof);

}


void CObj::CreaPared()
{
	//vertex program
	cgGLSetStateMatrixParameter(cgGetNamedParameter(program,"ModelViewProj"),
			CG_GL_MODELVIEW_PROJECTION_MATRIX,
			CG_GL_MATRIX_IDENTITY);
	cgGLSetStateMatrixParameter(cgGetNamedParameter(program,"ModelView"),
			CG_GL_MODELVIEW_MATRIX,
			CG_GL_MATRIX_IDENTITY);
	cgGLSetStateMatrixParameter(cgGetNamedParameter(program,"ModelViewIT"),
			CG_GL_MODELVIEW_MATRIX,
			CG_GL_MATRIX_INVERSE_TRANSPOSE);

	wave = cgGetNamedParameter(program,"IN.wave");

    		    glGenTextures(1, &murtex->texID);
				glBindTexture(GL_TEXTURE_2D, murtex->texID);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	//or GL_CLAMP
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	//or GL_CLAMP

				gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, murtex->width, murtex->height,
					GL_RGB, GL_UNSIGNED_BYTE, murtex->data);

			    glEnable(GL_TEXTURE_2D);

	// fragment program
	cgGLSetTextureParameter(cgGetNamedParameter(tprog,"decal"),murtex->texID);
	glEnable(GL_TEXTURE_2D);	
	cgGLEnableTextureParameter(cgGetNamedParameter(tprog,"decal"));

glPushMatrix();
  	glBegin(GL_QUADS);
  	glNormal3f(0.0, 1.0, 0.0);	
  	// tamaño.
  	GLfloat x= -15.0, z = -5.0;
  	// necesitamos crear el plano con muchos "quads" si queremos ver el efecto de la niebla
  	for (GLint i = 0; i < 20; i++, x += 1)
  	{
    	for (GLint j = 0; j < 20; j++, z += 1)
    	{
		cgGLSetParameter3f(wave, wave_movement, 0.1f, 0.1f);
		glTexCoord2f(0.0f, 0.0f); 
		glVertex3f(x, -0.1, z);
      	glTexCoord2f(-15.0f, 0.0f); 
		glVertex3f(x + 1.0, -0.1, z);
      	glTexCoord2f(-15.0f, 0.5f); 
		glVertex3f(x + 1.0, -0.1, z + 1.0);
     	glTexCoord2f(0.0f, 0.5f); 
		glVertex3f(x, -0.1, z + 1.0);
		wave_movement += 0.00001f;
		if (wave_movement > TWO_PI)									// Prevent Crashing
			wave_movement = 0.0f;
    	}
    	z = -5.0;
  	}
  	glEnd();
glPopMatrix();
	cgGLDisableTextureParameter(cgGetNamedParameter(tprog,"decal"));
}



void CObj::CreaPared_s()
{
	//vertex program
	cgGLSetStateMatrixParameter(cgGetNamedParameter(program,"ModelViewProj"),
			CG_GL_MODELVIEW_PROJECTION_MATRIX,
			CG_GL_MATRIX_IDENTITY);
	cgGLSetStateMatrixParameter(cgGetNamedParameter(program,"ModelView"),
			CG_GL_MODELVIEW_MATRIX,
			CG_GL_MATRIX_IDENTITY);
	cgGLSetStateMatrixParameter(cgGetNamedParameter(program,"ModelViewIT"),
			CG_GL_MODELVIEW_MATRIX,
			CG_GL_MATRIX_INVERSE_TRANSPOSE);



    		    glGenTextures(1, &murtex->texID);
				glBindTexture(GL_TEXTURE_2D, murtex->texID);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	//or GL_CLAMP
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	//or GL_CLAMP

				gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, murtex->width, murtex->height,
					GL_RGB, GL_UNSIGNED_BYTE, murtex->data);

			    glEnable(GL_TEXTURE_2D);
	cgGLSetTextureParameter(cgGetNamedParameter(tprog,"decal"),murtex->texID);
	glEnable(GL_TEXTURE_2D);	
	cgGLEnableTextureParameter(cgGetNamedParameter(tprog,"decal"));

glPushMatrix();
  	glBegin(GL_QUADS);
  	glNormal3f(0.0, 1.0, 0.0);	
  	// tamaño.
  	GLfloat x= -15.0, z = -5.0;
  	// necesitamos crear el plano con muchos "quads" si queremos ver el efecto de la niebla
  	for (GLint i = 0; i < 20; i++, x += 1)
  	{
    	for (GLint j = 0; j < 20; j++, z += 1)
    	{
		glTexCoord2f(0.0f, 0.0f); 
		glVertex3f(x, -0.1, z);
      	glTexCoord2f(-15.0f, 0.0f); 
		glVertex3f(x + 1.0, -0.1, z);
      	glTexCoord2f(-15.0f, 0.5f); 
		glVertex3f(x + 1.0, -0.1, z + 1.0);
     	glTexCoord2f(0.0f, 0.5f); 
		glVertex3f(x, -0.1, z + 1.0);
    	}
    	z = -5.0;
  	}
  	glEnd();
glPopMatrix();
	cgGLDisableTextureParameter(cgGetNamedParameter(tprog,"decal"));
}

void CObj::ChooseProfiles()
{
    // Make sure that the appropriate profiles are available on the
    // user's system.
    if (cgGLIsProfileSupported(CG_PROFILE_ARBVP1))
        profile = CG_PROFILE_ARBVP1;
    else {
        // try VP30
        if (cgGLIsProfileSupported(CG_PROFILE_VP30))
            profile = CG_PROFILE_VP30;
        else {
            fprintf(stderr, "Neither arbvp1 or vp30 vertex profiles supported on this system.\n");
            exit(1);
        }
    }

    if (cgGLIsProfileSupported(CG_PROFILE_ARBFP1))
        tprof = CG_PROFILE_ARBFP1;
    else {
        // try FP30
        if (cgGLIsProfileSupported(CG_PROFILE_FP30))
            tprof = CG_PROFILE_FP30;
        else {
            fprintf(stderr, "Neither arbvp1 or vp30 vertex profiles supported on this system.\n");
            exit(2);
        }
    }
/**/
}


void CObj::LoadCgPrograms()
{
    // Load and compile the vertex program from demo_vert.cg; hold on to the
    // handle to it that is returned.
    program = cgCreateProgramFromFile(context, CG_SOURCE, CWD "vertex.cg",
                                            profile, NULL, NULL);
    if (program==0)
		exit(1);

	if (!cgIsProgramCompiled(program))
        cgCompileProgram(program);

    // Enable the appropriate vertex profile and load the vertex program.
    cgGLLoadProgram(program);
   
	// Fragment
	// Program
    tprog = cgCreateProgramFromFile(context, CG_SOURCE, CWD "fragment.cg",
                                            tprof, NULL, NULL);
    if (tprog==0)
		exit(4);

	if (!cgIsProgramCompiled(tprog))
        cgCompileProgram(tprog);

    // Enable the appropriate vertex profile and load the vertex program.
    cgGLLoadProgram(tprog);

}
