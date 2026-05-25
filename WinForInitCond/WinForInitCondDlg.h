// WinForInitCondDlg.h : header file
//

#if !defined(AFX_WINFORINITCONDDLG_H__064615A5_E2AA_11D6_A1F1_0001021C09FA__INCLUDED_)
#define AFX_WINFORINITCONDDLG_H__064615A5_E2AA_11D6_A1F1_0001021C09FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWinForInitCondDlg dialog

class CWinForInitCondDlg : public CDialog
{
// Construction
public:
	CWinForInitCondDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWinForInitCondDlg)
	enum { IDD = IDD_WINFORINITCOND_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinForInitCondDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWinForInitCondDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnIntegrate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINFORINITCONDDLG_H__064615A5_E2AA_11D6_A1F1_0001021C09FA__INCLUDED_)
