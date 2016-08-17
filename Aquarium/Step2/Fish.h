/**
 * \file Fish.h
 *
 * \author Po-An Tsai
 *
 * \brief Class that move the fish
 */
#pragma once
#include "Item.h"

/** \brief Base class for a fish
 * This applies to all of the fish, but not the decor
 * items in the aquarium.
 */
class CFish : public CItem
{
public:
	/// \brief Default constructor (disabled)
	CFish() = delete;

	/// \brief Copy constructor (disabled)
	CFish(const CFish &) = delete;

	virtual ~CFish();

	void Update(double elapsed);

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);

	void FishBehave(const double, const double, const double, const double);

protected:
	CFish::CFish(CAquarium *aquarium, const std::wstring &filename);

private:
	/// Fish speed in the X direction
	double mSpeedX;

	/// Fish speed in the Y direction
	double mSpeedY;
};

