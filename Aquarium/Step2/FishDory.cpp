/**
 * \file FishDory.cpp
 *
 * \author Po-An Tsai
 */

#include "stdafx.h"
#include "FishDory.h"

using namespace std;

/// Fish filename 
const wstring FishDoryImageName(L"images/dory.png");

/** Constructor
* \param aquarium The aquarium this is a member of
*/
CFishDory::CFishDory(CAquarium *aquarium) : CFish(aquarium, FishDoryImageName)
{
}

/**
 * \brief Destructor
 */
CFishDory::~CFishDory()
{
}

/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \return a XmlNode type
*/
std::shared_ptr<xmlnode::CXmlNode> CFishDory::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CFish::XmlSave(node);

	itemNode->SetAttribute(L"type", L"dory");

	return itemNode;
}