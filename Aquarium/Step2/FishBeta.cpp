/**
 * \file FishBeta.cpp
 *
 * \author Po-An Tsai
 */

#include "stdafx.h"
#include "FishBeta.h"

using namespace std;

/// Fish filename 
const wstring FishBetaImageName(L"images/beta.png");

/** Constructor
* \param aquarium The aquarium this is a member of
*/
CFishBeta::CFishBeta(CAquarium *aquarium) : CFish(aquarium, FishBetaImageName)
{
}

/**
 * \brief Destructor
 */
CFishBeta::~CFishBeta()
{
}

/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \return a XmlNode type
*/
std::shared_ptr<xmlnode::CXmlNode> CFishBeta::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CFish::XmlSave(node);

	itemNode->SetAttribute(L"type", L"beta");

	return itemNode;
}