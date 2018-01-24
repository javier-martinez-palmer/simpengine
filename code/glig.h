/*************************************************************************/
/*                                                                       */
/*                 glig.h LIBRERIA DE MODELADO GEOMETRICO	             */
/*                                                                       */
/*   Rev. 2.0  01/01/2002   AUTORES: O. Belmonte, M. Chover, J. Ribelles */
/*                                                                       */
/*************************************************************************/

#define E 0.0001
#define F 0.0001

/* Devuelve la coordenada de un punto en R3 a partir de un punto (u,v) */
/*   de un espacio parametrico en R2 */
float xSuperQuadric(float u, float v, float R, float s1, float s2);

/* Devuelve la coordenada de un punto en R3 a partir de un punto (u,v) */
/*   de un espacio parametrico en R2 */
float ySuperQuadric(float u, float v, float R, float s1, float s2);

/* Devuelve la coordenada de un punto en R3 a partir de un punto (u,v) */
/*   de un espacio parametrico en R2 */
float zSuperQuadric(float u, float v, float R, float s1, float s2);

/* Crea una cuadrica segun los parametros que se le pasan */
void igCreateQuadricObject (int pu, int pv, float uMax, float vMax, float R, float s1, float s2);

/* Crea una cuadrica segun los parametros que se le pasan */
void igCreateSolidQuadricObject (int pu, int pv, float uMax, float vMax, float R, float s1, float s2, int numtext);

/* Crea una esfera a partir de las ecuaciones de la supercuadrica */
void igWireSphere (int pu, int pv);

/* Crea un rulo a partir de las ecuaciones de la supercuadrica */
void igWireRulo (int pu, int pv);

/* Crea un dado a partir de las ecuaciones de la supercuadrica */
void igWireDado (int pu, int pv);

/* Crea una semiesfera a partir de las ecuaciones de la supercuadrica */
void igWireSemiSphere (int pu, int pv);

/* Crea un cono a partir de las ecuaciones de la supercuadrica */
void igWireCone (int pu, int pv);

/* Crea una piedra a partir de las ecuaciones de la supercuadrica*/
void igWireStone (int pu, int pv);

/*LAS SOLIDAS*/

/* Crea una esfera a partir de las ecuaciones de la supercuadrica */
void igSolidSphere (int pu, int pv, int numtext);

/* Crea un rulo a partir de las ecuaciones de la supercuadrica */
void igSolidRulo (int pu, int pv, int numtext);

/* Crea un dado a partir de las ecuaciones de la supercuadrica */
void igSolidDado (int pu, int pv, int numtext);

/* Crea una semiesfera a partir de las ecuaciones de la supercuadrica */
void igSolidSemiSphere (int pu, int pv, int numtext);

/* Crea un cono a partir de las ecuaciones de la supercuadrica */
void igSolidCone (int pu, int pv, int numtext);

/* Crea una piedra a partir de las ecuaciones de la supercuadrica*/
void igSolidStone (int pu, int pv, int numtext);

/*ILUMINACIÓN*/

float dxuSuperQuadric(float u, float v, float R, float s1, float s2);
float dyuSuperQuadric(float u, float v, float R, float s1, float s2);
float dzuSuperQuadric(float u, float v, float R, float s1, float s2);
float dxvSuperQuadric(float u, float v, float R, float s1, float s2);
float dyvSuperQuadric(float u, float v, float R, float s1, float s2);
float dzvSuperQuadric(float u, float v, float R, float s1, float s2);
float nxSuperQuadric(float u, float v, float R, float s1, float s2);
float nySuperQuadric(float u, float v, float R, float s1, float s2);
float nzSuperQuadric(float u, float v, float R, float s1, float s2);