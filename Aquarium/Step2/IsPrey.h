/**
 * \file IsPrey.h
 *
 * \author Zoe, Joey, Po-An
 *
 * \brief Visitor to check if item is prey
 */

#pragma once
#include "ItemVisitor.h"
/**
 * \brief Visitor to check if item is prey
 */
class CIsPrey :
	public CItemVisitor
{
public:
	CIsPrey();
	virtual ~CIsPrey();

	/** \brief check the Fish is beta or not
	* \param beta CFishBeta visit in */
	virtual void VisitBeta(CFishBeta *beta) override { mIsBeta = true; mIsPrey = true; mNum++; }

	/** \brief return the mIsBeta
	* \returns true or false */
	bool IsBeta() const { return mIsBeta; }

	/** \brief check the Fish is cat or not
	* \param cat CFishCat visit in */
	virtual void VisitCat(CFishCat *cat) override { mIsCat = true; mIsPrey = true; mNum++; }

	/** \brief return the mIsCat
	* \returns true or false */
	bool IsCat() const { return mIsCat; }

	/** \brief return the mIsPrey
	* \returns true or false */
	bool IsPrey() const { return mIsPrey; }

	/** \brief return the number of prey
	* \returns num of prey */
	int NumPrey() const { return mNum; }

private:
	/// true or false for the item
	bool mIsBeta = false;
	/// true or false for the item
	bool mIsCat = false;
	/// true or false for the item
	bool mIsPrey = false;
	/// num of prey
	int mNum = 0;
};

