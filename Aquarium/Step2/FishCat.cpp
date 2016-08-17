/**
* \file FishCat.cpp
*
* \author Po-An Tsai
*/

#include "stdafx.h"
#include "FishCat.h"

using namespace std;

/// Fish filename 
const wstring FishBetaImageName(L"images/catfish.png");

/** Constructor
* \param aquarium The aquarium this is a member of
*/
CFishCat::CFishCat(CAquarium *aquarium) : CFish(aquarium, FishBetaImageName)
{
}

/**
* \brief Destructor
*/
CFishCat::~CFishCat()
{
}

/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \return a XmlNode type
*/
std::shared_ptr<xmlnode::CXmlNode> CFishCat::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CFish::XmlSave(node);

	itemNode->SetAttribute(L"type", L"catfish");

	return itemNode;
}