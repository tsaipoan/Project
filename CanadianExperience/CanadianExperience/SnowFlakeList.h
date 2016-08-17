/**
* \file SnowFlakeList.h
*
* \author Po-An Tsai
*
* \brief Class that demonstrates a simple doubly-linked list
*/

#pragma once

#include "SnowFlake.h"


/**
* \brief Class that demonstrates a simple doubly-linked list
*/
class CSnowFlakeList
{
public:
	/// \brief Constructor
	CSnowFlakeList() {}
	/// \brief Destructor
	virtual ~CSnowFlakeList() {}

	/** \brief Copy constructor disabled */
	CSnowFlakeList(const CSnowFlakeList &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CSnowFlakeList &) = delete;

	/** \brief Iterator that iterates over the list */
	class SnowIter
	{
	public:
		/** \brief Constructor
		* \param pos The position we are going over
		*/
		SnowIter(std::shared_ptr<CSnowFlake> pos) : mPos(pos)
		{
		}

		/** \brief Test for end of the iterator
		* \param iter The end we are using
		* \returns True if we this position equals not equal to the other position */
		bool operator!= (const SnowIter &iter) const { return mPos != iter.mPos; }

		/** \brief Get value at current position
		* \returns Value at mPos in the collection */
		std::shared_ptr<CSnowFlake>  operator* () const { return mPos; }

		/** \brief Increment the iterator
		* \returns Reference to this iterator */
		const SnowIter& operator++ ()
		{
			mPos = mPos->GetNext();
			return *this;
		}

	private:
		std::shared_ptr<CSnowFlake> mPos;        ///< Current position in linked list
	};

	/** \brief Get an iterator for the beginning of the list
	* \returns Iter object at position head */
	SnowIter begin() const { return SnowIter(mHead); }

	/** \brief Get an iterator for the end of the list
	* \returns Iter object at position past the end */
	SnowIter end() const { return SnowIter(nullptr); }

	void PushBack(std::shared_ptr<CSnowFlake> snow);
	void PushFront(std::shared_ptr<CSnowFlake> snow);
	void Remove(std::shared_ptr<CSnowFlake> snow);

	/** \brief The Head
	* \returns Head */
	std::shared_ptr<CSnowFlake> GetHead() { return mHead; }

private:
	std::shared_ptr<CSnowFlake> mHead;   ///< Head of the list
	std::shared_ptr<CSnowFlake> mTail;   ///< Tail of the list
};

