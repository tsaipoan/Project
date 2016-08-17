/**
 * \file HaroldFactory.h
 *
 * \author Charles B. Owen
 * \author Po-An Tsai
 *
 * \brief Factory class that builds the Harold character
 */

#pragma once
#include "ActorFactory.h"

class CTextBubbleDrawable;

/** 
 * \brief Factory class that builds the Harold character 
 */
class CHaroldFactory :
    public CActorFactory
{
public:
    CHaroldFactory();
    virtual ~CHaroldFactory();

    std::shared_ptr<CActor> Create(); 

	/** \brief The text bubble drawable
	* \returns The text bubble drawable */
	std::shared_ptr<CTextBubbleDrawable> GetTextBubble() { return mTextBubble; }

private:
	/// The text bubble drawable
	std::shared_ptr<CTextBubbleDrawable> mTextBubble;
};

