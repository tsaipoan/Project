
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "Step2.h"
#include "ChildView.h"
#include "FishBeta.h"
#include "FishNemo.h"
#include "FishDory.h"
#include "FishCat.h"
#include "DecorTreasure.h"
#include "Predator.h"
#include "Prey.h"
#include "IsPredator.h"
#include "IsPrey.h"

/// Frame duration in milliseconds
const int FrameDuration = 30;
/// Value of fish
const int doryCost = -225; ///<cost of dory fish
const int nemoCost = -175; ///<cost of nemo fish
const int catCost = -75; ///<cost of catfish
const int betaCost = -100; ///<cost of beta fish
const int decorCost = -250; ///<cost of treasure chest
const double refundModifier = .5; ///<the amount of the original price you get back for deleting fish via trashcan

/// Initial fish X location
const int InitialX = 200;

/// Initial fish Y location
const int InitialY = 200;

#include <algorithm>

using namespace std;
using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

/** \brief Constructor */
CChildView::CChildView()
{
	srand((unsigned int)time(nullptr));
}

/** \brief Destrructor */
CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_ADDFISH_BETAFISH, &CChildView::OnAddfishBetafish)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_ADDFISH_NEMOFISH, &CChildView::OnAddfishNemofish)
	ON_COMMAND(ID_ADDFISH_DORYFISH, &CChildView::OnAddfishDoryfish)
	ON_COMMAND(ID_FILE_TRASHCAN, &CChildView::OnFileTrashcan)
	ON_COMMAND(ID_ADDDECOR_T, &CChildView::OnAdddecorT)
	ON_COMMAND(ID_FILE_SAVEAS, &CChildView::OnFileSaveas)
	ON_COMMAND(ID_FILE_OPEN32778, &CChildView::OnFileOpen)
	ON_WM_TIMER()
	ON_COMMAND(ID_ADDFISH_CATFISH, &CChildView::OnAddfishCatfish)
	ON_UPDATE_COMMAND_UI(ID_FILE_TRASHCAN, &CChildView::OnUpdateFileTrashcan)
	ON_COMMAND(ID_CARE_CLEANTANK, &CChildView::OnCareCleantank)
	ON_COMMAND(ID_CARE_FEEDFISH, &CChildView::OnCareFeedfish)
	ON_COMMAND(ID_HELP_INSTRUCTIONS, &CChildView::OnHelpInstructions)
END_MESSAGE_MAP()



// CChildView message handlers

/** \brief This function is called before the window is created.
 * \param cs A structure with the window creation parameters
 * \returns TRUE
 */
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

/** \brief This function is called to draw in the window.
 *
 * This function is called in response to a drawing message
 * whenever we need to redraw the window on the screen.
 * It is responsible for painting the window.
 */
void CChildView::OnPaint()
{
	if (mFirstDraw)
	{
		mFirstDraw = false;
		SetTimer(1, FrameDuration, nullptr);

		/*
		* Initialize the elapsed time system
		*/
		LARGE_INTEGER time, freq;
		QueryPerformanceCounter(&time);
		QueryPerformanceFrequency(&freq);

		mLastTime = time.QuadPart;
		mTimeFreq = double(freq.QuadPart);
	}
	/*
	* Compute the elapsed time since the last draw
	*/
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	long long diff = time.QuadPart - mLastTime;
	double elapsed = double(diff) / mTimeFreq;
	mLastTime = time.QuadPart;

	mAquarium.Update(elapsed);

	Invalidate();

	CPaintDC dc(this); // device context for painting

	// Get the size of the window
	CRect rect;
	GetClientRect(&rect);

	// Create a memory buffer
	Bitmap memory(rect.Width(), rect.Height(), PixelFormat32bppARGB);

	// And a graphics context for that buffer
	Graphics graphics(&memory);
	graphics.Clear(Color(0, 0, 0));

	mAquarium.OnDraw(&graphics, rect);

	Graphics graphicsReal(dc.m_hDC);
	graphicsReal.DrawImage(&memory, 0, 0, rect.Width(), rect.Height());

	CPredator visitor;
	mAquarium.Accept(&visitor);

	CPrey visitorPrey;
	mAquarium.Accept(&visitorPrey);

	mAquarium.EatFish();

}


/** \brief Add Fish/Beta menu option handler
 */
