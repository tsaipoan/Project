/**
 * \file FishNemo.cpp
 *
 * \author Po-An Tsai
 */

#include "stdafx.h"
#include "FishNemo.h"

using namespace std;

/// Fish filename 
const wstring FishNemoImageName(L"images/nemo.png");

/** Constructor
* \param aquarium The aquarium this is a member of
*/
CFishNemo::CFishNemo(CAquarium *aquarium) : CFish(aquarium, FishNemoImageName)
{
}

/**
 * \brief Destructor
 */
CFishNemo::~CFishNemo()
{
}

/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \return a XmlNode type
*/
std::shared_ptr<xmlnode::CXmlNode> CFishNemo::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CFish::XmlSave(node);

	itemNode->SetAttribute(L"type", L"nemo");

	return itemNode;
}

