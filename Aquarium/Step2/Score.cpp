/**
 * \file Score.cpp
 *
 * \author Zoe Hayes, Joey Hollopter, Po-An Tsai
 */

#include "stdafx.h"
#include "Score.h"
#include "Aquarium.h"
#include "Item.h"
#include "IsFish.h"
#include "IsPredator.h"
#include "IsPrey.h"
#include <vector>

using namespace std;

const double betaScore = 2; ///<number of points per second the fish generates
const double catScore = 1.75; ///<number of points per second the fish generates
const double decorScore = 1.25; ///<number of points per second the treasure generates
const double doryScore = 2.5; ///<multiplier to be applied to prey points for each fish
const double nemoScore = 4; ///<multiplier to be applied to prey points for each fish
const double clean0modifier = 1; ///<multiplier for a clean tank
const double clean1modifier = .75; ///<multiplier for a slightly dirty tank
const double clean2modifier = .50; ///<multiplier for a dirty tank
const double clean3modifier = .20; ///<multiplier for a ohgodwhy dirty tank
const double timeLimit = 540; ///<time limit in seconds

/**
 * \brief Destructor
 */
CScore::~CScore()
{
}

/**
* \brief Adds to score (negative values passed will subtract from score)
* \param num The value to add/subtract
* \returns true if operation is successful (points wont go into negative)
*/
bool CScore::AddScore(double num) 
{
	if ((mScore + num) > 0)
	{
		mScore += num;
		return true;
	}
	return false;
}

/**
 * \brief Updates the score
 */
void CScore::Update(double elapsed)
{
	bool empty = true;
	//if game has started, then start counting the time
	if (mStart) 
		mTime += elapsed;
	//handle modifier for cleanliness
	double modifier;
	int cleanStage = mAquarium->GetCleanStage();
	switch (cleanStage)
	{
	case 1:
		modifier = clean1modifier;
		break;
	case 2:
		modifier = clean2modifier;
		break;
	case 3:
		modifier = clean3modifier;
		break;
	default:
		modifier = clean0modifier;
		break;
	}
	//get items list
	vector<shared_ptr<CItem> > items = mAquarium->GetItems();
	//sort through list, and if it is a fish, give points
	double scorePrey = 0, scoreDecor = 0;
	int doryCount = 0, nemoCount = 0;
	for (auto item : items)
	{
		CIsFish visitor;
		item->Accept(&visitor);
		if (visitor.IsFish())
		{
			mStart = true;
			empty = false;
			CIsPredator predVisitor;
			CIsPrey preyVisitor;
			item->Accept(&predVisitor);
			item->Accept(&preyVisitor);
			if (predVisitor.IsDory())
			{
				doryCount++;
			}
			else if (predVisitor.IsNemo())
			{
				doryCount++;
			}
			else if (preyVisitor.IsBeta())
			{
				scorePrey += betaScore*elapsed*modifier;
			}
			else if (preyVisitor.IsCat())
			{
				scorePrey += catScore*elapsed*modifier;
			}
		}
		else
		{
			scoreDecor += decorScore*elapsed*modifier;
		}
	}
	//sum all score components and add to total score, set points/sec too
	if (doryCount == 0 && nemoCount == 0)
		mPointsSec = scorePrey + scoreDecor;
	else if (doryCount == 0 && nemoCount != 0)
		mPointsSec = (nemoCount*nemoScore)*scorePrey + scoreDecor;
	else if (doryCount != 0 && nemoCount == 0)
		mPointsSec = (doryCount*doryScore)*scorePrey + scoreDecor;
	else if (doryCount != 0 && nemoCount != 0)
		mPointsSec = (doryCount*doryScore + nemoCount*nemoScore)*scorePrey + scoreDecor;
	mScore += mPointsSec;
	mPointsSec = mPointsSec / elapsed;
	//ending conditions - tank is empty and the game has started, or timelimit reach and game started
	if (empty && mStart)
	{
		mStart = false;
		wstring score = L"You lost the game!\n You lasted for: " + to_wstring(int(mTime)) + L" seconds.\n Your Score: " + to_wstring(int(mScore));
		const wchar_t* scoreString = score.c_str();
		mTime = 0;
		mScore = 200;
		mAquarium->ResetCleanTime();
		mAquarium->ResetFoodTime();
		mAquarium->Clear();
		AfxMessageBox(scoreString);
	}
	if (mTime >= timeLimit && mStart)
	{
		mStart = false;
		wstring score = L"You lasted until the time limit!\n Your Score: " + to_wstring(int(mScore));
		const wchar_t* scoreString = score.c_str();
		mTime = 0;
		mScore = 200;
		mAquarium->ResetCleanTime();
		mAquarium->ResetFoodTime();
		mAquarium->Clear();
		AfxMessageBox(scoreString);
	}
}

/**
* \brief Get the time remaining in the game
* \returns the time remaining
*/
double CScore::GetTimeRemaining()
{ 
	return timeLimit-mTime; 
}
