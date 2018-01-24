/*************************************************************************/
/*  NOMBRE PROFESSOR DE PRACTICAS ASPECTOS QUE QUEREMOS DESTACAR          */
/*                                                                       */
/*                 glig.c LIBRERIA DE MODELADO GEOMETRICO	             */
/*                                                                       */
/*   Rev. 2.0  01/01/2002   AUTORES: O. Belmonte, M. Chover, J. Ribelles */
/*                                                                       */
/*************************************************************************/

/***************** INCLUDES DE LAS LIBRERIAS NECESARIAS ******************/
#include <gl/glut.h>
#include <math.h>
#include <stdio.h>
#include "glig.h"

#define PI 3.1415926535897932
#define ALFA (0.5-v)*PI
#define BETA 2*PI*u

/************************* FUNCIONES BASICAS **********************************************/
/******************************************************************************************/
/* Devuelve la coordenada de un punto en R3 a partir de un punto (u,v)                    */
/*   de un espacio parametrico en R2                                                      */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La coordenada x de un punto en R3                                              */
/******************************************************************************************/
float xSuperQuadric (float u, float v, float R, float s1, float s2)
{
	float cosalfa, cosbeta, powcosalfa, powcosbeta;

	cosalfa = (float)cos(ALFA);
	cosbeta = (float)cos(BETA);

	if(cosalfa > 0.0)
		powcosalfa = (float)pow(cosalfa,s1);
	else
		powcosalfa =(float) - pow(- cosalfa,s1);

	if(cosbeta > 0.0)
		powcosbeta = (float)pow(cosbeta,s2);
	else
		powcosbeta = (float) - pow(- cosbeta,s2);

	return (R*powcosalfa*powcosbeta);

}


/******************************************************************************************/
/* Devuelve la coordenada de un punto en R3 a partir de un punto (u,v)                    */
/*   de un espacio parametrico en R2                                                      */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La coordenada y de un punto en R3                                              */
/******************************************************************************************/
float ySuperQuadric (float u, float v, float R, float s1, float s2)
{
	float sinalfa, powsinalfa;

	sinalfa = (float)sin(ALFA);

	if(sinalfa > 0.0)
		powsinalfa = (float)pow(sinalfa,s1);
	else
		powsinalfa = (float)- pow(- sinalfa,s1);

	return (R*powsinalfa);
}


/******************************************************************************************/
/* Devuelve la coordenada de un punto en R3 a partir de un punto (u,v)                    */
/*   de un espacio parametrico en R2                                                      */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La coordenada z de un punto en R3                                              */
/******************************************************************************************/
float zSuperQuadric(float u, float v, float R, float s1, float s2)
{
	float cosalfa, sinbeta, powcosalfa, powsinbeta;

	cosalfa = (float)cos(ALFA);
	sinbeta=(float)sin(BETA);

	if(cosalfa > 0.0)
		powcosalfa = (float)pow(cosalfa,s1);
	else
		powcosalfa=(float) - pow(- cosalfa,s1);

	if(sinbeta > 0.0)
		powsinbeta = (float)pow(sinbeta,s2);
	else
		powsinbeta = (float) - pow(- sinbeta,s2);

	return(R*powcosalfa*powsinbeta);
}


/******************************************************************************************/
/* Calcula la variacion en x para un incremento de u, derivada de x con respecto de u     */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La variacion de x con u                                                        */
/******************************************************************************************/
float dxuSuperQuadric(float u, float v, float R, float s1, float s2)
{
	return((xSuperQuadric(u+E,v,R,s1,s2)-xSuperQuadric(u-E,v,R,s1,s2))/(2*E));
}


/******************************************************************************************/
/* Calcula la variacion en y para un incremento de u, derivada de y con respecto de u     */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La variacion de y con u                                                        */
/******************************************************************************************/
float dyuSuperQuadric(float u, float v, float R, float s1, float s2)
{
	return((ySuperQuadric(u+E,v,R,s1,s2)-ySuperQuadric(u-E,v,R,s1,s2))/(2*E));
}


