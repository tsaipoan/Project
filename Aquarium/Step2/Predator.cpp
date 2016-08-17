/** \ Predator.cpp
*
*  Authors: Po-An, Zoe, Joseph
*/
#include "stdafx.h"
#include "Predator.h"
#include "IsPrey.h"
#include "FishDory.h"
#include "FishNemo.h"
#include "Aquarium.h"

CPredator::CPredator()
{
}


CPredator::~CPredator()
{
}


void CPredator::VisitDory(CFishDory *dory)
{
	
	GetDoryTarget(dory, true);
}


void CPredator::VisitNemo(CFishNemo *nemo)
{
	GetNemoTarget(nemo, true);
	
}

/**
 * \brief Get predator a target to chace and eat on
 * \param nemo Predator we are using
 * \param isnemo bool that we use to check is nemo or not
 */
void CPredator::GetNemoTarget(CFish *nemo, bool isnemo)
{
	double nemoX = nemo->GetX();
	double nemoY = nemo->GetY();
	double preyX;
	double preyY;
	double dx;
	double dy;
	double len = INFINITY;
	bool find = false;
	std::shared_ptr<CItem> prey;

	for (auto item : nemo->GetAquarium()->GetItems())
	{
		CIsPrey visitor;
		item->Accept(&visitor);
		if (visitor.IsCat())
		{
			preyX = item->GetX();
			preyY = item->GetY();
			double preX = preyX - nemoX;
			double preY = preyY - nemoY;
			if (sqrt(preX * preX + preY * preY) < len)
			{
				dx = preyX - nemoX;
				dy = preyY - nemoY;
				len = sqrt(dx * dx + dy * dy);
				if (isnemo)
				{
					while ((abs(dx) > 200 || abs(dy) > 200))
					{
						dx = dx * 0.9;
						dy = dy *0.9;
					}
				}
				else
				{
					while ((abs(dx) > 100 || abs(dy) > 100))
					{
						dx = dx * 0.9;
						dy = dy *0.9;
					}
				}

				prey = item;
				find = true;
			}
		}
	}

	if (find)
	{
		nemo->FishBehave(dx, dx, dy, dy);
		if (nemo->HitTest(prey->GetX(), prey->GetY(), 0, 0))
		{
			nemo->GetAquarium()->AddEatFish(prey);
		}


	}
	else if (isnemo)
	{
		GetDoryTarget(nemo, false);
	}
}

/**
 * \brief Get predator a target to chace and eat on
 * \param dory Predator we are using
 * \param isdory bool that we use to check is dory or not
 */
void CPredator::GetDoryTarget(CFish *dory, bool isdory)
{
	double doryX = dory->GetX();
	double doryY = dory->GetY();
	double preyX;
	double preyY;
	double dx;
	double dy;
	double len = INFINITY;
	bool find = false;
	std::shared_ptr<CItem> prey;

	for (auto item : dory->GetAquarium()->GetItems())
	{
		CIsPrey visitor;
		item->Accept(&visitor);
		if (visitor.IsBeta())
		{
			preyX = item->GetX();
			preyY = item->GetY();
			double preX = preyX - doryX;
			double preY = preyY - doryY;
			if (sqrt(preX * preX + preY * preY) < len)
			{
				dx = preyX - doryX;
				dy = preyY - doryY;
				len = sqrt(dx * dx + dy * dy);
				if (isdory)
				{
					while ((abs(dx) > 100 || abs(dy) > 100))
					{
						dx = dx * 0.9;
						dy = dy *0.9;
					}
				}
				else
				{
					while ((abs(dx) > 200 || abs(dy) > 200))
					{
						dx = dx * 0.9;
						dy = dy *0.9;
					}
				}

				prey = item;
				find = true;
			}
		}
	}

	if (find)
	{
		dory->FishBehave(dx, dx, dy, dy);
		if (dory->HitTest(prey->GetX(), prey->GetY(), 0, 0))
		{
			dory->GetAquarium()->AddEatFish(prey);
		}


	}
	else if (isdory)
	{
		GetNemoTarget(dory, false);
	}
}

