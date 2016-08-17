/**
 * \file Environment.h
 *
 * \author Zoe Hayes, Joseph Hollopter, Po-An Tsai
 *
 * \brief Environment for the aquarium - Cleaning and Feeding
 */

#pragma once

#include <memory>

/// Forward declaration
class CAquarium;

/**
 * \brief Environment for the aquarium - Cleaning and Feeding
 */
class CEnvironment
{
public:
	CEnvironment() = delete;
	/// Constructor
	CEnvironment(CAquarium *aquarium);
	/// Destructor
	virtual ~CEnvironment();

	/// Updates the environment
	void Update(double cleanTime, double foodTime, bool hungerMessage, bool hungerDyingMessage);

	/**
	* \brief Gets the cleanliness stage of the tank
	* \returns 0,1,2,3 are the different stages
	*/
	int GetCleanStage() { return mCleanStage; }

private:
	/// Aquarium it belongs to
	CAquarium *mAquarium;
	/// The stage of cleanliness of the aquarium
	int mCleanStage = 0;
};