/******************************************************************************************/
/* Calcula la variacion en z para un incremento de u, derivada de z con respecto de u     */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La variacion de z con u                                                        */
/******************************************************************************************/
float dzuSuperQuadric(float u, float v, float R, float s1, float s2)
{
	return((zSuperQuadric(u+E,v,R,s1,s2)-zSuperQuadric(u-E,v,R,s1,s2))/(2*E));
}


/******************************************************************************************/
/* Calcula la variacion en x para un incremento de v, derivada de x con respecto de v     */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La variacion de x con v                                                        */
/******************************************************************************************/
float dxvSuperQuadric(float u, float v, float R, float s1, float s2)
{
	return((xSuperQuadric(u,v+E,R,s1,s2)-xSuperQuadric(u,v-E,R,s1,s2))/(2*E));
}


/******************************************************************************************/
/* Calcula la variacion en y para un incremento de u, derivada de y con respecto de v     */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La variacion de y con u                                                        */
/******************************************************************************************/
float dyvSuperQuadric(float u, float v, float R, float s1, float s2)
{
	return((ySuperQuadric(u,v+E,R,s1,s2)-ySuperQuadric(u,v-E,R,s1,s2))/(2*E));
}

/******************************************************************************************/
/* Calcula la variacion en z para un incremento de u, derivada de z con respecto de v     */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La variacion de z con u                                                        */
/******************************************************************************************/
float dzvSuperQuadric(float u, float v, float R, float s1, float s2)
{
	return((zSuperQuadric(u,v+E,R,s1,s2)-zSuperQuadric(u,v-E,R,s1,s2))/(2*E));
}

/******************************************************************************************/
/* Calcula la componente x del vector normal a la supercuadrica en (u,v)                  */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: Componente x del vector normal                                                 */
/******************************************************************************************/
float nxSuperQuadric(float u, float v, float R, float s1, float s2)
{
	if (v<= E) v= F;
	if (v>= 1-E) v= 1-F;
	return(dyuSuperQuadric(u,v,R,s1,s2)*dzvSuperQuadric(u,v,R,s1,s2)-
		dyvSuperQuadric(u,v,R,s1,s2)*dzuSuperQuadric(u,v,R,s1,s2));
}

/******************************************************************************************/
/* Calcula la componente y del vector normal a la supercuadrica en (u,v)                  */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: Componente y del vector normal                                                 */
/******************************************************************************************/
float nySuperQuadric(float u, float v, float R, float s1, float s2)
{
	if (v<= E) v= F;
	if (v>= 1-E) v= 1-F;
	return(dxvSuperQuadric(u,v,R,s1,s2)*dzuSuperQuadric(u,v,R,s1,s2)-
		dxuSuperQuadric(u,v,R,s1,s2)*dzvSuperQuadric(u,v,R,s1,s2));
}

/******************************************************************************************/
/* Calcula la componente z del vector normal a la supercuadrica en (u,v)                  */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: Componente z del vector normal                                                 */
/******************************************************************************************/
float nzSuperQuadric(float u, float v, float R, float s1, float s2)
{
	if (v<= E) v= F;
	if (v>= 1-E) v= 1-F;
	return(dxuSuperQuadric(u,v,R,s1,s2)*dyvSuperQuadric(u,v,R,s1,s2)-
		dxvSuperQuadric(u,v,R,s1,s2)*dyuSuperQuadric(u,v,R,s1,s2));
}









