/**
 * \file Predator.h
 *
 * \author Zoe Hayes, Joseph Hollopter, Po-An Tsai
 *
 * \brief Predator fish visitor class
 */

#pragma once
#include "ItemVisitor.h"
/**
 * \brief Predator fish visitor class
 */
class CPredator :
	public CItemVisitor
{
public:
	CPredator();
	virtual ~CPredator();
	/**
	* \brief Visits dory fish
	* \param dory Dory we are visiting
	*/
	virtual void VisitDory(CFishDory *dory);

	/**
	* \brief Visits nemo fish
	* \param nemo Nemo we are visiting
	*/
	virtual void VisitNemo(CFishNemo *nemo);

	void GetNemoTarget(CFish *nemo, bool isnemo);

	void GetDoryTarget(CFish *dory, bool isdory);


};

