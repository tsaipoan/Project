/**
* \file Floor.h
* \brief floor class to track the floor button is pressed or not.
*
*  \author Po-An Tsai
*/
#pragma once

class CController;
/** \brief floor class to track the floor button is pressed or not.
*/
class CFloor
{
public:
	CFloor();
	virtual ~CFloor();

	/** \brief Get the value of Up for a floor.
	* \returns Up value for mUp
	*/
	bool IsUp(){ return mUp; }

	void SetUp(bool up);

	/** \brief Get the value of Down for a floor.
	* \returns Down value for mDown
	*/
	bool IsDown(){ return mDown; }

	void SetDown(bool d);

	/** \brief Get the value of panel for a floor.
	* \returns Panel value for mPanel
	*/
	bool IsPanel(){ return mPanel; }

	void SetPanel(bool panel);

	/** \brief Get the value of the floor.
	* \returns Floor value for mFloor
	*/
	int GetFloor(){ return mFloor; }

	/** \brief Set the value of Floor for a floor.
	* \param floor The new value for mFloor
	*/
	void SetFloor(int floor) { mFloor = floor; }

	/** \brief Set controller class.
	* \param conrroller The controller class we are using
	*/
	void SetController(CController *conrroller) { mController = conrroller; }

private:
	bool mUp = false;		///< The up button is pressed or not
	bool mDown = false;		///< The down button is pressed or not
	bool mPanel = false;	///< The panel button is pressed or not
	int mFloor = 0;			///< The current floor

	CController *mController;   ///< Controller for this object
};