/********************** RUTINA DE DIBUJO *********************************/
/******************************************************************************************/
/* Crea una cuadrica segun los parametros que se le pasan                                 */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/*             float uMax --> Valor maximo que alcanza el parametro u                     */
/*             float vMax --> Valor maximo que alcanza el parametro v                     */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1, float s2 --> Definen la forma de la cuadrica                     */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igCreateQuadricObject (int pu, int pv, float uMax, float vMax, float R, float s1, float s2)
{ 
    float u, v, inc_u, inc_v; 
    float x, y, z; 
    int i;
	int j;

    v =0.0; 
    u =0.0; 
    inc_u = uMax/pu; /* donde 10 es el número de puntos en u */ 
	inc_v = vMax/pv;

	for (j = 0; j <= pv; j++)
	{
		glBegin (GL_LINE_LOOP); 
			for (i= 0; i< pu; i++)
			{ 
				x= xSuperQuadric (u, v, R, s1, s2); 
				y= ySuperQuadric (u, v, R, s1, s2); 
				z= zSuperQuadric (u, v, R, s1, s2); 
				glVertex3f (x, y, z); 
				u= u+ inc_u; 
			} 
		glEnd(); 
		v = v + inc_v;
		u = 0.0f;
	}

	v = 0.0f;
	u = 0.0f;
	for (i = 0; i < pu; i++)
	{
		glBegin (GL_LINE_STRIP);
			for (j = 0; j <= pv; j++)
			{
				x= xSuperQuadric (u, v, R, s1, s2); 
				y= ySuperQuadric (u, v, R, s1, s2); 
				z= zSuperQuadric (u, v, R, s1, s2); 
				glVertex3f (x, y, z); 
				v = v + inc_v;
			}
		glEnd ();
		u = u + inc_u;
		v = 0.0f;
	}
}

/*******************************************************************************************/
/* La misma función pero para texturizar												   */
/*******************************************************************************************/

void igCreateSolidQuadricObject (int pu, int pv, float uMax, float vMax, float R, float s1, float s2, int numtext)
{ 
    float u, v, inc_u, inc_v; 
    float x, y, z; 
    float nx, ny, nz;
	int i;
	int j;

    v = 0.0; 
    u =0.0; 
    inc_u = uMax/pu; /* donde 10 es el número de puntos en u */ 
	inc_v = vMax/pv;

	for (j = 0; j < pv; j++)
	{
		glBegin (GL_TRIANGLE_STRIP); 
			for (i= 0; i<= pu; i++)
			{ 
				x= xSuperQuadric (u, v, R, s1, s2); 
				y= ySuperQuadric (u, v, R, s1, s2); 
				z= zSuperQuadric (u, v, R, s1, s2); 
				
				nx= nxSuperQuadric (u, v, R, s1, s2); 
				ny= nySuperQuadric (u, v, R, s1, s2); 
				nz= nzSuperQuadric (u, v, R, s1, s2); 
				
				glNormal3f(nx,ny,nz);
				glTexCoord2f(u*numtext, v*numtext);
				glVertex3f (x, y, z);
				

				x= xSuperQuadric (u, v+inc_v, R, s1, s2); 
				y= ySuperQuadric (u, v+inc_v, R, s1, s2); 
				z= zSuperQuadric (u, v+inc_v, R, s1, s2); 
				
				nx= nxSuperQuadric (u, v+inc_v, R, s1, s2); 
				ny= nySuperQuadric (u, v+inc_v, R, s1, s2); 
				nz= nzSuperQuadric (u, v+inc_v, R, s1, s2); 
				
				glNormal3f(nx,ny,nz);	
				glTexCoord2f(u*numtext, numtext*(v+inc_v));
				glVertex3f (x, y, z); 
			

				u= u+ inc_u; 
			} 
		glEnd(); 
		v = v + inc_v;
		u = 0.0f;
	}

}


/************************************************************************************************/
/*OTRAS FUNCIONES               
/************************************************************************************************/

