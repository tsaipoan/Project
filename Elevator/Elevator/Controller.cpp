/**
* \file Controller.cpp
*
* \author Po-An Tsai
*/

#include "stdafx.h"
#include "Controller.h"


/// The time the door remains open
const double DoorOpenTime = 2.0;

/** \brief Constructor */
CController::CController()
{
	for (int f = 1; f <= NumFloors; f++)
	{
		mFloors[f - 1].SetController(this);
		mFloors[f - 1].SetFloor(f);
	}
}

/** \brief Destructor */
CController::~CController()
{
}

/** \brief This function is called when the open button is pressed.
*/
void CController::OnOpenPressed()
{
	switch (mState)
	{
	case Idle:
		// Transition to the DoorOpening state
		SetState(DoorOpening);
		break;

	case DoorOpen:
		SetState(DoorOpen);
		break;

	case DoorClosing:
		SetState(DoorOpening);
		break;

	default:
		break;
	}
}

/** \brief Set a state
* \param state The new state to set
*/
void CController::SetState(States state)
{
	mState = state;
	mStateTime = 0;

	// Entry activities for states
	switch (mState)
	{
	case Idle:
		SetDoorMotor(mFloor, 0);
		break;

	case DoorOpening:
		SetDoorMotor(mFloor, 1);

		WhatFloorToGoTo();
		mFloors[mFloor - 1].SetPanel(false);
		if (mGoingUp)
		{
			mFloors[mFloor - 1].SetUp(false);
		}
		else
		{
			mFloors[mFloor - 1].SetDown(false);
		}
		break;

	case DoorOpen:
		SetDoorMotor(mFloor, 0);
		break;

	case DoorClosing:
		SetDoorMotor(mFloor, -1);
		break;

	case Moving:
		SetBrake(false);
		SetMotorSpeed(mGoingUp ? 1 : -1);
		break;

	case Stop:
		SetMotorSpeed(0);
		SetBrake(true);
		break;

	case FireDoorClose:
		SetMotorSpeed(0);
		SetBrake(true);
		SetDoorMotor(mFloor, -1);
		CancelAllLight();
		break;

	case FireMoving:
		SetDoorMotor(mFloor, 0);
		SetBrake(false);
		SetMotorSpeed(-1);
		CancelAllLight();
		break;

	case FireStop:
		SetMotorSpeed(0);
		SetBrake(true);
		break;

	case FireDoorOpening:
		SetDoorMotor(mFloor, 1);
		break;

	case FireDoorOpen:
		SetDoorMotor(mFloor, 0);
		break;

	default:
		break;
	}
}

/** \brief Elevator service function
*
* This function is called once every 0.001 seconds and
* allows us to control elevator functionality.
*/
void CController::Service()
{
	// Increment state time by 1 millisecond
	mStateTime += 0.001;

	switch (mState)
	{
	case Idle:
	{
		if (IsFireMode())
		{
			SetState(FireDoorClose);
			break;
		}
		int floor = WhatFloorToGoTo();
		if (floor == mFloor)
		{
			// Button pressed on this floor. Open the door
			SetState(DoorOpening);
		}
		else if (floor != 0)
		{
			SetState(Moving);
		}
	}
		break;

	case DoorOpening:
		if (IsDoorOpen(mFloor))
		{
			SetState(DoorOpen);
		}
		break;

	case DoorClosing:
		if (IsDoorClosed(mFloor))
		{
			SetState(Idle);
		}
		break;

	case DoorOpen:
	{
		if (IsFireMode())
		{
			SetState(FireDoorClose);
		}
		else if (mStateTime >= DoorOpenTime)
		{
			SetState(DoorClosing);
		}
	}
		break;

	case Moving:
	{
		if (IsFireMode())
		{
			SetState(FireMoving);
			break;
		}
		int floor = WhatFloorToGoTo();
		assert(floor != 0);

		// What's the position for that floor?
		double floorPosition = (floor - 1) * FloorSpacing;

		if (fabs(GetPosition() - floorPosition) < FloorTolerance)
		{
			mFloor = floor;
			SetState(Stop);
		}
	}
		break;

	case Stop:
		if (IsFireMode())
		{
			SetState(FireDoorClose);
		}
		else if (mStateTime >= 1)
		{
			SetState(DoorOpening);
		}
		break;

	case FireDoorClose:
	{
		if (mFloor == 1)
		{
			SetState(FireDoorOpening);
		}
		else if (IsDoorClosed(mFloor))
		{
			SetState(FireMoving);
		}
	}
		break;

	case FireMoving:
	{
		int floor = 1;

		// What's the position for that floor?
		double floorPosition = (floor - 1) * FloorSpacing;
		if (fabs(GetPosition() - floorPosition) < FloorTolerance)
		{
			mFloor = floor;
			SetState(FireStop);
		}
	}
		break;

	case FireStop:
		if (mStateTime >= 1)
		{
			SetState(FireDoorOpening);
		}
		break;

	case FireDoorOpening:
		if (IsDoorOpen(mFloor))
		{
			SetState(FireDoorOpen);
		}
		break;

	case FireDoorOpen:
		if (!IsFireMode())
		{
			SetState(DoorOpen);
		}
		break;

	default:
		break;
	}
}

