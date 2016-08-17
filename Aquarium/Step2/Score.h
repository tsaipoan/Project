/**
 * \file Score.h
 *
 * \author Zoe Hayes
 *
 * \brief Score class to keep score of the aquarium game
 */

#pragma once

/// Forward Declaration
class CAquarium;

/**
 * \brief Score class to keep score of the aquarium game
 */
class CScore
{
public:
	/// Default constructor - deleted
	CScore() = delete;

	/// Constructor
	CScore(CAquarium *aquarium) : mAquarium(aquarium) {}

	/// Destructor
	virtual ~CScore();

	/// Updates the score
	void Update(double elapsed);

	/** 
	* \brief gets the score
	* \returns the score
	*/
	double GetScore() { return mScore; }

	/**
	* \brief Adds to score (negative values passed will subtract from score)
	* \param num The value to add/subtract
	* \returns true if operation is successful (points wont go into negative)
	*/
	bool AddScore(double num);

	/**
	* \brief Get the time remaining in the game
	* \returns the time remaining
	*/
	double GetTimeRemaining();

	/**
	* \brief Get the points/sec
	* \returns the points/sec
	*/
	double GetPointsSec() { return mPointsSec; }

private:
	/// Score - start with 500 for buying fish
	double mScore = 200;

	/// Aquarium it belongs to
	CAquarium *mAquarium;

	/// if game has started
	bool mStart = false;

	/// if game ends
	bool mEnd = false;

	/// total time elapsed
	double mTime = 0;

	/// points/sec
	double mPointsSec = 0;
};

