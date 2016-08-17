/**
 * \file Aquarium.cpp
 *
 * \author Po-An Tsai
 */

#include "stdafx.h"
#include "Aquarium.h"
#include "resource.h"
#include <algorithm>

#include "Item.h"
#include "XmlNode.h"
#include "FishBeta.h"
#include "FishNemo.h"
#include "FishDory.h"
#include "FishCat.h"
#include "ItemVisitor.h"
#include "DecorTreasure.h"
#include "IsPrey.h"
#include "IsPredator.h"

#include <math.h>
#include <sstream>
#include <iomanip>

using namespace std;
using namespace Gdiplus;
using namespace xmlnode;



/**
 * \brief Constructor
 */
CAquarium::CAquarium()
{
	
	mBackground0 = shared_ptr<Bitmap>(Bitmap::FromFile(L"images/backgroundW.png"));
	if (mBackground0->GetLastStatus() != Ok)
	{
		AfxMessageBox(L"Failed to open images/backgroundW.png");
	}
	mBackground1 = shared_ptr<Bitmap>(Bitmap::FromFile(L"images/backgroundW1.png"));
	if (mBackground1->GetLastStatus() != Ok)
	{
		AfxMessageBox(L"Failed to open images/backgroundW1.png");
	}
	mBackground2 = shared_ptr<Bitmap>(Bitmap::FromFile(L"images/backgroundW2.png"));
	if (mBackground2->GetLastStatus() != Ok)
	{
		AfxMessageBox(L"Failed to open images/backgroundW2.png");
	}
	mBackground3 = shared_ptr<Bitmap>(Bitmap::FromFile(L"images/backgroundW3.png"));
	if (mBackground3->GetLastStatus() != Ok)
	{
		AfxMessageBox(L"Failed to open images/backgroundW3.png");
	}
	mBackground = mBackground0;

	mTrashcan = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/trashcan.png"));
	if (mTrashcan->GetLastStatus() != Ok)
	{
		AfxMessageBox(L"Failed to open images/trashcan.png");
	}

	mNavigation = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/nav1.png"));
	if (mNavigation->GetLastStatus() != Ok)
	{
		AfxMessageBox(L"Failed to open images/nav1.png");
	}
	
}


/**
 * \brief Destructor
 */
CAquarium::~CAquarium()
{
}

/** \brief Draw the aquarium
 * \param graphics The GDI+ graphics context to draw on
 * \param rect The CRect we are using to get the window info
 */
void CAquarium::OnDraw(Gdiplus::Graphics *graphics, CRect rect)
{
	if (-mDrawY + rect.Height() > mBackground->GetHeight())
		mDrawY = rect.Height() - mBackground->GetHeight();

	if (-mDrawX + rect.Width() > mBackground->GetWidth())
		mDrawX = rect.Width() - mBackground->GetWidth();

	mHeight = rect.Height() - mNavigation->GetHeight();
	mWidth = rect.Width() - mNavigation->GetWidth();
	graphics->DrawImage(mBackground.get(), mDrawX, mDrawY,
		mBackground->GetWidth(), mBackground->GetHeight());

	graphics->DrawImage(mNavigation.get(), mWidth, mHeight,
		mNavigation->GetWidth(), mNavigation->GetHeight());

	if (mTrashcanActive)
	{
		graphics->DrawImage(mTrashcan.get(), 0, 0,
			mTrashcan->GetWidth(), mTrashcan->GetHeight());
	}

	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 16);

	stringstream s;
	// print it into sstream using maximum precision
	s << fixed << setprecision(2) << mScore.GetPointsSec();
	std::string res = s.str();

	std::wstring uniString;
	// Convert one to the other:
	uniString.assign(res.begin(), res.end());

	SolidBrush green(Color(0, 0, 0));
	wstring score = L"Score: " + to_wstring(int(mScore.GetScore()));
	const wchar_t* scoreString = score.c_str();
	wstring points = L"Points/Sec: " + uniString;
	const wchar_t* pointsString = points.c_str();
	wstring time = L"Time Remaining: " + to_wstring(int(mScore.GetTimeRemaining()));
	const wchar_t* timeString = time.c_str();
	graphics->DrawString(scoreString, -1, &font, PointF(50, 2), &green);
	graphics->DrawString(pointsString, -1, &font, PointF(50, 25), &green);
	graphics->DrawString(timeString, -1, &font, PointF(210, 2), &green);

	for (auto item : mItems)
	{
		item->Draw(graphics, mDrawX, mDrawY);
	}
	
}

