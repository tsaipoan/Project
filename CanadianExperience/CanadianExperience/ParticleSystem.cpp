/**
* \file ParticleSystem.cpp
*
* \author Po-An Tsai
*/

#include "stdafx.h"
#include "ParticleSystem.h"
#include "Picture.h"

using namespace std;
using namespace Gdiplus;


CParticleSystem::~CParticleSystem()
{
}

/** \brief Create the snow in active list
*/
void CParticleSystem::CreateSnowFlake()
{
	mParticleNum = 10 + ((double)rand() / RAND_MAX) * (50 - 10);
	auto snow = mParticlePoolList.GetHead();
	int snowNum = 1;
	while (snow != nullptr && snowNum <= mParticleNum)
	{
		auto nextSnow = snow->GetNext();
		// Do something with node
		double minX = -300;
		//double minY = 0;
		//double maxY = mWindowSize.Height;
		double maxX = mWindowSize.Width;

		double maxSp = 40.0;
		double minSp = 10.0;
		double x = minX + ((double)rand() / RAND_MAX) * (maxX - minX);
		//double y = minY + ((double)rand() / RAND_MAX) * (maxY - minY);
		double deltaX = minSp + ((double)rand() / RAND_MAX) * (maxSp - minSp);
		double deltaY = minSp + ((double)rand() / RAND_MAX) * (maxSp - minSp);
		snow->SetPosition(PointF(x, 0));
		snow->SetDelta(deltaX, deltaY);

		mParticlePoolList.Remove(snow);
		mActiveParticleList.PushBack(snow);

		snow = nextSnow;

		snowNum++;
	}
}

/** \brief Clean the snow in active list
*/
void CParticleSystem::CleanSnowFlake()
{
	auto snow = mActiveParticleList.GetHead();
	while (snow != nullptr)
	{
		auto nextSnow = snow->GetNext();
		// Do something with node
		mActiveParticleList.Remove(snow);
		mParticlePoolList.PushBack(snow);

		snow = nextSnow;
	}
}

/** \brief Update the snow flake
* \param time The time elapsed
*/
void CParticleSystem::Update(double time)
{
	mTime = mTime + time;
	auto snow = mActiveParticleList.GetHead();
	while (snow != nullptr)
	{
		auto nextSnow = snow->GetNext();
		// Do something with node
		snow->Update(time);
		PointF pos = snow->GetPosition();
		if (pos.X > mWindowSize.Width || pos.Y > mWindowSize.Height)
		{
			mActiveParticleList.Remove(snow);
			mParticlePoolList.PushBack(snow);
		}

		snow = nextSnow;
	}
}

/** \brief Draw this system on a device context
* \param graphics The device context to draw on
* \param brush The brush to use
*/
void CParticleSystem::Draw(Gdiplus::Graphics *graphics, SolidBrush *brush)
{
	if (mTime >= 0.3)
	{
		CreateSnowFlake();
		mTime = 0;
	}
	auto node = mActiveParticleList.GetHead();
	while (node != nullptr)
	{
		// Do something with node
		node->Draw(graphics, brush);

		node = node->GetNext();
	}
}

