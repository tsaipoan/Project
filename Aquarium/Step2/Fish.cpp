/**
* \file Fish.cpp
*
* \author Po-An Tsai
*/

#include "stdafx.h"
#include "Fish.h"
#include "Aquarium.h"



/** Constructor
* \param aquarium The aquarium we are in
* \param filename Filename for the image we use
*/
CFish::CFish(CAquarium *aquarium, const std::wstring &filename) : CItem(aquarium, filename)
{
	if (filename == L"images/nemo.png")
	{
		FishBehave(-70, -50, -70, -50);
	}
	else if (filename == L"images/beta.png")
	{
		FishBehave(50, 30, 20, 10);
	}
	else if (filename == L"images/dory.png")
	{
		FishBehave(0, 0, -50, -20);
	}
	else
	{
		FishBehave(100, 90, -50, -20);
	}
	
	
}

/**
* \brief Destructor
*/
CFish::~CFish()
{
}

/** \brief Handle updates in time of our fish
*
* This is called before we draw and allows us to
* move our fish. We add our speed times the amount
* of time that has elapsed.
* \param elapsed Time elapsed since the class call
*/
void CFish::Update(double elapsed)
{
	
	SetLocation(GetX() + mSpeedX * elapsed,
		GetY() + mSpeedY * elapsed);
		
	if (mSpeedX > 0)
	{
		SetMirror(mSpeedX < 0);
		if (GetX() >= (GetAquarium()->GetWidth() - 50 - GetWidth() / 2))
		{
			mSpeedX = -mSpeedX;
		}
	}
	else if (mSpeedX < 0)
	{
		SetMirror(mSpeedX < 0);
		if (GetX() <= (0 + 50 + GetWidth() / 2))
		{
			mSpeedX = -mSpeedX;
		}
	}
	

	if (mSpeedY > 0 && GetY() >= (GetAquarium()->GetHeight() - 50 - GetHeight() / 2))
	{
		mSpeedY = -mSpeedY;
	}
	else if (mSpeedY < 0 && GetY() <= (0 + 50 + GetHeight() / 2))
	{
		mSpeedY = -mSpeedY;
	}


	if (mSpeedX == 0.0 && GetY() <= (0 + 50 + GetHeight() / 2))
	{
		FishBehave(100, 100, 0, 0);
	}
	else if (mSpeedX == 0.0 && GetY() >= (GetAquarium()->GetHeight() - 50 - GetHeight() / 2))
	{
		FishBehave(-100, -100, 0, 0);
	}
	else if (mSpeedY == 0.0 && GetX() <= (0 + 50 + GetWidth() / 2))
	{
		FishBehave(0, 0, -70, -70);
	}
	else if (mSpeedY == 0.0 && GetX() >= (GetAquarium()->GetWidth() - 50 - GetWidth() / 2))
	{
		FishBehave(0, 0, 70, 70);
	}
	
	
}

/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \return a XmlNode type
*/
std::shared_ptr<xmlnode::CXmlNode> CFish::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CItem::XmlSave(node);

	itemNode->SetAttribute(L"SpeedX", mSpeedX);
	itemNode->SetAttribute(L"SpeedY", mSpeedY);

	return itemNode;
}

/**
* brief Load the attributes for an item node.
*
* This is the  base class version that loads the attributes
* common to all items. Override this to load custom attributes
* for specific items.
*
* \param node The Xml node we are loading the item from
*/
void CFish::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	CItem::XmlLoad(node);
	mSpeedX = node->GetAttributeDoubleValue(L"SpeedX", 0);
	mSpeedY = node->GetAttributeDoubleValue(L"SpeedY", 0);
}

/** \brief create a speed on X and Y plane
* \param MaxSpeedX the maximum speed in X
* \param MinSpeedX the minimum speed in X
* \param MaxSpeedY the maximum speed in Y
* \param MinSpeedY the minimum speed in Y
*/
void CFish::FishBehave(const double MaxSpeedX, const double MinSpeedX, const double MaxSpeedY, const double MinSpeedY)
{
	mSpeedX = MinSpeedX + ((double)rand() / RAND_MAX) * (MaxSpeedX - MinSpeedX);
	mSpeedY = MinSpeedY + ((double)rand() / RAND_MAX) * (MaxSpeedY - MinSpeedY);
}
