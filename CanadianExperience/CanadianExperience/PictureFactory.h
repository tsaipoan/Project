/**
 * \file PictureFactory.h
 *
 * \author Charles B. Owen
 * \author Po-An Tsai
 *
 * \brief A factory class that builds our picture.
 */

#pragma once

#include <memory>

#include "Picture.h"

class CTextBubbleDrawable;

/**
 * \brief A factory class that builds our picture.
 */
class CPictureFactory
{
public:
    CPictureFactory();
    virtual ~CPictureFactory();

    std::shared_ptr<CPicture> Create();

	/** \brief The text bubble drawable
	* \returns The harold text bubble drawable */
	std::shared_ptr<CTextBubbleDrawable> GetHaroldTextBubble() { return mTextBubbleHarold; }

	/** \brief The text bubble drawable
	* \returns The sparty text bubble drawable */
	std::shared_ptr<CTextBubbleDrawable> GetSpartyTextBubble() { return mTextBubbleSparty; }

private:
	/// The Harold text bubble drawable
	std::shared_ptr<CTextBubbleDrawable> mTextBubbleHarold;

	/// The Sparty text bubble drawable
	std::shared_ptr<CTextBubbleDrawable> mTextBubbleSparty;
};

