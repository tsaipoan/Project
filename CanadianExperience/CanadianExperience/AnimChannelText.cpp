/**
* \file AnimChannelText.cpp
*
* \author Po-An Tsai
*/
#include "stdafx.h"
#include "AnimChannelText.h"

using namespace std;

/**
* \brief Constructor
*/
CAnimChannelText::CAnimChannelText()
{
}


/**
* \brief Destructor
*/
CAnimChannelText::~CAnimChannelText()
{
}



/**
* \brief Set a keyframe
*
* This function allocates a new keyframe and sends it to
* CAnimChannel, which will insert it into the collection of keyframes.
* \param text The text for the keyframe
* \param mirror The mirror for the keyframe
*/
void CAnimChannelText::SetKeyframe(std::wstring text, std::wstring mirror)
{
	// Create a keyframe of the appropriate type
	// Telling it this channel and the angle
	shared_ptr<KeyframeText> keyframe = make_shared<KeyframeText>(this, text, mirror);

	// Insert it into the collection
	InsertKeyframe(keyframe);
}




/** \brief Save this keyframe to an XML node
* \param node The node we are going to be a child of
* \returns Allocated XML node.
*/
std::shared_ptr<xmlnode::CXmlNode> CAnimChannelText::KeyframeText::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CAnimChannel::Keyframe::XmlSave(node);
	itemNode->SetAttribute(L"text", mText);
	itemNode->SetAttribute(L"mirror", mMirrored);

	return itemNode;
}



/**
* \brief Handle loading this channel's keyframe type
* \param node keyframe tag node
*/
void CAnimChannelText::XmlLoadKeyframe(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	wstring text = node->GetAttributeValue(L"text", L"");
	wstring mirror = node->GetAttributeValue(L"mirror", L"");

	// Set a keyframe there
	SetKeyframe(text, mirror);
}

/** \brief Compute a tweened text between to text
* \param t The tweening t value
*/
void CAnimChannelText::Tween(double t)
{
	if (t == 1)
	{
		mText = mKeyframe2->GetText();
		mMirrored = mKeyframe2->GetMirror();
	}
	else
	{
		mText = mKeyframe1->GetText();
		mMirrored = mKeyframe1->GetMirror();
	}
}