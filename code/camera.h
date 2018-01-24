#ifndef __CAMERA_H
#define __CAMERA_H

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
/****************************************************************************
CAMERA.H
The interface for CCamera - the camera system: The CCamera class is the camera system
 
 Author   :   Javier Palmer
 Date     :   2/3/2005

 Written for the FATMAN Game
*****************************************************************************/
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "vector.h"
#include "object.h"

class CObject;
class CEntity;

class CCamera
{
private:
	// these are used for moving and changing camera orientation
	// through the MoveTo/LookTo methods
	CVector initPosition, finalPosition;
	CVector initLookAt, finalLookAt;

	CVector lookAtVel;			// velocity for looking at objects
	CVector lookAtAccel;		// acceleration for looking at objects

	void UpdateLookAt();
	void UpdateMoveTo();

public:
	CVector position;			// position of camera
	CVector velocity;			// velocity of camera
	CVector acceleration;		// acceleration of camera
	CVector lookAt;			// lookat vector
	CVector PositionPlayer;  // posicion que ocupa el jugador en este momento;

	// up, forward, right vectors
	CVector up;
	CVector forward;
	CVector right;

	// yaw and pitch angles
	float yaw;
	float pitch;

	int screenWidth, screenHeight;
	int centerX, centerY;

	CCamera();
	CCamera(int width, int height) {}
	CCamera(CVector *look);
	CCamera(CVector *pos, CVector *look);
	~CCamera();

//*****************
	void SetCameraPlayer(CEntity *player);
	void LookAtPlayer();
//*****************
	void LookAt(CObject *object);
	void LookAtNow(CObject *object);
	void MoveTo(CObject *object);
	void MoveToNow(CObject *object);
	void MoveToNow(scalar_t x, scalar_t y, scalar_t z);

	// right rotation along y-axis (yaw)
	void RotateYaw(scalar_t radians);
	void RotatePitch(scalar_t radians);
	void RotateRoll(scalar_t radians);

	// do physics calculations
	void Animate(scalar_t deltaTime);
};

#endif