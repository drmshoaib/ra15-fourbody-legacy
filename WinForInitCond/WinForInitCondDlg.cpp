// WinForInitCondDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WinForInitCond.h"
#include "WinForInitCondDlg.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

__declspec(dllimport) int fnMy4BodyIntegrator(double *X, double *V, double T, double *M);


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

double CalcEnergy(double *X,double *V, double *M);

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinForInitCondDlg dialog

CWinForInitCondDlg::CWinForInitCondDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWinForInitCondDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWinForInitCondDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinForInitCondDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWinForInitCondDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWinForInitCondDlg, CDialog)
	//{{AFX_MSG_MAP(CWinForInitCondDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnIntegrate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinForInitCondDlg message handlers

BOOL CWinForInitCondDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWinForInitCondDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWinForInitCondDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWinForInitCondDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWinForInitCondDlg::OnIntegrate() 
{
	// TODO: Add your control notification handler code here
	
	int i;

	double X[10], V[10], M[9], T;
	FILE *out;

	CProgressCtrl myctrl;
	int nLower, nUpper,progi;

	myctrl.Create(WS_CHILD|WS_VISIBLE|PBS_SMOOTH, CRect(1,1,300,30), 
			 this,IDC_PROGRESS);

	myctrl.SetRange( 0, 1000 );
	myctrl.GetRange( nLower, nUpper );
	myctrl.SetStep( (nUpper-nLower)/100 );
	


	double timestep,time=0,E0;

	CString buf;
	int idcname;
	
	idcname = IDC_EDIT1;

	for(i=idcname;i<=idcname+8;i++)
	{	
		GetDlgItemText(i,buf);
		X[i-idcname] = atof(buf);
		GetDlgItemText(i+8,buf);
		V[i-idcname] = atof(buf);
	}




	GetDlgItemText(IDC_TIME,buf);
	T = atof(buf);

	idcname = IDC_EDIT18;

	for(i=idcname;i<=idcname+4;i++)
	{	
		GetDlgItemText(i,buf);
		M[i-idcname] = atof(buf);
	}

	timestep = T/1000.0;

	GetDlgItemText(IDC_STEPSIZE,buf);
	timestep = atof(buf);


	out = fopen("result.txt","wt");

	E0 = CalcEnergy(X,V,M);

	progi = (int)(T/timestep)/100;

//	fprintf(out,"Time x1 y1 x2 y2 x3 y3 x4 y4 \n");

	for(i=0;i<T/timestep;i++)
	{
		if( fabs((CalcEnergy(X,V,M)-E0)/E0) > 0.01)
		{
			AfxMessageBox("Energy conservation fails!!!!");
			fprintf(out,"The energy conservation fails!");
			fclose(out);
			return;
		}
		fprintf(out,"%f %f %f %f %f %f %f %f %f \n", time, X[0], 
			X[1], X[2], X[3], X[4], X[5], X[6], X[7] );

		fnMy4BodyIntegrator(X, V, timestep, M);

		if(fmod(i,progi) == 0)
			myctrl.StepIt();

		time=time+timestep;
	}

	fclose(out);


}

double CalcEnergy(double *x, double *v, double *m)
{
double U, K;

	U = m[0]*m[1]/sqrt((x[0] - x[2])*(x[0] - x[2]) + (x[1] - x[3])*(x[1] - x[3])) +
		m[0]*m[2]/sqrt((x[0] - x[4])*(x[0] - x[4]) + (x[1] - x[5])*(x[1] - x[5])) +
		m[0]*m[3]/sqrt((x[0] - x[6])*(x[0] - x[6]) + (x[1] - x[7])*(x[1] - x[7])) +
		m[1]*m[2]/sqrt((x[2] - x[4])*(x[2] - x[4]) + (x[3] - x[5])*(x[3] - x[5])) +
		m[1]*m[3]/sqrt((x[2] - x[6])*(x[2] - x[6]) + (x[3] - x[7])*(x[3] - x[7])) +
		m[2]*m[3]/sqrt((x[4] - x[6])*(x[4] - x[6]) + (x[5] - x[7])*(x[5] - x[7]));

	K = 0.5*m[0]*(v[0]*v[0]+v[1]*v[1]) +
		0.5*m[1]*(v[2]*v[2]+v[3]*v[3]) +
		0.5*m[2]*(v[4]*v[4]+v[5]*v[5]) +
		0.5*m[3]*(v[6]*v[6]+v[7]*v[7]);
		
	return K - U; 
}
