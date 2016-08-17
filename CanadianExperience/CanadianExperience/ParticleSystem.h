/**
* \file ParticleSystem.h
*
* \author Po-An Tsai
*
* \brief The system to control the snow
*/
#pragma once
#include "ParticlePoolList.h"
#include "ActiveParticleList.h"


class CPicture;


/**
* \brief The system to control the snow
*/
class CParticleSystem
{
public:
	virtual ~CParticleSystem();
	/** \brief Default constructor */
	CParticleSystem(){}
	/** \brief Copy constructor disabled */
	CParticleSystem(const CParticleSystem &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CParticleSystem &) = delete;

	void CreateSnowFlake();

	void CleanSnowFlake();

	void Update(double time);

	void Draw(Gdiplus::Graphics *graphics, Gdiplus::SolidBrush *brush);

	/** \brief Set the window size to draw on
	* \param size The size to use
	*/
	void SetWindowSize(Gdiplus::Size size) { mWindowSize = size; }
	
private:
	int mParticleNum;  ///< num of Particle to add

	double mTime = 0;  ///< count on elapsed time

	/// The picture size
	Gdiplus::Size mWindowSize;

	CActiveParticleList mActiveParticleList; ///< The active list
	CParticlePoolList mParticlePoolList;  ///< The not active list



};

