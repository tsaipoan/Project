/**
* \file Controller.h
* \brief controller class.
*
* This class is the controller class.
* That class do the elevator control.
*
*  \author Po-An Tsai
*/

#pragma once
#include "ElevatorController.h"
#include "Floor.h"

/** \brief controller class.
* this class are derived from CElevatorController.
*/
class CController :
	public CElevatorController
{
public:
	CController();
	virtual ~CController();

	virtual void OnOpenPressed() override;

	virtual void Service() override;

	virtual void OnClosePressed() override;

	/// The state machine states
	enum States { Idle, DoorOpening, DoorOpen, DoorClosing, Moving, Stop, FireDoorClose, FireMoving, FireStop, FireDoorOpening, FireDoorOpen };

	void Initialize();

	virtual void OnPanelFloorPressed(int floor) override;

	virtual void OnCallUpPressed(int floor) override;

	virtual void OnCallDownPressed(int floor) override;

	void CancelAllLight();

private:
	void SetState(States state);

	int WhatFloorToGoTo();

	int WhatFloorUp();

	int WhatFloorDown();

	int mFloor = 1;      ///< The current floor

	States mState = Idle;   ///< The current state

	double mStateTime = 0;  ///< The time in a current state

	/// An object for each floor
	CFloor mFloors[NumFloors];

	bool mGoingUp = true;   ///< The current direction
};

