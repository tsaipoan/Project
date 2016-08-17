/** \ IsPredator.h
*
*  Authors: Po-An, Zoe, Joseph
*/
#pragma once
#include "ItemVisitor.h"
/**
 * \brief Checks if fish is predator or not
 */
class CIsPredator :
	public CItemVisitor
{
public:
	/// construtor
	CIsPredator();
	/// destrutor
	virtual ~CIsPredator();

	/** \brief check the Fish is Nemo or not
	* \param Nemo CFishNemo visit in */
	virtual void VisitNemo(CFishNemo *Nemo) override { mIsPredator = true; mIsNemo = true; mNum++; }

	/** \brief check the Fish is Dory or not
	* \param Dory CFishDory visit in */
	virtual void VisitDory(CFishDory *Dory) override { mIsPredator = true; mIsDory = true; mNum++; }

	/// \brief returns mIsPredator (if fish is predator)
	bool IsPredator(){ return mIsPredator; }

	/** \brief Check if nemo fish
	* \return mIsNemo
	*/
	bool IsNemo(){ return mIsNemo; }

	/** \brief Check if dory fish
	* \return mIsDory
	*/
	bool IsDory(){ return mIsDory; }

	/** \brief return the number of predators
	* \returns num of predators */
	int NumPredators() const { return mNum; }
private:
	/// \brief if fish is predator
	bool mIsPredator = false;

	/// if fish is a nemo
	bool mIsNemo = false;

	/// if fish is a dory
	bool mIsDory = false;

	/// num of predators
	int mNum = 0;
};