void CChildView::OnAddfishBetafish()
{
	if (mAquarium.AddScore(betaCost))
	{
		auto fish = make_shared<CFishBeta>(&mAquarium);
		fish->SetLocation(InitialX, InitialY);
		mAquarium.Add(fish);
		Invalidate();
	}
	else
	{
		AfxMessageBox(L"Not enough points to purchase this item!");
	}
}


/** \brief Called when there is a left mouse button press
 * \param nFlags Flags associated with the mouse button press
 * \param point Where the button was pressed
 */
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (mAquarium.IsNavigationActive())
	{
		mDragX = point.x;
		mDragY = point.y;
	}
	else
	{
		mGrabbedItem = mAquarium.HitTest(point.x, point.y);
		if (mGrabbedItem != nullptr)
		{
			// We have selected an item
			// Move it to the end of the list of items
			// you'll need code here to do that...
			mAquarium.MoveToFront(mGrabbedItem);
		}
		else if (mAquarium.IsOverTrashcan(point.x, point.y))
		{
			mAquarium.ToggleTrashCanActive();
		}
	}
	

}


/** \brief Called when the left mouse button is released
 * \param nFlags Flags associated with the mouse button release
 * \param point Where the button was pressed
 */
void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (mAquarium.IsOverTrashcan(point.x, point.y) && mGrabbedItem != nullptr)
	{
		CIsPredator predVisitor;
		CIsPrey preyVisitor;
		mGrabbedItem->Accept(&predVisitor);
		mGrabbedItem->Accept(&preyVisitor);
		if (predVisitor.IsDory())
		{
			mAquarium.AddScore(-doryCost*refundModifier);
		}
		else if (predVisitor.IsNemo())
		{
			mAquarium.AddScore(-nemoCost*refundModifier);
		}
		else if (preyVisitor.IsBeta())
		{
			mAquarium.AddScore(-betaCost*refundModifier);
		}
		else if (preyVisitor.IsCat())
		{
			mAquarium.AddScore(-catCost*refundModifier);
		}
		else
		{
			mAquarium.AddScore(-decorCost*refundModifier);
		}
		mAquarium.DeleteItem(mGrabbedItem);
	}
	OnMouseMove(nFlags, point);
	mAquarium.NavigationMode(point.x, point.y);
	

}


/** \brief Called when the mouse is moved
 * \param nFlags Flags associated with the mouse movement
 * \param point Where the button was pressed
 */
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (mAquarium.IsNavigationActive() && nFlags & MK_LBUTTON)
	{
		mAquarium.ScrolledBackground(mDragX - point.x, mDragY - point.y);
		mDragX = point.x;
		mDragY = point.y;
		
	}
	// See if an item is currently being moved by the mouse
	if (mGrabbedItem != nullptr)
	{
		// If an item is being moved, we only continue to 
		// move it while the left button is down.
		if (nFlags & MK_LBUTTON)
		{
			mGrabbedItem->SetLocation(point.x - mAquarium.GetDrawX(), point.y - mAquarium.GetDrawY());
			
		}
		else
		{
			// When the left button is released, we release the
			// item.

			mGrabbedItem = nullptr;
		}
		
		// Force the screen to redraw
		Invalidate();
	}
}

/**
 * \brief Erase the background prior to drawing.
 * \param pDC A device context to draw on
 * \returns TRUE
 */
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// This disabled the default background erase
	return TRUE;
}

/** \brief Add Fish/Nemo menu option handler
 */
void CChildView::OnAddfishNemofish()
{
	if (mAquarium.GetNumPredators() < mAquarium.GetNumPrey() / 2.0)
	{
		if (mAquarium.AddScore(nemoCost))
		{
			auto fish = make_shared<CFishNemo>(&mAquarium);
			fish->SetLocation(InitialX, InitialY);
			mAquarium.Add(fish);
			Invalidate();
		}
		else
		{
			AfxMessageBox(L"Not enough points to purchase this item!");
		}
	}
	else
		AfxMessageBox(L"Not enough prey!");
}

/** \brief Add Fish/Dory menu option handler
 */
void CChildView::OnAddfishDoryfish()
{
	if (mAquarium.GetNumPredators() < mAquarium.GetNumPrey() / 2.0)
	{
		if (mAquarium.AddScore(doryCost))
		{
			auto fish = make_shared<CFishDory>(&mAquarium);
			fish->SetLocation(InitialX, InitialY);
			mAquarium.Add(fish);
			Invalidate();
		}
		else
		{
			AfxMessageBox(L"Not enough points to purchase this item!");
		}
	}
	else
		AfxMessageBox(L"Not enough prey!");
}

