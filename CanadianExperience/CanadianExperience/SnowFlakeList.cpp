/**
* \file SnowFlakeList.cpp
*
* \author Po-An Tsai
*/

#include "stdafx.h"
#include "SnowFlakeList.h"



/**
* \brief Add a snow to the end of the linked list
* \param snow Snow to add
*/
void CSnowFlakeList::PushBack(std::shared_ptr<CSnowFlake> snow)
{
	if (mHead == nullptr)
	{
		// Empty list
		mHead = snow;
		mTail = snow;
	}
	else
	{
		snow->SetPrev(mTail);
		mTail->SetNext(snow);
		mTail = snow;
	}
}


/**
* \brief Add a snow to the beginning of the linked list
* \param snow Snow to add
*/
void CSnowFlakeList::PushFront(std::shared_ptr<CSnowFlake> snow)
{
	if (mHead == nullptr)
	{
		// Empty list
		mHead = snow;
		mTail = snow;
	}
	else
	{
		snow->SetNext(mHead);
		mHead->SetPrev(snow);
		mHead = snow;
	}
}


/**
* \brief Remove a snow from the linked list
* \param snow Snow to remove
*/
void CSnowFlakeList::Remove(std::shared_ptr<CSnowFlake> snow)
{
	// Fix previous pointers
	if (snow->GetPrev() == nullptr)
	{
		// Removing from head of list
		mHead = snow->GetNext();
	}
	else
	{
		// Removing from elsewhere  in the list
		snow->GetPrev()->SetNext(snow->GetNext());
	}

	// Fix next pointers
	if (snow->GetNext() == nullptr)
	{
		// Removing from end of list
		mTail = snow->GetPrev();
	}
	else
	{
		// Removing from elsewhere in the list
		snow->GetNext()->SetPrev(snow->GetPrev());
	}

	// Ensure head and tail point correctly
	if (mHead != nullptr)
	{
		mHead->SetPrev(nullptr);
		mTail->SetNext(nullptr);
	}

	// Ensure removed node points to nothing
	snow->SetPrev(nullptr);
	snow->SetNext(nullptr);
}

