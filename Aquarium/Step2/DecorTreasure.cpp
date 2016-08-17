/**
 * \file DecorTreasure.cpp
 *
 * \author Po-An Tsai
 */

#include "stdafx.h"
#include "DecorTreasure.h"

using namespace std;


/// Fish filename 
const wstring DecorTreasureImageName(L"images/treasure-chest.png");

/** Constructor
* \param aquarium The aquarium this is a member of
*/
CDecorTreasure::CDecorTreasure(CAquarium *aquarium) : CItem(aquarium, DecorTreasureImageName)
{
}

/**
* \brief Destructor
*/
CDecorTreasure::~CDecorTreasure()
{
}

/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \return a XmlNode type
*/
std::shared_ptr<xmlnode::CXmlNode> CDecorTreasure::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CItem::XmlSave(node);

	itemNode->SetAttribute(L"type", L"treasure-chest");

	return itemNode;
}
