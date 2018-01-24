#include "gui.h"
#include <math.h>
#include <stdio.h>
/****************************************************************************
GUI.CPP
*****************************************************************************/
CGUI::CGUI()
{
	minutesLeft = secondsLeft = enemiesLeft = orangesLeft = 0;
	font = new CFont("Arial", 16);
	endText = new CFont("Arial", 40);
}

CGUI::~CGUI()
{
	font->ClearFont();
	crosshair->ClearFont();
	endText->ClearFont();
	delete font;
	delete endText;
}

void CGUI::SetCurrentTime(float timeLeft)
{
	// timeLeft is in seconds

	minutesLeft = (int)(timeLeft / 60.0);	// 60 seconds in 1 minute
	secondsLeft = (int)floor(timeLeft) % 60;
	millisecondsLeft = (int)(timeLeft - (float)floor(timeLeft)) * 60;
}

void CGUI::SetEnemiesLeft(int eLeft)
{
	enemiesLeft = eLeft;
}

void CGUI::SetOrangesLeft(int oLeft)
{
	orangesLeft = oLeft;
}

void CGUI::DrawWinner()
{
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	endText->SetPos3D(-0.25f, 0.3f, -0.1f);
	endText->SetRGBA(0.3f, 1.0f, 0.3f, 0.8f);
	endText->Print(" You win!");

	endText->SetPos3D(-0.5f, -0.3f, -0.1f);
	endText->SetRGBA(0.8f, 0.8f, 0.8f, 0.8f);
	endText->Print("Press the ESC key to exit");

	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
}

void CGUI::DrawLoser()
{
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	endText->SetPos3D(-0.25f, 0.3f, -0.1f);
	endText->SetRGBA(1.0f, 0.3f, 0.3f, 0.8f);
	endText->Print(" You lose!");

	endText->SetPos3D(-0.5f, -0.3f, -0.1f);
	endText->SetRGBA(0.8f, 0.8f, 0.8f, 0.8f);
	endText->Print("Press the ESC key to exit");
	
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
}

void CGUI::Draw()
{
	char *cadena;
	cadena = new char[256];
	glDisable(GL_TEXTURE_2D);
	font->SetPos3D(2.5f, 2.9f, -5.0f);
	font->SetRGB(0.2f, 0.0f, 1.0f);
	
	if (secondsLeft < 10)
	{
		if (millisecondsLeft < 10)
		{
			sprintf(cadena,"Time: %d:0%d.0%d",minutesLeft,secondsLeft,millisecondsLeft);
			font->Print(cadena);
		}
		else
		{
			sprintf(cadena,"Time: %d:0%d.%d",minutesLeft,secondsLeft,millisecondsLeft);
			font->Print(cadena);
		}
	}
	else
	{
		if (millisecondsLeft < 10)
		{
			sprintf(cadena,"Time: %d:%d.0%d",minutesLeft,secondsLeft,millisecondsLeft);
			font->Print(cadena);
		}
		else
		{
			sprintf(cadena,"Time: %d:%d.%d",minutesLeft,secondsLeft,millisecondsLeft);
			font->Print(cadena);
		}
	}

	font->SetPos3D(2.5f, 2.7f, -5.0f);
	sprintf(cadena,"Goblins:   %d", enemiesLeft+1);
	font->Print(cadena);

	font->SetPos3D(2.5f, 2.5f, -5.0f);
	sprintf(cadena,"Oranges: %d", orangesLeft+1);
	font->Print(cadena);


	glEnable(GL_TEXTURE_2D);
}