/** \brief Add an item to the aquarium
 * \param item New item to add
 */
void CAquarium::Add(std::shared_ptr<CItem> item)
{
	mItems.push_back(item);
}

/** \brief Test an x,y click location to see if it clicked
 * on some item in the aquarium.
 * \param x X location
 * \param y Y location
 * \returns Pointer to item we clicked on or nullptr if none.
 */
std::shared_ptr<CItem> CAquarium::HitTest(int x, int y)
{
	for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
	{
		if ((*i)->HitTest(x, y, mDrawX, mDrawY))
		{
			return *i;
		}
	}

	return  nullptr;
}

/** \brief Move an item to the front
 * \param item Erase and add again
 */
void CAquarium::MoveToFront(std::shared_ptr<CItem> item)
{
	auto loc = find(begin(mItems), end(mItems), item);
	if (loc != end(mItems))
	{
		mItems.erase(loc);
		mItems.push_back(item);
	}
}

/** \brief Delete an item to the aquarium
 * \param item to Delete
 */
void CAquarium::DeleteFish(std::shared_ptr<CItem> item)
{
	auto loc = find(begin(mItems), end(mItems), item);
	if (loc != end(mItems))
	{
		mItems.erase(loc);
	}
}


/** \brief Save the aquarium as a .aqua XML file.
*
* Open an XML file and stream the aquarium data to it.
*
* \param filename The filename of the file to save the aquarium to
*/
void CAquarium::Save(const std::wstring &filename)
{
	//
	// Create an XML document
	//
	auto root = CXmlNode::CreateDocument(L"aqua");

	// Iterate over all items and save them
	for (auto item : mItems)
	{
		item->XmlSave(root);
	}

	try
	{
		root->Save(filename);
	}
	catch (CXmlNode::Exception ex)
	{
		AfxMessageBox(ex.Message().c_str());
	}

}

/** \brief Load the aquarium from a .aqua XML file.
*
* Opens the XML file and reads the nodes, creating items as appropriate.
*
* \param filename The filename of the file to load the aquarium from.
*/
void CAquarium::Load(const std::wstring &filename)
{
	// We surround with a try/catch to handle errors
	try
	{
		// Open the document to read
		shared_ptr<CXmlNode> root = CXmlNode::OpenDocument(filename);

		// Once we know it is open, clear the existing data
		Clear();

		//
		// Traverse the children of the root
		// node of the XML document in memory!!!!
		//
		for (auto node : root->GetChildren())
		{
			if (node->GetType() == NODE_ELEMENT && node->GetName() == L"item")
			{
				XmlItem(node);
			}
		}
	}
	catch (CXmlNode::Exception ex)
	{
		AfxMessageBox(ex.Message().c_str());
	}

}

/**
* \brief Clear the aquarium data.
*
* Deletes all known items in the aquarium.
*/
void CAquarium::Clear()
{
	mItems.clear();
}

/**
* \brief check the mItmes data.
*
* Check if it is Empty or not
* \returns true if empty false otherwise
*/
bool CAquarium::IsEmpty()
{
	if (mItems.empty())
	{
		return true;
	}
	else
		return false;
}

/**
* \brief Handle an item node.
* \param node Pointer to XML node we are handling
*/
void CAquarium::XmlItem(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	// A pointer for the item we are loading
	shared_ptr<CItem> item;

	// We have an item. What type?
	wstring type = node->GetAttributeValue(L"type", L"");
	if (type == L"beta")
	{
		item = make_shared<CFishBeta>(this);
	}
	else if (type == L"treasure-chest")
	{
		item = make_shared<CDecorTreasure>(this);
	}
	else if (type == L"dory")
	{
		item = make_shared<CFishDory>(this);
	}
	else if (type == L"nemo")
	{
		item = make_shared<CFishNemo>(this);
	}
	else if (type == L"catfish")
	{
		item = make_shared<CFishCat>(this);
	}

	if (item != nullptr)
	{
		item->XmlLoad(node);
		Add(item);
	}
}

