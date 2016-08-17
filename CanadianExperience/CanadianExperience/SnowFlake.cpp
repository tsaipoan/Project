/**
* \file SnowFlake.cpp
*
* \author Po-An Tsai
*/

#include "stdafx.h"
#include "SnowFlake.h"

using namespace Gdiplus;

/** \brief Constructor for a snow flake
* \param position The position of the snow
* \param deltaX The velocity x for a snow to use
* \param deltaY The velocity y for a snow to use
*/
CSnowFlake::CSnowFlake(Gdiplus::PointF position, double deltaX, double deltaY)
{
	mPosition = position;

	mDeltaX = deltaX;

	mDeltaY = deltaY;
}

/**
* \brief Destructor
*/
CSnowFlake::~CSnowFlake()
{
}

/** \brief Draw this snow on a device context
* \param graphics The device context to draw on
* \param brush The brush to use
*/
void CSnowFlake::Draw(Graphics *graphics, SolidBrush *brush)
{
	graphics->FillEllipse(brush, (int)mPosition.X, (int)mPosition.Y, 3, 3);
}

/** \brief Update this snow on it's position
* \param time The time elapsed
*/
void CSnowFlake::Update(double time)
{
	float x = mDeltaX * time;
	float y = mDeltaY * time;

	mPosition = mPosition + PointF(x, y);
}

