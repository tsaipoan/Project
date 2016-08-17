/**
* \file ParticlePoolList.h
*
* \author Po-An Tsai
*
* \brief Class that demonstrates a simple doubly-linked list
*/
#pragma once
#include "SnowFlakeList.h"

/**
* \brief Class that demonstrates a simple doubly-linked list
*/
class CParticlePoolList :
	public CSnowFlakeList
{
public:
	CParticlePoolList();
	virtual ~CParticlePoolList();
	/** \brief Copy constructor disabled */
	CParticlePoolList(const CParticlePoolList &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CParticlePoolList &) = delete;
};

