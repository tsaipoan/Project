#include "stdafx.h"
#include "CppUnitTest.h"
#include "ElevatorWnd.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Testing
{
	/** \brief Mock controller class.
	*/
    class CMockController : public CElevatorController
    {
    public:
		/** \brief This function is called to set the mInitialized to true.
		*/
        virtual void Initialize() override { mInitialized = true; }

		/** \brief This function is called to set mOpenPressed to true.
		*/
        virtual void OnOpenPressed() override { mOpenPressed = true; }

        bool mInitialized = false; ///< The current Initialize
        bool mOpenPressed = false; ///< The current OpenPressed
    };


	TEST_CLASS(CElevatorControllerTest)
	{
	public:
        BEGIN_TEST_METHOD_ATTRIBUTE(TestCElevatorWndSetController)
            TEST_TRAIT(L"ElevatorLib")
        END_TEST_METHOD_ATTRIBUTE()

        TEST_METHOD(TestCElevatorWndSetController)
        {
            // Create a test object
            CElevatorWnd elevator;

            // Create a mock controller and install it
            auto controller = make_shared<CMockController>();

            elevator.SetController(controller);

            Assert::IsTrue(controller->GetElevator() == &elevator);
            Assert::IsTrue(controller->mInitialized);
        }

        BEGIN_TEST_METHOD_ATTRIBUTE(TestCElevatorWndOnOpenPressed)
            TEST_TRAIT(L"ElevatorLib")
        END_TEST_METHOD_ATTRIBUTE()

        TEST_METHOD(TestCElevatorWndOnOpenPressed)
        {
            // Create a test object
            CElevatorWnd elevator;

            // Create a mock controller and install it
            auto controller = make_shared<CMockController>();

            elevator.SetController(controller);

            elevator.PressOpen();
            Assert::IsTrue(controller->mOpenPressed);
        }

	};
}