/** \brief This function is called when the door close button is pressed.
*/
void CController::OnClosePressed()
{
	switch (mState)

	{
	case DoorOpen:
		SetState(DoorClosing);
		break;

	case DoorOpening:
		SetState(DoorClosing);
		break;

	default:
		break;
	}
}


/** \brief Initialization function.
*
* This function is called when the elevator system is initialized. This is
* later than when it is constructed, since the controller is not installed on
* an elevator when it is constructed. This function is called when the elevator
* controller is installed and ready to control an elevator.
*/
void CController::Initialize()
{

}

/** \brief This function is called when the panel button is pressed
* on a floor.
* \param floor The floor we are called to 1-3
*/
void CController::OnPanelFloorPressed(int floor)
{
	if (!IsFireMode())
	{
		mFloors[floor - 1].SetPanel(true);
	}
	
}

/** \brief This function is called when the up button is pressed
* on a floor.
* \param floor The floor we are called to 1-3
*/
void CController::OnCallUpPressed(int floor)
{
	if (!IsFireMode())
	{
		mFloors[floor - 1].SetUp(true);
	}
}

/** \brief This function is called when the down button is pressed
* on a floor.
* \param floor The floor we are called to 1-3
*/
void CController::OnCallDownPressed(int floor)
{
	if (!IsFireMode())
	{
		mFloors[floor - 1].SetDown(true);
	}
}

/**
* \brief Determine floor to go to in the up direction.
*
* Assuming we are going up, determine any floor we would
* go to in the up direction.
* \returns Floor 1 to 3 or 0 if no floor is selected.
*/
int CController::WhatFloorUp()
{
	// What floor are we currently on?
	// We stop with FloorTolerance of a floor. Suppose I am at position
	// 3.42. That's just above 3.42 - 3.28 = 0.14 above floor 2, but it's within
	// the tolerance, so we think of it as on floor 2.
	int floor = int((GetPosition() + FloorTolerance) / FloorSpacing) + 1;

	// Is there a floor to goto in the up direction that has the panel
	// or the up button pressed?
	for (int f = floor; f <= NumFloors; f++)
	{
		if (mFloors[f - 1].IsUp() || mFloors[f - 1].IsPanel())
			return f;
	}

	// Is there a floor to go to in the up direction that has the down
	// button pressed. We don't look at the current floor, though.
	for (int f = NumFloors; f>floor; f--)
	{
		if (mFloors[f - 1].IsDown())
			return f;
	}

	// If nothing, return 0;
	return 0;
}


/**
* \brief Determine floor to go to in the down direction.
*
* Assuming we are going down, determine any floor we would
* go to in the down direction.
* \returns Floor 1 to 3 or 0 if no floor is selected.
*/
int CController::WhatFloorDown()
{
	// What floor are we currently on?
	// We stop with FloorTolerance of a floor. Suppose I am at position
	// 3.42. That's just above 3.42 - 3.28 = 0.14 above floor 2, but it's within
	// the tolerance, so we think of it as on floor 2.
	int floor = int((GetPosition() + FloorTolerance) / FloorSpacing) + 1;

	// Is there a floor to goto in the up direction that has the panel
	// or the up button pressed?
	for (int f = floor; f >= 1; f--)
	{
		if (mFloors[f - 1].IsDown() || mFloors[f - 1].IsPanel())
			return f;
	}

	// Is there a floor to go to in the up direction that has the down
	// button pressed. We don't look at the current floor, though.
	for (int f = 1; f < floor; f++)
	{
		if (mFloors[f - 1].IsUp())
			return f;
	}

	// If nothing, return 0;
	return 0;
}

/**
* \brief Determine the floor to go to.
*
* Given the current direction we are going, determine what floor
* we should go to.
* \returns A floor to go to (1 to 3) or 0 if none
*/
int CController::WhatFloorToGoTo()
{
	if (mGoingUp)
	{
		// We are going up, so try for a floor in that direction
		int floor = WhatFloorUp();
		if (floor != 0)
			return floor;

		// Guess we can't go up, so see if we need to go down
		floor = WhatFloorDown();
		if (floor != 0)
		{
			// Reverse the direction
			mGoingUp = false;
			return floor;
		}
	}
	else
	{
		int floor = WhatFloorDown();
		if (floor != 0)
		{
			return floor;
		}

		// We are going up, so try for a floor in that direction
		floor = WhatFloorUp();
		if (floor != 0)
		{
			// Reverse the direction
			mGoingUp = true;
			return floor;
		}
	}

	return 0;
}

/** \brief cancel all the light are pressed function. */
void CController::CancelAllLight()
{
	for (int f = 1; f <= NumFloors; f++)
	{
		mFloors[f - 1].SetPanel(false);
		mFloors[f - 1].SetUp(false);
		mFloors[f - 1].SetDown(false);
	}
}