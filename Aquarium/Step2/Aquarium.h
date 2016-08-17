/**
 * \file Aquarium.h
 *
 * \author Po-An Tsai
 *
 * \brief Class that represents an aquarium.
 */
#pragma once
#include "XmlNode.h"
#include <memory>
#include <vector>
#include "Item.h"
#include "Environment.h"
#include "Score.h"
#include <list>

class CItem;
class CEnvironment;

/**
 * \brief Represents an aquarium
 */
class CAquarium
{
public:
	/// Constructor
    CAquarium();
	/// Destructor
    virtual ~CAquarium();

	/// Draw the aquarium
	void OnDraw(Gdiplus::Graphics *graphics, CRect rect);

	/// Add item to the aquarium
	void Add(std::shared_ptr<CItem> item);

	/// Tests if something at point x,y and if so returns pointer
	std::shared_ptr<CItem> HitTest(int x, int y);

	/// Move the item to the front of the mItems item storage
	void MoveToFront(std::shared_ptr<CItem> item);

	/// Delete fish from the aquarium
	void DeleteFish(std::shared_ptr<CItem> item);

	/// Save the aquarium
	void Save(const std::wstring &filename);

	/// Load the aquarium
	void Load(const std::wstring &filename);

	/// Empty the aquarium
	void Clear();

	/// Tests if the aquarium is empty
	bool IsEmpty();

	/// Update the aquarium from the elapsed time
	void Update(double elapsed);

	/// \brief Get the width of the aquarium
	/// \returns Aquarium width
	int GetWidth() const { return mBackground->GetWidth(); }

	/// \brief Get the height of the aquarium
	/// \returns Aquarium height
	int GetHeight() const { return mBackground->GetHeight(); }

	/// Toggles the trash can on/off
	void CAquarium::ToggleTrashCanActive();

	/// \brief Is the trash can active?
	/// \returns true if trash can is active.
	bool IsTrashcanActive() const { return mTrashcanActive; }

	/// Tests if point is over trash can
	bool CAquarium::IsOverTrashcan(int x, int y);

	/// Delete item from aqarium
	void CAquarium::DeleteItem(std::shared_ptr<CItem> item);

	/// If point is over navigation mode icon, toggle the mode
	void CAquarium::NavigationMode(int x, int y);

	/**
	* \brief Gets status of navigation mode
	* \returns Status of navigation mode
	*/
	bool IsNavigationActive() const { return mNavigationActive; }

	/// Updates background for scrolling
	void ScrolledBackground(int x, int y);

	/**
	* \brief Gets DrawX
	* \returns mDrawX
	*/
	int GetDrawX() const{ return mDrawX; }

	/**
	* \brief Gets DrawX
	* \returns mDrawX
	*/
	int GetDrawY() const{ return mDrawY; }

	/**
	* \brief Sets mCleanTime to 0
	*/
	void ResetCleanTime() { mCleanTime = 0; }

	/**
	* \brief Sets mFoodTime to 0
	*/
	void ResetFoodTime() { mFoodTime = 0; }

	/**
	* \brief Sets mHungerMessage
	* \param a Value to set it to
	*/
	void SetHungerMessage(bool a) { mHungerMessage = a; }


	/**
	* \brief Sets mHungerDyingMessage
	* \param a Value to set it to
	*/
	void SetHungerDyingMessage(bool a) { mHungerDyingMessage = a; }

	/*void GetNemoTarget(CFish *nemo, bool isnemo);

	void GetDoryTarget(CFish *dory, bool isdory);*/

	/// Accepts visitor
	void Accept(CItemVisitor *visitor);

	/// Adds fish to be eaten
	void AddEatFish(std::shared_ptr<CItem> item);

	/// Eats fish
	void EatFish();

	/**
	* \brief Gets mItems
	* \returns mItems
	*/
	std::vector<std::shared_ptr<CItem> > GetItems() { return mItems; }

	/// Sets which background to use
	void SetBkg(int num);

	/** \brief Gets the aquarium score
	* \return score
	*/
	double GetScore(){ return mScore.GetScore(); }

	/** \brief Adds score - subtracts if negative
	* \param num The number to add
	* \return true if successful (score doesn't go negative)
	*/
	bool AddScore(int num){ return mScore.AddScore(num); }

	/**
	* \brief Gets the cleanliness stage of the tank
	* \returns 0,1,2,3 are the different stages
	*/
	int GetCleanStage() { return mEnvironment.GetCleanStage(); }

	/** \brief gets number of prey
	*  /returns number of prey
	*/
	int GetNumPrey();

	/** \brief gets number of predators
	*  /returns number of predators
	*/
	int GetNumPredators();

private:
    std::shared_ptr<Gdiplus::Bitmap> mBackground; ///< Current background image to use
	std::shared_ptr<Gdiplus::Bitmap> mBackground0; ///< Background image for clean stage 0 
	std::shared_ptr<Gdiplus::Bitmap> mBackground1; ///< Background image for clean stage 1 
	std::shared_ptr<Gdiplus::Bitmap> mBackground2; ///< Background image for clean stage 2 
	std::shared_ptr<Gdiplus::Bitmap> mBackground3; ///< Background image for clean stage 3 

    /// All of the items to populate our aquarium
    std::vector<std::shared_ptr<CItem> > mItems;

	/// All item that needs to be delete
	std::list<std::shared_ptr<CItem> > mToRemove;

	void XmlItem(const std::shared_ptr<xmlnode::CXmlNode> &node);

	std::unique_ptr<Gdiplus::Bitmap> mTrashcan; ///< Trashcan image to use
	bool mTrashcanActive = false;               ///< Is the trash can active?
	bool mNavigationActive = false;///< Is the nav image active

	/// Image for nav icon
	std::unique_ptr<Gdiplus::Bitmap> mNavigation;

	int mHeight; ///< Aquarium height
	int mWidth; ///< Aquarium width

	int mDrawX = 0; ///< X position for scrolling
	int mDrawY = 0; ///< Y position fro scrolling

	/// Time since last cleaned - Determines cleanliness state
	double mCleanTime = 0;

	/// Time since last fed - Determines hunger state
	double mFoodTime = 0;

	/// Whether or not the hunger message has been displayed
	bool mHungerMessage = false;

	/// Whether or not the hunger dying message has been displayed
	bool mHungerDyingMessage = false;

	/// Environment for the aquarium
	CEnvironment mEnvironment = CEnvironment(this);

	/// Score for the aquarium
	CScore mScore = CScore(this);

};