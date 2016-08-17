/**
* \file AnimChannelText.h
*
* \brief An animation channel specific to text
*
* \author Po-An Tsai
*/

#pragma once
#include "AnimChannel.h"

/** \brief An animation channel specific to text
*/
class CAnimChannelText :
	public CAnimChannel
{
public:
	CAnimChannelText();
	virtual ~CAnimChannelText();

	/// \brief The text we use
	/// \return The text
	std::wstring GetText() { return mText; }

	/// \brief The mirror we use
	/// \return The mirror
	std::wstring GetMirror() { return mMirrored; }

	/// \brief A keyframe for a text channel
	class KeyframeText : public Keyframe
	{
	public:
		/** \brief Constructor
		* \param channel The channel we are for
		* \param text The animation text for the keyframe
		* \param mirror The animation mirror for the keyframe */
		KeyframeText(CAnimChannelText *channel, std::wstring text, std::wstring mirror) :
			Keyframe(channel), mChannel(channel), mText(text), mMirrored(mirror) {}

		/** \brief Default constructor disabled */
		KeyframeText() = delete;
		/** \brief Copy constructor disabled */
		KeyframeText(const KeyframeText &) = delete;
		/** \brief Assignment operator disabled */
		void operator=(const KeyframeText &) = delete;

		/// \brief The keyframe text
		/// \return The keyframe text
		std::wstring GetText() { return mText; }

		/// \brief The keyframe mirror
		/// \return The keyframe mirror
		std::wstring GetMirror() { return mMirrored; }

		/** \brief Use this keyframe as keyframe 1 */
		virtual void UseAs1() override { mChannel->mKeyframe1 = this; }

		/** \brief Use this keyframe as keyfraem 2 */
		virtual void UseAs2() override { mChannel->mKeyframe2 = this; }

		/** \brief Use this keyframe as the text bubble */
		virtual void UseOnly() override { mChannel->mText = mText; mChannel->mMirrored = mMirrored; }

		virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node);

	private:
		std::wstring mText = L"";             ///< The unadulterated text

		std::wstring mMirrored = L"not mirrored";             ///< The unadulterated text

		/// The channel this keyframe is associated with
		CAnimChannelText *mChannel;
	};

	void SetKeyframe(std::wstring text, std::wstring mirror);
	void Tween(double t);

protected:
	virtual void XmlLoadKeyframe(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

private:
	std::wstring mText = L"";             ///< The unadulterated text

	std::wstring mMirrored = L"not mirrored";             ///< The unadulterated text

	/// The first text keyframe
	KeyframeText *mKeyframe1 = nullptr;

	/// The second text keyframe
	KeyframeText *mKeyframe2 = nullptr;
};

