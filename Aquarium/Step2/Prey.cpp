/** \ Prey.cpp
 *
 *  Authors: Po-An, Zoe, Joseph
*/
#include "stdafx.h"
#include "Prey.h"
#include "IsPredator.h"
#include "FishBeta.h"
#include "FishCat.h"
#include "Aquarium.h"

/// \brief Construtor
CPrey::CPrey()
{
}

/// \brief Deconstuctor
CPrey::~CPrey()
{
}

/**
* \brief Visits cat fish
* \param cat CFishCat visit in
*/
void CPrey::VisitCat(CFishCat *cat)
{
	/// x and y of prey
	double PreyX = cat->GetX();
	double PreyY = cat->GetY();

	/// predator X and Y
	double predatorX;
	double predatorY;

	/// this is the change in x and y -- becames the speed mod for fish
	double dx;
	double dy;

	/// default length, then after predator found - gets closest predator length
	double len = INFINITY;

	/// is predator found
	bool find = false;

	/// predator item to get the x and y of each predator item gotten from CIsPredator
	std::shared_ptr<CItem> predator;

	/// loop through items in Aquarium
	for (auto item : cat->GetAquarium()->GetItems())
	{
		CIsPredator visitor;
		item->Accept(&visitor);
		if (visitor.IsPredator())
		{
			predatorX = item->GetX();
			predatorY = item->GetY();
			double preX = PreyX - predatorX;
			double preY = PreyY - predatorY;
			if (sqrt(preX * preX + preY * preY) < len)
			{
				dx = PreyX - predatorX;
				dy = PreyY - predatorY;
				len = sqrt(dx * dx + dy * dy);
				double angle = atan2(dy, dx);
				dx = cos(angle);
				dy = sin(angle);

				auto predator = item;
				find = true;
			}
		}
	}
	if (!find)
	{
		dx = 0;
		dy = 0;
	}
	if (cat->GetY() <= cat->GetHeight() / 2)
	{
		dy = -dy;
	}
	if (cat->GetX() <= cat->GetWidth() / 2)
	{
		dx = -dx;
	}
	if (find&& cat->GetY() <= (cat->GetAquarium()->GetHeight() - 200) && cat->GetX()
		<= (cat->GetAquarium()->GetWidth() - 200)
		&& cat->GetY() > 200 && cat->GetX() > 200)
	{
		cat->FishBehave(dx * 100, dx * 100, dy * 100, dy * 100);
	}
	if (find && (cat->GetY() == 100 || cat->GetY() == (cat->GetAquarium()->GetHeight() - 100) ||
		cat->GetX() == (cat->GetAquarium()->GetWidth() - 100)
		|| cat->GetX() == 100))
	{
		cat->FishBehave(dx * 100, dx * 100, dy * 100, dy * 100);
	}
}

/**
* \brief Visits beta fish
* \param beta CFishBeta visit in
*/
void CPrey::VisitBeta(CFishBeta *beta)
{
	/// x and y of prey
	double PreyX = beta->GetX();
	double PreyY = beta->GetY();

	/// predator X and Y
	double predatorX;
	double predatorY;

	/// this is the change in x and y -- becames the speed mod for fish
	double dx;
	double dy;

	/// default length, then after predator found - gets closest predator length
	double len = INFINITY;

	/// is predator found
	bool find = false;

	/// predator item to get the x and y of each predator item gotten from CIsPredator
	std::shared_ptr<CItem> predator;

	/// loop through items in Aquarium
	for (auto item : beta->GetAquarium()->GetItems())
	{
		CIsPredator visitor;
		item->Accept(&visitor);
		if (visitor.IsPredator())
		{
			predatorX = item->GetX();
			predatorY = item->GetY();
			double preX = PreyX - predatorX;
			double preY = PreyY - predatorY;
			if (sqrt(preX * preX + preY * preY) < len)
			{
				dx = PreyX - predatorX;
				dy = PreyY - predatorY;
				len = sqrt(dx * dx + dy * dy);
				double angle = atan2(dy, dx);
				dx = cos(angle);
				dy = sin(angle);

				auto predator = item;
				find = true;
			}
		}
	}
	if (!find)
	{
		dx = 0;
		dy = 0;
	}
	if (beta->GetY() <= beta->GetHeight() / 2)
	{
		dy = -dy;
	}
	if (beta->GetX() <= beta->GetWidth() / 2)
	{
		dx = -dx;
	}
	if (find&& beta->GetY() <= (beta->GetAquarium()->GetHeight() - 200) && beta->GetX() 
		<= (beta->GetAquarium()->GetWidth() - 200)
		&& beta->GetY() > 200 && beta->GetX() > 200)
	{
		beta->FishBehave(dx * 100, dx * 100, dy * 100, dy * 100);
	}
	if (find && (beta->GetY() == 100 || beta->GetY() == (beta->GetAquarium()->GetHeight() - 100) ||
		beta->GetX() == (beta->GetAquarium()->GetWidth() - 100)
		|| beta->GetX() == 100))
	{
		beta->FishBehave(dx * 100, dx * 100, dy * 100, dy * 100);
	}
}