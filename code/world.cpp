#include "world.h"
#include <gl/glut.h>
#include <iostream>
/****************************************************************************
WORLD.CPP
 
 Author   :   Javier Palmer
 Date     :   2/3/2005

 Written for the FATMAN Game
*****************************************************************************/
CWorld::CWorld()
{
}

CWorld::~CWorld()
{
//	audioSystem->Shutdown();

	delete templos;
	delete arboles;
	delete terrain;
	delete audioSystem;
	delete worldSound;
}

CWorld::CWorld(CCamera *c)
{	
	camera = c;

	terrain = new CTerrain(8, 2.0f);
	player = new CPlayer;
	audioSystem = new CAudioSystem;
	gui = new CGUI;

	gameDone = false;		// game is just starting
	LoadRest = 0;	

	player->AttachTo(terrain);
	audioSystem->InitDirectXAudio(NULL);
	player->SetTerrain(terrain);
	player->SetAudioSystem(audioSystem);

	LoadWorld();
	//musica
	worldSound = audioSystem->Create("data\\music\\ambient.mid", false);
	audioSystem->Play(worldSound, DMUS_SEG_REPEAT_INFINITE);
	//Interface
	timeStart = 180.0;			// 300 seconds = 5 minutes
	timeElapsed = 0.0;
	numgoblins=5;
	numoranges=14;
	gui->SetCurrentTime(timeStart);
	gui->SetEnemiesLeft(numgoblins);
	gui->SetOrangesLeft(numoranges);
}

void CWorld::Animate(float deltaTime)
{
	camera->SetCameraPlayer(player);

	terrain->Animate(deltaTime);

    // keep the fatman in the terrain
	if (player->position.x <= terrain->GetScanDepth())
		player->position.x = terrain->GetScanDepth();
	if (player->position.x >= terrain->GetWidth()*terrain->GetMul() - terrain->GetScanDepth())
		player->position.x = terrain->GetWidth()*terrain->GetMul() - terrain->GetScanDepth();
	if (player->position.z <= terrain->GetScanDepth())
		player->position.z = terrain->GetScanDepth();
	if (player->position.z >= terrain->GetWidth()*terrain->GetMul() - terrain->GetScanDepth())
		player->position.z = terrain->GetWidth()*terrain->GetMul() - terrain->GetScanDepth();
	
	const type_info &goblin_type = typeid(CGoblinEnemy); 
	const type_info &orange_type = typeid(CFruta);

	numgoblins = CountObjectTypes(goblin_type);           // count goblins
	numoranges = CountObjectTypes(orange_type);            // count oranges

	gui->SetEnemiesLeft(numgoblins);
	gui->SetOrangesLeft(numoranges);
	gui->SetCurrentTime(timeStart - timeElapsed);

	if (!gameDone)
		timeElapsed += deltaTime;
	else
		timeElapsed = timeStart;

}

void CWorld::Draw(CCamera *camera)
{
	if(!gameDone){

	gui->Draw();
	terrain->Draw(camera);
//lamparas
//puertas
glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glTranslatef(74, obj->position.y-4.0, 100);
		glRotatef(-(obj->direction), 0.0, 1.0, 0.0);
		glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
		glScalef(0.25, 0.25, 0.25);
	    obj->AnimateModel(0, 0, (obj->deltaT)*(obj->animSpeed));
glPopMatrix();
glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glTranslatef(100, obj->position.y-4.0,74);
		glRotatef(-(obj->direction), 0.0, 1.0, 0.0);
		glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
		glScalef(0.25, 0.25, 0.25);
	    obj->AnimateModel(0, 0, (obj->deltaT)*(obj->animSpeed));
glPopMatrix();
//esparcidas
glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glTranslatef(290, obj->position.y-4.0, 90);
		glRotatef(-(obj->direction), 0.0, 1.0, 0.0);
		glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
		glScalef(0.25, 0.25, 0.25);
	    obj->AnimateModel(0, 0, (obj->deltaT)*(obj->animSpeed));
glPopMatrix();
glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glTranslatef(90, obj->position.y-4.0, 290);
		glRotatef(-(obj->direction), 0.0, 1.0, 0.0);
		glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
		glScalef(0.25, 0.25, 0.25);
	    obj->AnimateModel(0, 0, (obj->deltaT)*(obj->animSpeed));
glPopMatrix();
//ultimo
glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glTranslatef(290, obj->position.y-4.0, 290);
		glRotatef(-(obj->direction), 0.0, 1.0, 0.0);
		glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
		glScalef(0.25, 0.25, 0.25);
	    obj->AnimateModel(0, 0, (obj->deltaT)*(obj->animSpeed));
glPopMatrix();


	}
	if (gameDone)
	{
		FadeScreen();
		if ((player->aiState != AI_DEAD) && ((numgoblins <= 0) && (numoranges <= 0))){
			gui->DrawWinner();
		}
		else{
			audioSystem->Stop(worldSound);
			gui->DrawLoser();
		}
	}
}

void CWorld::OnPrepare()
{
	//Clear
	glClearColor(terrain->fogColor[0], terrain->fogColor[1], terrain->fogColor[2], terrain->fogColor[3]);
	
	//Where I am?
	if(!gameDone)
	{
	    terrain->Prepare();
		if( (LoadRest < 2) && (numoranges == 1)) // Refresh oranges
		{
			if (LoadRest == 1)
			{
				LoadRestOranges_2();
				LoadRest = 2;
			}
			if (LoadRest == 0)
			{
				LoadRestOranges_1();
			    LoadRest = 1;
			}
		}
	}

	if ((numgoblins <= 0 && numoranges <= 0) || (timeElapsed >= timeStart) || (player->aiState == AI_DEAD))
		gameDone = true;
}

