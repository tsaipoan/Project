/**
 * \file DecorTreasure.h
 *
 * \author Po-An Tsai
 *
 * \brief Class the implements a Decor Treasure
 */

#pragma once
#include "Item.h"

/**
* \brief Implements a Decor Treasure
*/
class CDecorTreasure :
	public CItem
{
public:
	CDecorTreasure(CAquarium *aquarium);

	/// \brief Default constructor (disabled)
	CDecorTreasure() = delete;

	/// \brief Copy constructor (disabled)
	CDecorTreasure(const CDecorTreasure &) = delete;

	~CDecorTreasure();

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	virtual void Accept(CItemVisitor *visitor) override { visitor->VisitTreasure(this); }
};

