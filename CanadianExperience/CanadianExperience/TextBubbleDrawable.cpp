/**
* \file TextBubbleDrawable.cpp
*
* \author Po-An Tsai
*/

#include "stdafx.h"
#include "TextBubbleDrawable.h"
#include "TextBubbleDlg.h"
#include "Timeline.h"
#include "Actor.h"

using namespace std;
using namespace Gdiplus;

/** \brief Constructor
* \param name The drawable name
*/
CTextBubbleDrawable::CTextBubbleDrawable(const std::wstring &name) :
CDrawable(name)
{
}


CTextBubbleDrawable::~CTextBubbleDrawable()
{
}

/**
* \brief Draw the text drawable
* \param graphics Graphics context to draw on
*/
void CTextBubbleDrawable::Draw(Gdiplus::Graphics *graphics)
{
	mBubble.SetBubblePosition(mPlacedPosition.X, mPlacedPosition.Y);
	mBubble.DrawMe(graphics);
}

/**
* \brief Test to see if we clicked on the text bubble.
* \param pos Position to test
* \returns True if clicked on
*/
bool CTextBubbleDrawable::HitTest(Gdiplus::Point pos)
{
	return mBubble.IsPointInside(pos.X, pos.Y);
}

/**
* \brief Show the dialog box to change the text.
*/
void CTextBubbleDrawable::ShowDialogBox()
{
	// Create the dialog box object
	CTextBubbleDlg dlg;

	// Tell it about the text bubble
	dlg.SetTextBubble(&mBubble);
	if (dlg.DoModal() == IDOK)
	{
		// Take the changes to the text bubble
		dlg.Take();
	}
}

/**
* \brief Set the actor. This is where we set the channel name
* \param actor Actor to set
*/
void CTextBubbleDrawable::SetActor(CActor *actor)
{

	// Set the channel name
	mPositionChannel.SetName(actor->GetName() + L":" + GetName() + L":position");

	mTextChannel.SetName(actor->GetName() + L":" + GetName() + L":text");

}


/**
* \brief Set the timeline. The tells the channel the timeline
* \param timeline Timeline to set
*/
void CTextBubbleDrawable::SetTimeline(CTimeline *timeline)
{

	timeline->AddChannel(&mPositionChannel);

	timeline->AddChannel(&mTextChannel);
}


/** \brief Set the keyframe based on the current status.
*/
void CTextBubbleDrawable::SetKeyframe()
{

	mPositionChannel.SetKeyframe(GetPosition());
	wstring mirror;

	if (mBubble.GetMirror())
	{
		mirror = L"mirrored";
	}
	else
	{
		mirror = L"not mirrored";
	}

	mTextChannel.SetKeyframe(mBubble.GetText(), mirror);
}

/** \brief Get the current channel from the animation system.
*/
void CTextBubbleDrawable::GetKeyframe()
{

	if (mPositionChannel.IsValid())
		SetPosition(mPositionChannel.GetPoint());

	if (mTextChannel.IsValid())
	{
		bool mirror = false;
		mBubble.SetText(mTextChannel.GetText());
		if (mTextChannel.GetMirror() == L"mirrored")
		{
			mirror = true;
		}
		mBubble.SetMirrored(mirror);
	}
		
}