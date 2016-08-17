/**
* \file SnowFlake.h
*
* \author Po-An Tsai
*
* \brief Class for a simple doubly-linked list SnowFlake
*/

#pragma once

#include <memory>

/**
* \brief Class for a simple doubly-linked list SnowFlake
*/
class CSnowFlake
{
public:
	CSnowFlake(Gdiplus::PointF position, double deltaX, double deltaY);
	virtual ~CSnowFlake();

	/** \brief Default constructor disabled */
	CSnowFlake() = delete;
	/** \brief Copy constructor disabled */
	CSnowFlake(const CSnowFlake &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CSnowFlake &) = delete;

	/** \brief Set the next SnowFlake to point at
	* \param next The next SnowFlake
	*/
	void SetNext(std::shared_ptr<CSnowFlake> next) { mNext = next; }

	/** \brief The next SnowFlake
	* \returns Next */
	std::shared_ptr<CSnowFlake> GetNext() { return mNext; }

	/** \brief Set the previous SnowFlake to point at
	* \param prev The previous SnowFlake
	*/
	void SetPrev(std::shared_ptr<CSnowFlake> prev) { mPrev = prev; }

	/** \brief The previous SnowFlake
	* \returns Prev */
	std::shared_ptr<CSnowFlake> GetPrev() { return mPrev.lock(); }

	void Draw(Gdiplus::Graphics *graphics, Gdiplus::SolidBrush *brush);

	void Update(double time);

	/** \brief The at end or not
	* \returns false */
	bool AtEnd(){ return false; }

	/** \brief The position
	* \returns Position */
	Gdiplus::PointF GetPosition(){ return mPosition; }

	/** \brief Set the SnowFlake position
	* \param pos The new position
	*/
	void SetPosition(Gdiplus::PointF pos){ mPosition = pos; }
	
	/** \brief Set the SnowFlake velocity
	* \param x The x velocity
	* \param y The y velocity
	*/
	void SetDelta(double x, double y){ mDeltaX = x; mDeltaY = y; }
private:
	Gdiplus::PointF mPosition;  ///< The position of the snow

	double mDeltaX;  ///< The velocity in x direction

	double mDeltaY;  ///< The velocity in y direction
	

	std::shared_ptr<CSnowFlake> mNext;   ///< Previous node
	std::weak_ptr<CSnowFlake> mPrev;     ///< Next node
};

