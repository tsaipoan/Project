/**
* \file ParticlePoolList.cpp
*
* \author Po-An Tsai
*/
#include "stdafx.h"
#include "ParticlePoolList.h"


using namespace std;
using namespace Gdiplus;

/** \brief constructor */
CParticlePoolList::CParticlePoolList()
{
	for (int i = 1; i <= 1500; i++)
	{
		auto node1 = make_shared<CSnowFlake>(PointF(0, 0), 0, 0);
		PushBack(node1);
	}
}

/** \brief Destructor */
CParticlePoolList::~CParticlePoolList()
{
}
