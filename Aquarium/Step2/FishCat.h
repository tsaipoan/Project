/**
* \file FishCat.h
*
* \author Po-An Tsai
*
* \brief Class the implements a Cat fish
*/

#pragma once

#include "Item.h"
#include "Fish.h"


/**
* \brief Implements a Cat fish
*/
class CFishCat : public CFish
{
public:
	CFishCat(CAquarium *aquarium);

	/// \brief Default constructor (disabled)
	CFishCat() = delete;

	/// \brief Copy constructor (disabled)
	CFishCat(const CFishCat &) = delete;

	~CFishCat();

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	virtual void Accept(CItemVisitor *visitor) override { visitor->VisitCat(this); }
};

