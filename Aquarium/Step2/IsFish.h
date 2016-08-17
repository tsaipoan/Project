/**
 * \file IsFish.h
 *
 * \author Zoe Hayes
 *
 * \brief Visitor that asks items if they are a fish
 */

#pragma once
#include "ItemVisitor.h"
/**
 * \brief Visitor that asks items if they are a fish
 */
class CIsFish :
	public CItemVisitor
{
public:
	///Constructor
	CIsFish();
	///Destructor
	virtual ~CIsFish();

	/**
	* \brief Visits beta fish
	*/
	virtual void VisitBeta(CFishBeta *beta) { mIsFish = true; }

	/**
	* \brief Visits dory fish
	*/
	virtual void VisitDory(CFishDory *dory) { mIsFish = true; }

	/**
	* \brief Visits nemo fish
	*/
	virtual void VisitNemo(CFishNemo *nemo) { mIsFish = true; }

	/**
	* \brief Visits cat fish
	*/
	virtual void VisitCat(CFishCat *cat) { mIsFish = true; }

	/**
	* \brief Visits decor treasure
	*/
	virtual void VisitTreasure(CDecorTreasure *treasure) {}

	/** \brief Tells if item is fish or not
	* \returns if it is a fish
	*/
	bool IsFish(){ return mIsFish; }

private:
	/// Fish status
	bool mIsFish = false;
};