void CWorld::LoadWorld() 
{
	int enemyIdx = 0;
	// generate muros
		objeto = new CObj;
		objeto->AttachTo(terrain);	
	//generate enemigos wolf
	for (enemyIdx = 2; enemyIdx < 5; enemyIdx++)
	{	    
		wolf = new CWolfEnemy(80*enemyIdx,80*enemyIdx);
		wolf->AttachTo(terrain);
		wolf->SetAudioSystem(audioSystem);
		wolf->SetPlayer(player);
		wolf->SetTerrain(terrain);
	}		
	//generate enemigos goblin
	for (enemyIdx = 2; enemyIdx < 7; enemyIdx++)
	{	  
		goblin = new CGoblinEnemy(50*enemyIdx,50*enemyIdx);
		goblin->AttachTo(terrain);
		goblin->SetPlayer(player);
		goblin->SetTerrain(terrain);
	}

// lamparas
		obj = new CEntity;
		obj->AttachTo(terrain);
		obj->Load("data\\world\\biglamp.md2", "data\\world\\biglamp.pcx");
// Templos
		templos = new CArb2;
		templos->AttachTo(terrain);
		templos->position.x = 290;
		templos->position.y = -1.0f;
		templos->position.z = 160;
        templos->SetPlayer(player);

		templos = new CArb2;
		templos->AttachTo(terrain);
		templos->position.x = 230;
		templos->position.y = -1.0f;
		templos->position.z = 300;
        templos->SetPlayer(player);

		templos = new CArb2;
		templos->AttachTo(terrain);
		templos->position.x = 100;
		templos->position.y = -1.0f;
		templos->position.z = 267;
        templos->SetPlayer(player);

// troncos arbol
       	arboles = new CArb1;
		arboles->AttachTo(terrain);
		arboles->position.x = 169;
		arboles->position.y = -1.0f;
		arboles->position.z = 120;
        arboles->SetPlayer(player);

       	arboles = new CArb1;
		arboles->AttachTo(terrain);
		arboles->position.x = 220;
		arboles->position.y = -1.0f;
		arboles->position.z = 250;
        arboles->SetPlayer(player);

       	arboles = new CArb1;
		arboles->AttachTo(terrain);
		arboles->position.x = 300;
		arboles->position.y = -1.0f;
		arboles->position.z = 100;
        arboles->SetPlayer(player);

// generate oranges		
		orange = new CFruta(180,160);
		orange->AttachTo(terrain);
		orange->SetPlayer(player);

		orange = new CFruta(120,130);
		orange->AttachTo(terrain);
		orange->SetPlayer(player);

		orange = new CFruta(120,200);
		orange->AttachTo(terrain);
		orange->SetPlayer(player);

		orange = new CFruta(212,259);
		orange->AttachTo(terrain);
		orange->SetPlayer(player);

		orange = new CFruta(200,300);
		orange->AttachTo(terrain);
		orange->SetPlayer(player);
}

void CWorld::FadeScreen()
{
  CTexture * over;
  over = new CTexture;
  over->LoadTexture("data\\texture\\ove.tga");	


	glGenTextures(1, &over->texID);
	glBindTexture(GL_TEXTURE_2D, over->texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, over->width, over->height,
					GL_RGB, GL_UNSIGNED_BYTE, over->data);

  	glEnable(GL_TEXTURE_2D);

glPushMatrix();
glLoadIdentity();
	glEnable(GL_POINT_SMOOTH);
    glShadeModel(GL_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D,over->texID);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); 
	glVertex3f(-5, -5, -7.0);
	glTexCoord2f(1.0f, 0.0f); 
	glVertex3f(5, -5, -7.0);
	glTexCoord2f(1.0f, 1.0f); 
	glVertex3f(5, 5, -7.0);
	glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(-5, 5, -7.0);
	glEnd();
	
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_POINT_SMOOTH);
glPopMatrix();
}


void CWorld::SetScreen(int width, int height)
{
	screenWidth = width;
	screenHeight = height;
}


void CWorld::LoadRestOranges_1(void)
{

		orange = new CFruta(279,312);
		orange->AttachTo(terrain);
		orange->SetPlayer(player);

		orange = new CFruta(300,112);
		orange->AttachTo(terrain);
		orange->SetPlayer(player);

		orange = new CFruta(300,300);
		orange->AttachTo(terrain);
		orange->SetPlayer(player);

		orange = new CFruta(290,217);
		orange->AttachTo(terrain);
		orange->SetPlayer(player);

		orange = new CFruta(193,230);
		orange->AttachTo(terrain);
		orange->SetPlayer(player);
}


void CWorld::LoadRestOranges_2(void)
{

		orange = new CFruta(143,120);
		orange->AttachTo(terrain);
		orange->SetPlayer(player);

		orange = new CFruta(180,120);
		orange->AttachTo(terrain);
		orange->SetPlayer(player);

		orange = new CFruta(270,300);
		orange->AttachTo(terrain);
		orange->SetPlayer(player);

		orange = new CFruta(300,190);
		orange->AttachTo(terrain);
		orange->SetPlayer(player);
}

int CWorld::CountObjectTypes(const type_info &classID)
{
	int count = 0;
	CObject *c1;
	CObject *c2;

	c1 = (CObject*)terrain->childNode;

	while (c1 != NULL)
	{
		c2 = c1;
		do
		{
			if (typeid(*c2) == classID)
				count++;
			c2 = (CObject*)c2->nextNode;
		} while (!c2->IsFirstChild());

		count--;

		c1 = (CObject*)c1->childNode;
	}

	return count;
}