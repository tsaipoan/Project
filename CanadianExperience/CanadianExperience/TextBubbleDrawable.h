/**
* \file TextBubbleDrawable.h
*
* \author Po-An Tsai
*
* \brief A drawable based on drawing a text bubble.
*/

#pragma once
#include "Drawable.h"
#include "TextBubble.h"
#include "AnimChannelPoint.h"
#include "AnimChannelText.h"

/**
* \brief A drawable based on drawing a text bubble.
*/
class CTextBubbleDrawable :
	public CDrawable
{
public:
	CTextBubbleDrawable(const std::wstring &name);
	virtual ~CTextBubbleDrawable();

	/** \brief Default constructor disabled */
	CTextBubbleDrawable() = delete;
	/** \brief Copy constructor disabled */
	CTextBubbleDrawable(const CTextBubbleDrawable &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CTextBubbleDrawable &) = delete;

	virtual void Draw(Gdiplus::Graphics *graphics) override;
	virtual bool HitTest(Gdiplus::Point pos) override;

	/// \brief Is this drawable moveable?
	/// \returns true
	virtual bool IsMovable() { return true; }
	
	void ShowDialogBox();

	virtual void SetActor(CActor *actor) override;
	virtual void SetTimeline(CTimeline *timeline) override;
	virtual void SetKeyframe() override;
	virtual void GetKeyframe() override;
	
private:
	/// Text Bubble for the CTextBubble class
	CTextBubble mBubble;

	/// Channel for the text bubble position
	CAnimChannelPoint mPositionChannel;

	/// Channel for the text bubble text
	CAnimChannelText mTextChannel;
};