/** \brief Add Fish/Catfish menu option handler
 */
void CChildView::OnAddfishCatfish()
{
	if (mAquarium.AddScore(catCost))
	{
		auto fish = make_shared<CFishCat>(&mAquarium);
		fish->SetLocation(InitialX, InitialY);
		mAquarium.Add(fish);
		Invalidate();

	}
	else
	{
		AfxMessageBox(L"Not enough points to purchase this item!");
	}
}


/** \brief Add Trash Can menu option handler
 */
void CChildView::OnFileTrashcan()
{
	mAquarium.ToggleTrashCanActive();
	Invalidate();
	
}

/** \brief Add DecorTreasure menu option handler
*/
void CChildView::OnAdddecorT()
{
	if (mAquarium.AddScore(decorCost))
	{
		auto decor = make_shared<CDecorTreasure>(&mAquarium);
		decor->SetLocation(InitialX, InitialY);
		mAquarium.Add(decor);
		Invalidate();
	}
	else
	{
		AfxMessageBox(L"Not enough points to purchase this item!");
	}
}


/**
* \brief Handler for the File/Save As menu option
*/
void CChildView::OnFileSaveas()
{
	CFileDialog dlg(false,  // false = Save dialog box
		L".aqua",           // Default file extension
		nullptr,            // Default file name (none)
		0,                  // Flags (none)
		L"Aquarium Files (*.aqua)|*.aqua|All Files (*.*)|*.*||");    // Filter          // 
	if (dlg.DoModal() != IDOK)
		return;

	wstring filename = dlg.GetPathName();

	mAquarium.Save(filename);
}


/** This function is called when an File Open menu item is selected.
*
* It loads the aquarium from a file.
*
*/
void CChildView::OnFileOpen()
{
	CFileDialog dlg(true,  // true = Open dialog box
		L".aqua",           // Default file extension
		nullptr,            // Default file name (none)
		0,    // Flags
		L"Aquarium Files (*.aqua)|*.aqua|All Files (*.*)|*.*||");    // Filter
	if (dlg.DoModal() != IDOK)
		return;

	wstring filename = dlg.GetPathName();

	mAquarium.Load(filename);
	Invalidate();
}

/**
* \brief Handle timer events
* \param nIDEvent The timer event ID
*/
void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	Invalidate();
	CWnd::OnTimer(nIDEvent);
}


/**
* \brief Handles updating trash can check mark
* \param pCmdUI The UI
*/
void CChildView::OnUpdateFileTrashcan(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mAquarium.IsTrashcanActive());
}


/**
 * \brief File menu handler for Care>Clean Tank
 */
void CChildView::OnCareCleantank()
{
	mAquarium.ResetCleanTime();
}


/**
 * \brief File menu handler for Care>Feed Fish
 */
void CChildView::OnCareFeedfish()
{
	mAquarium.ResetFoodTime();
	mAquarium.SetHungerMessage(false);
	mAquarium.SetHungerDyingMessage(false);
}

/**
* \brief File menu handler for Help Instructions
*/
void CChildView::OnHelpInstructions()
{
	AfxMessageBox(L"Moving Around\n To move around, first check the bottom right corner of the screen. \
This is the navigation indicator.When the finger has a yellow aura, you can click on \
the empty aquarium to drag your view around. When there is no aura, you can click and \
drag the fish around. To toggle the navigation / fish mode, just click this icon.\n\n \
Fish\n To spawn fish, click the menu option Add Fish>Add(fish type). Different fish have \
different behaviors.Some are predators and others are prey.The predators chase the prey, \
and the prey try to escape the predators. Buying fish costs points. Each prey fish you have generates \
points and predator fish act as a multiplier for points earned from prey fish. You may get a 50% refund \
if you delete the fish using the trashcan in the file menu. However if a prey fish is eaten by a \
predator fish, you will get no points back. \n\n Fish Care\n Your aquarium will get dirty as time \
goes on. Clean it often or the dirt builds up and you will not gain points as fast. Your fish will also\
require feeding on a regular basis or they will start to die off. If a fish dies of hunger, you will get\
a small point penalty. \n\n Winning and Losing\n You 'win' the game when the time remaining reaches 0. \
You will lose if all your fish die before time runs out. The object is to get as many points as \
possible before winning or losing.");
}
