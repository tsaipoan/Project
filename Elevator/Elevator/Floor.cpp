/**
* \file Floor.cpp
*
* \author Po-An Tsai
*/

#include "stdafx.h"
#include "Floor.h"
#include "Controller.h"

/** \brief Constructor */
CFloor::CFloor()
{
}

/** \brief Destructor */
CFloor::~CFloor()
{
}

/** \brief Set the value of Up for a floor.
* \param s The new value for mUp
*/
void CFloor::SetUp(bool s)
{
	mUp = s;
	mController->SetCallLight(mFloor, CElevatorController::Up, mUp);
}

/** \brief Set the value of Down for a floor.
* \param d The new value for mDown
*/
void CFloor::SetDown(bool d)
{
	mDown = d;
	mController->SetCallLight(mFloor, CElevatorController::Down, mDown);
}

/** \brief Set the value of Panel for a floor.
* \param p The new value for mPanel
*/
void CFloor::SetPanel(bool p)
{
	mPanel = p;
	mController->SetPanelFloorLight(mFloor, mPanel);
}