void igWireCaja(float largo,float alto, float ancho){

	float a,b,c;
	a=largo/2;
	b=alto/2;
	c=ancho/2;
    
	glBegin (GL_LINE_LOOP); 
	glVertex3f (a, b, -c);
	glVertex3f (a,-b,-c);   //detras
	glVertex3f (-a, -b, -c);
	glVertex3f (-a, b, -c);
	glEnd();
	
	glBegin (GL_LINE_LOOP); 
	glVertex3f (a, b, c);
	glVertex3f (a, b, -c);
	glVertex3f (-a, b, -c);  //arriba
	glVertex3f (-a, b, c);
	glEnd();

	glBegin (GL_LINE_LOOP); 
	glVertex3f (a,b,c);
	glVertex3f (a,b,-c);  //derecha
	glVertex3f (a,-b,-c);
	glVertex3f (a,-b,c);
	glEnd();
	
	glBegin (GL_LINE_LOOP); 
	glVertex3f (a, b, c);
	glVertex3f (-a, b, c);
	glVertex3f (-a, -b, c);    //delante
	glVertex3f (a, -b, c);
	glEnd();
	
	glBegin (GL_LINE_LOOP); 
	glVertex3f (a,-b,c);
	glVertex3f (a,-b,-c);   //izquierda
	glVertex3f (-a,-b,-c);
	glVertex3f (-a,-b,c);
	glEnd();
	
	glBegin (GL_LINE_LOOP); 
	glVertex3f (a,-b,c);
	glVertex3f (a,-b,-c);   //abajo
	glVertex3f (-a,-b,-c);
	glVertex3f (-a,-b,c);
	glEnd();
	 
}

void igWireCube (void){

	igWireCaja(1,1,1);
}

void igSolidCube (void){
//volver del revés para las normales
float cubo[8][3]={{0.5,0.5,0.5},{0.5,0.5,-0.5},{0.5,-0.5,0.5},{0.5,-0.5,-0.5},
					{-0.5,0.5,0.5},{-0.5,0.5,-0.5},{-0.5,-0.5,0.5},{-0.5,-0.5,-0.5}};
	
	glBegin(GL_POLYGON);

		glNormal3f(cubo[0][0],0,1.5); //Normal
		glVertex3f(cubo[1][0],cubo[1][1],cubo[1][2]);
		glVertex3f(cubo[0][0],cubo[0][1],cubo[0][2]);		
		glVertex3f(cubo[2][0],cubo[2][1],cubo[2][2]);
		glVertex3f(cubo[3][0],cubo[3][1],cubo[3][2]);

	
	glEnd();

	glBegin(GL_POLYGON);
		
		glNormal3f(0,cubo[0][0],cubo[0][0]+0.5); //Normal
		glVertex3f(cubo[0][0],cubo[0][1],cubo[0][2]);
		glVertex3f(cubo[4][0],cubo[4][1],cubo[4][2]);
		glVertex3f(cubo[6][0],cubo[6][1],cubo[6][2]);
		glVertex3f(cubo[2][0],cubo[2][1],cubo[2][2]);
		
		
	glEnd();

	glBegin(GL_POLYGON);

		glNormal3f(cubo[0][0],cubo[0][0],cubo[0][0]); //Normal
		glVertex3f(cubo[4][0],cubo[4][1],cubo[4][2]);
		glVertex3f(cubo[5][0],cubo[5][1],cubo[5][2]);
		glVertex3f(cubo[7][0],cubo[7][1],cubo[7][2]);
		glVertex3f(cubo[6][0],cubo[6][1],cubo[6][2]);
		
		
	glEnd();

	glBegin(GL_POLYGON);

		glNormal3f(cubo[0][0],cubo[0][0],cubo[0][0]); //Normal
		glVertex3f(cubo[1][0],cubo[1][1],cubo[1][2]);
		glVertex3f(cubo[3][0],cubo[3][1],cubo[3][2]);
		glVertex3f(cubo[7][0],cubo[7][1],cubo[7][2]);
		glVertex3f(cubo[5][0],cubo[5][1],cubo[5][2]);
		
	glEnd();

	glBegin(GL_POLYGON);

		glNormal3f(cubo[0][0],cubo[0][0],cubo[1][0]); //Normal
		glVertex3f(cubo[0][0],cubo[0][1],cubo[0][2]);
		glVertex3f(cubo[1][0],cubo[1][1],cubo[1][2]);
		glVertex3f(cubo[5][0],cubo[5][1],cubo[5][2]);
		glVertex3f(cubo[4][0],cubo[4][1],cubo[4][2]);
		
	glEnd();

	glBegin(GL_POLYGON);

		glNormal3f(cubo[0][0],cubo[0][0],cubo[1][0]); //Normal
		glVertex3f(cubo[2][0],cubo[2][1],cubo[2][2]);
		glVertex3f(cubo[3][0],cubo[3][1],cubo[3][2]);
		glVertex3f(cubo[7][0],cubo[7][1],cubo[7][2]);
		glVertex3f(cubo[6][0],cubo[6][1],cubo[6][2]);
		
	glEnd();

}

