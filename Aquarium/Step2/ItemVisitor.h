/**  ItemVisitor.h
*/
#pragma once

class CFishBeta;
class CFishDory;
class CFishNemo;
class CFish;
class CDecorTreasure;
class CFishCat;

/**
 * \brief Visitor class for items
 */
class CItemVisitor
{
public:
	///Constructor
	CItemVisitor();
	///Destructor
	virtual ~CItemVisitor();

	/**
	* \brief Visits beta fish
	*/
	virtual void VisitBeta(CFishBeta *beta) {}

	/**
	* \brief Visits dory fish
	*/
	virtual void VisitDory(CFishDory *dory) {}

	/**
	* \brief Visits nemo fish
	*/
	virtual void VisitNemo(CFishNemo *nemo) {}

	/**
	* \brief Visits cat fish
	*/
	virtual void VisitCat(CFishCat *cat) {}

	/**
	* \brief Visits decor treasure
	*/
	virtual void VisitTreasure(CDecorTreasure *treasure) {}

};

