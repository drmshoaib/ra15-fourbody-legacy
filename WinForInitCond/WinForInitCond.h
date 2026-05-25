// WinForInitCond.h : main header file for the WINFORINITCOND application
//

#if !defined(AFX_WINFORINITCOND_H__064615A3_E2AA_11D6_A1F1_0001021C09FA__INCLUDED_)
#define AFX_WINFORINITCOND_H__064615A3_E2AA_11D6_A1F1_0001021C09FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWinForInitCondApp:
// See WinForInitCond.cpp for the implementation of this class
//

class CWinForInitCondApp : public CWinApp
{
public:
	CWinForInitCondApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinForInitCondApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWinForInitCondApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINFORINITCOND_H__064615A3_E2AA_11D6_A1F1_0001021C09FA__INCLUDED_)