/** \brief Handle updates for animation
* \param elapsed The time since the last update
*/
void CAquarium::Update(double elapsed)
{
	for (auto item : mItems)
	{
		item->Update(elapsed);
	}
	mCleanTime += elapsed;
	mFoodTime += elapsed;
	mEnvironment.Update(mCleanTime, mFoodTime, mHungerMessage, mHungerDyingMessage);
	mScore.Update(elapsed);
	}

/** \brief Toggle the state of the flag mTrashCanActive
*/
void CAquarium::ToggleTrashCanActive()
{
	mTrashcanActive = !mTrashcanActive;
}

/** \brief Is this location over the trash can?
* \param x X location
* \param y Y location
* \returns true if x,y is over the trash can */
bool CAquarium::IsOverTrashcan(int x, int y)
{
	if (!mTrashcanActive)
	{
		return false;
	}

	return x < mTrashcan->GetWidth() && y < mTrashcan->GetHeight();
}

/** \brief Delete an item from the aquarium
*
* \param item The item to delete.
*/
void CAquarium::DeleteItem(std::shared_ptr<CItem> item)
{
	auto loc = find(begin(mItems), end(mItems), item);
	if (loc != end(mItems))
	{
		mItems.erase(loc);
	}

}

/**
 * \brief If point is over navigation mode icon, toggle the mode
 * \param x Point's x coord
 * \param y Point's y coord
 */
void CAquarium::NavigationMode(int x, int y)
{ 
	if (x > mWidth && y > mHeight)
	{
		mNavigationActive = !mNavigationActive;
		if (mNavigationActive)
		{
			mNavigation = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/nav2.png"));
			if (mNavigation->GetLastStatus() != Ok)
			{
				AfxMessageBox(L"Failed to open images/nav2.png");
			}
		}
		else
		{
			mNavigation = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/nav1.png"));
			if (mNavigation->GetLastStatus() != Ok)
			{
				AfxMessageBox(L"Failed to open images/nav1.png");
			}
		}
	}
}

/**
 * \brief Updates background for scrolling
 * \param x 
 * \param y 
 */
void CAquarium::ScrolledBackground(int x, int y)
{
	mDrawX = mDrawX - x;
	mDrawY = mDrawY - y;

	if (mDrawX > 0)
		mDrawX = 0;
	if (mDrawY > 0)
		mDrawY = 0;
}

/** \brief Accept a visitor for the collection
* \param visitor The visitor for the collection
*/
void CAquarium::Accept(CItemVisitor *visitor)
{
	for (auto item : mItems)
	{
		item->Accept(visitor);
	}
}

/** \brief Add an item to the mToRemove
* \param item New item to add
*/
void CAquarium::AddEatFish(std::shared_ptr<CItem> item)
{
	mToRemove.push_back(item);
}

/** \brief Delete item to the aquarium
*/
void CAquarium::EatFish()
{
	for (auto item : mToRemove)
	{
		auto loc = find(begin(mItems), end(mItems), item);
		if (loc != end(mItems))
		{
			mItems.erase(loc);
		}
	}
	mToRemove.clear();
}
/**
* \brief Sets which background to use
* \param num Is which bkg to use; 0=clean, 1=dirty, 2=reallydirty, 3=ohgodplzclean
*/
void CAquarium::SetBkg(int num)
{
	switch (num)
	{
	case 0:
		mBackground = mBackground0;
		break;
	case 1:
		mBackground = mBackground1;
		break;
	case 2:
		mBackground = mBackground2;
		break;
	case 3:
		mBackground = mBackground3;
		break;
	default:
		break;
	}
}

/** \brief gets number of prey
*  \returns number of prey
*/
int CAquarium::GetNumPrey()
{
	CIsPrey visitor;
	for (auto i : mItems)
	{
		i->Accept(&visitor);
	}
	return visitor.NumPrey();
}

/** \brief gets number of prey
*  \returns number of prey
*/
int CAquarium::GetNumPredators()
{
	CIsPredator visitor;
	for (auto i : mItems)
	{
		i->Accept(&visitor);
	}
	return visitor.NumPredators();
}