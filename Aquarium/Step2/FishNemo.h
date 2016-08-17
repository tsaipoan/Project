/**
 * \file FishNemo.h
 *
 * \author Po-An Tsai
 *
 * \brief Class the implements a Nemo fish
 */

#pragma once

#include "Item.h"
#include "Fish.h"


/**
 * \brief Implements a Nemo fish
 */
class CFishNemo : public CFish
{
public:
	CFishNemo(CAquarium *aquarium);

	/// \brief Default constructor (disabled)
	CFishNemo() = delete;

	/// \brief Copy constructor (disabled)
	CFishNemo(const CFishNemo &) = delete;

	~CFishNemo();

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	virtual void Accept(CItemVisitor *visitor) override { visitor->VisitNemo(this); }

};
