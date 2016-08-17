/** \ Prey.h
*
*  Authors: Po-An, Zoe, Joseph
*/
#pragma once
#include "ItemVisitor.h"
class CPrey :
	public CItemVisitor
{
public:
	/// \brief Construtor
	CPrey();
	/// \brief Deconstuctor
	virtual ~CPrey();
	/**
	* \brief Visits cat fish
	* \param cat Cat fish
	*/
	virtual void VisitCat(CFishCat *cat);

	/**
	* \brief Visits beta fish
	* \param beta Beta fish
	*/
	virtual void VisitBeta(CFishBeta *beta);
};

