/**
* \file Prob.h
*
* \author Po-An Tsai
*
* \brief Implements the object of a characters prob,
* which has special functionality.
*/

#pragma once
#include "ImageDrawable.h"
#include "AnimChannelPoint.h"

/** \brief Implements the object of a characters prob,
* which has special functionality.
*/
class CProb :
	public CImageDrawable
{
public:
	CProb(const std::wstring &name, const std::wstring &filename);
	~CProb();

	/** \brief Default constructor disabled */
	CProb() = delete;
	/** \brief Copy constructor disabled */
	CProb(const CProb &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CProb &) = delete;

	/// \brief Is this drawable moveable?
	/// \returns true
	virtual bool IsMovable() { return true; }

	void Draw(Gdiplus::Graphics *graphics);
	

	virtual void SetActor(CActor *actor) override;
	virtual void SetTimeline(CTimeline *timeline) override;
	virtual void SetKeyframe() override;
	virtual void GetKeyframe() override;

private:

	/// Channel for the prob position
	CAnimChannelPoint mPositionChannel;
};

