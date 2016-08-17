/**
* \file ActiveParticleList.h
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
class CActiveParticleList :
	public CSnowFlakeList
{
public:
	CActiveParticleList();
	virtual ~CActiveParticleList();
	/** \brief Copy constructor disabled */
	CActiveParticleList(const CActiveParticleList &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CActiveParticleList &) = delete;
};