/******************************************************************************************/
/* Crea una esfera a partir de las ecuaciones de la supercuadrica                         */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igWireSphere (int pu, int pv)
{
	igCreateQuadricObject (pu, pv, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
}


/******************************************************************************************/
/* Crea un rulo a partir de las ecuaciones de la supercuadrica                            */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igWireRulo (int pu, int pv)
{
	igCreateQuadricObject (pu, pv, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f);
}


/******************************************************************************************/
/* Crea un dado a partir de las ecuaciones de la supercuadrica                            */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igWireDado (int pu, int pv)
{
	igCreateQuadricObject (pu, pv, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f); 
}


/******************************************************************************************/
/* Crea una semiesfera a partir de las ecuaciones de la supercuadrica                     */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igWireSemiSphere (int pu, int pv)
{
	igCreateQuadricObject (pu, pv,  1.0f, 0.5f,1.0f, 1.0f, 1.0f);
}


/******************************************************************************************/
/* Crea un cono a partir de las ecuaciones de la supercuadrica                            */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igWireCone (int pu, int pv)
{
	igCreateQuadricObject (pu, pv, 1.0f, 0.5f, 1.0f, 2.0f, 1.0f);
}

/*******************************************************************************************/
/* Crea una piedra en alambrico															   */
/*******************************************************************************************/

void igWireStone (int pu, int pv)
{
	igCreateQuadricObject (pu, pv, 1.0f, 1.0f, 1.0f, 0.0f, 0.5f); 
}

/*******************************************************************************************/
/* Crea una esfera solida       														   */
/*******************************************************************************************/
void igSolidSphere (int pu, int pv, int numtext)
{
	igCreateSolidQuadricObject (pu, pv, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, numtext);
}


/*******************************************************************************************/
/* Crea un rulo solido          														   */
/*******************************************************************************************/
void igSolidRulo (int pu, int pv, int numtext)
{
	igCreateSolidQuadricObject (pu, pv, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, numtext);
}


/*******************************************************************************************/
/* Crea un dado solido           														   */
/*******************************************************************************************/
void igSolidDado (int pu, int pv, int numtext)
{
	igCreateSolidQuadricObject (pu, pv, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f, numtext); 
}


/*******************************************************************************************/
/* Crea una  semiesfera solida       						   			                   */
/*******************************************************************************************/

void igSolidSemiSphere (int pu, int pv, int numtext)
{
	igCreateSolidQuadricObject (pu, pv, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, numtext);
}


/*******************************************************************************************/
/* Crea un cono solido           														   */
/*******************************************************************************************/

void igSolidCone (int pu, int pv, int numtext)
{
	igCreateSolidQuadricObject (pu, pv, 1.0f, 0.5f, 1.0f, 2.0f, 1.0f, numtext);
}


/*******************************************************************************************/
/* Crea una piedra solida       														   */
/*******************************************************************************************/

void igSolidStone (int pu, int pv, int numtext)
{
	igCreateSolidQuadricObject (pu, pv, 1.0f, 1.0f, 1.0f, 0.09f, 0.5f, numtext); 
}

