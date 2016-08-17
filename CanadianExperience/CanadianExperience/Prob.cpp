/**
* \file Prob.cpp
*
* \author Po-An Tsai
*/

#include "stdafx.h"
#include "Prob.h"
#include "Actor.h"
#include "Timeline.h"

#include <sstream>
#include <iomanip>

using namespace Gdiplus;
using namespace std;


/** \brief Constructor for a prob object
* \param name The drawable name to use
* \param filename The filename for the image to use
*/
CProb::CProb(const std::wstring &name, const std::wstring &filename) : CImageDrawable(name, filename)
{
}


/**
* \brief Destructor
*/
CProb::~CProb()
{
}


/**
* \brief Set the actor. This is where we set the channel name
* \param actor Actor to set
*/
void CProb::SetActor(CActor *actor)
{
	CImageDrawable::SetActor(actor);

	// Set the channel name
	mPositionChannel.SetName(actor->GetName() + L":" + GetName() + L":position");

}


/**
* \brief Set the timeline. The tells the channel the timeline
* \param timeline Timeline to set
*/
void CProb::SetTimeline(CTimeline *timeline)
{
	CImageDrawable::SetTimeline(timeline);

	timeline->AddChannel(&mPositionChannel);
}


/** \brief Set the keyframe based on the current status.
*/
void CProb::SetKeyframe()
{
	CImageDrawable::SetKeyframe();

	mPositionChannel.SetKeyframe(GetPosition());
}

/** \brief Get the current channel from the animation system.
*/
void CProb::GetKeyframe()
{
	CImageDrawable::GetKeyframe();

	if (mPositionChannel.IsValid())
		SetPosition(mPositionChannel.GetPoint());
}



/**
* \brief Draw the prob
* \param graphics Graphics context to draw on
*/
void CProb::Draw(Gdiplus::Graphics *graphics)
{
	CImageDrawable::Draw(graphics);
}
