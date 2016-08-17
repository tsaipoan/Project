/**
 * \file FishBeta.h
 *
 * \author Po-An Tsai
 *
 * \brief Class the implements a Beta fish
 */

#pragma once

#include "Item.h"
#include "Fish.h"


/**
 * \brief Implements a Beta fish
 */
class CFishBeta : public CFish
{
public:
	CFishBeta(CAquarium *aquarium);

	/// \brief Default constructor (disabled)
	CFishBeta() = delete;

	/// \brief Copy constructor (disabled)
	CFishBeta(const CFishBeta &) = delete;

	~CFishBeta();

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	virtual void Accept(CItemVisitor *visitor) override { visitor->VisitBeta(this); }
};

