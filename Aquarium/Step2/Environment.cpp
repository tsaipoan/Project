/**
 * \file Environment.cpp
 *
 * \author Zoe Hayes
 */

#include "stdafx.h"
#include "Environment.h"
#include "Aquarium.h"
#include "Item.h"
#include "IsFish.h"
#include <vector>

using namespace std;

const double stage1cleanTime = 30; ///< time at which tank gets dirtier
const double stage2cleanTime = 75; ///< time at which tank gets dirtier
const double stage3cleanTime = 120;///< time at which tank gets dirtier
const double upTol = 2.53; ///< upper tolerance 
const double lowTol = 2.47; ///< lower tolerance
const double mod = 5; ///< modulus
const double stage1foodTime = 50; ///< time at which fish are hungry
const double stage2foodTime = 90; ///< time at which fish start dying of hunger
const double hungerDeathPenalty = -50; ///< penalty for fish dying of hunger

/**
 * \brief Constructor
 * \param aquarium 
 */
CEnvironment::CEnvironment(CAquarium *aquarium)
{
	mAquarium = aquarium;
}


/**
 * \brief Destructor
 */
CEnvironment::~CEnvironment()
{
}

/**
 * \brief Updates the environment i.e. the clean/dirty bkg, and hunger
 * \param cleanTime Time since last cleaning
 * \param foodTime Time since last feeding
 * \param hungerMessage If hungermessage has been displayed
 * \param hungerDyingMessage If hungerDyingMessage has been displayed
 */
void CEnvironment::Update(double cleanTime, double foodTime, bool hungerMessage, bool hungerDyingMessage)
{
	vector<shared_ptr<CItem> > items = mAquarium->GetItems();
	//Deletes fish if fish are past due for feeding and if the time%5 ~=2.5s so one fish is killed every 5s
	if ((foodTime > stage2foodTime) && (lowTol < fmod(foodTime, mod)) && (fmod(foodTime, mod)< upTol))
	{
		for (auto item : items)
		{
			CIsFish visitor;
			item->Accept(&visitor);
			if (visitor.IsFish())
			{
				mAquarium->AddScore(hungerDeathPenalty);
				mAquarium->DeleteFish(item);
				if (hungerDyingMessage == false)
				{
					mAquarium->SetHungerDyingMessage(true);
					hungerDyingMessage = true;
					AfxMessageBox(L"Fish are dying of hunger!");
				}
				break;
			}
		}
	}
	//Alert that fish are getting hungry
	else if ((foodTime > stage1foodTime) && hungerMessage == false)
	{
		mAquarium->SetHungerMessage(true);
		hungerMessage = true;
		AfxMessageBox(L"Fish are getting hungry!");
	}
	//Determine which background to use
	int bkgId;
	if (cleanTime > stage3cleanTime)
		bkgId = 3;
	else if (cleanTime > stage2cleanTime)
		bkgId = 2;
	else if (cleanTime > stage1cleanTime)
		bkgId = 1;
	else
		bkgId = 0;
	mCleanStage = bkgId;
	mAquarium->SetBkg(bkgId);
}

