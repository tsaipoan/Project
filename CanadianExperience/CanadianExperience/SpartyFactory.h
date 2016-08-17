/**
 * \file SpartyFactory.h
 *
 * \author Charles B. Owen
 * \author Po-An Tsai
 *
 * \brief Factory that builds the Sparty actor.
 */

#pragma once
#include "ActorFactory.h"

class CTextBubbleDrawable;

/**
 * \brief Factory that builds the Sparty actor.
 */
class CSpartyFactory :
    public CActorFactory
{
public:
    CSpartyFactory();
    virtual ~CSpartyFactory();

    std::shared_ptr<CActor> Create();

	/** \brief The text bubble drawable
	* \returns The text bubble drawable */
	std::shared_ptr<CTextBubbleDrawable> GetTextBubble() { return mTextBubble; }

private:
	/// The text bubble drawable
	std::shared_ptr<CTextBubbleDrawable> mTextBubble;

};

