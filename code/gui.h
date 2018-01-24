/****************************************************************************
GUI.H
The GUI class interface

 Author   :   Javier Palmer
 Date     :   2/1/2005

 Written for the FATMAN Game
*****************************************************************************/

#ifndef __GUI_H
#define __GUI_H

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN


#include <windows.h>
#include "font.h"
#include "texture.h"

class CGUI
{
private:
	int minutesLeft, secondsLeft, millisecondsLeft;
	int enemiesLeft;
	int orangesLeft;

	CFont *font;
	CFont *crosshair;
	CFont *endText;

public:
	CGUI();
	~CGUI();

	void SetCurrentTime(float timeLeft);
	void SetEnemiesLeft(int eLeft);
	void SetOrangesLeft(int oLeft);
	void Draw();
	void Animate(float deltaTime);

	void DrawWinner();
	void DrawLoser();
};


#endif