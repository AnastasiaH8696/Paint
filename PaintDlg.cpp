
// PaintDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Paint.h"
#include "PaintDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPaintDlg dialog
CPaintDlg::CPaintDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PAINT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//TODO: Use the actual size of the board
	penStyle = PS_SOLID;
	rect.SetRect(0, 180, 1500, 800);
	dragIndex = -1;
	
}

void CPaintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, fillOption, colorOfTheShape);
	DDX_Control(pDX, brushOption, colorOfTheBorder);
}

BEGIN_MESSAGE_MAP(CPaintDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(RECTANGLE, &CPaintDlg::OnBnClickedRectangle)
	ON_BN_CLICKED(ELLIPSE, &CPaintDlg::OnBnClickedEllipse)
	ON_BN_CLICKED(TRIANGLE, &CPaintDlg::OnBnClickedTriangle)
	ON_BN_CLICKED(LINE, &CPaintDlg::OnBnClickedLine)
	ON_BN_CLICKED(MAGENDAVID, &CPaintDlg::OnBnClickedMagendavid)
	ON_BN_CLICKED(SOLID, &CPaintDlg::OnBnClickedSolid)
	ON_BN_CLICKED(DASH, &CPaintDlg::OnBnClickedDash)
	ON_BN_CLICKED(DOTS, &CPaintDlg::OnBnClickedDots)
	ON_BN_CLICKED(DASHDOT, &CPaintDlg::OnBnClickedDashdot)
	ON_BN_CLICKED(SMALL, &CPaintDlg::OnBnClickedSmall)
	ON_BN_CLICKED(MEDIUM, &CPaintDlg::OnBnClickedMedium)
	ON_BN_CLICKED(BIG, &CPaintDlg::OnBnClickedBig)
	ON_BN_CLICKED(SAVE, &CPaintDlg::OnBnClickedSave)
	ON_BN_CLICKED(LOAD, &CPaintDlg::OnBnClickedLoad)
	ON_BN_CLICKED(CLEAN, &CPaintDlg::OnBnClickedClean)
	ON_BN_CLICKED(DRAG, &CPaintDlg::OnBnClickedDrag)
	ON_BN_CLICKED(CHANGECOLOR, &CPaintDlg::OnBnClickedChangecolor)
	ON_BN_CLICKED(DELETEFIG, &CPaintDlg::OnBnClickedDeletefig)
	ON_BN_CLICKED(UNDO, &CPaintDlg::OnBnClickedUndo)
END_MESSAGE_MAP()


// CPaintDlg message handlers

BOOL CPaintDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Initialization
	CheckRadioButton(RECTANGLE, ELLIPSE, RECTANGLE);
	m_solidCheckBox = (CButton*)GetDlgItem(SOLID);
	m_dashCheckBox = (CButton*)GetDlgItem(DASH);
	m_dotsCheckBox = (CButton*)GetDlgItem(DOTS);
	m_dashDotsCheckBox = (CButton*)GetDlgItem(DASHDOT);
	m_smallCheckBox = (CButton*)GetDlgItem(SMALL);
	m_mediumCheckBox = (CButton*)GetDlgItem(MEDIUM);
	m_bigCheckBox = (CButton*)GetDlgItem(BIG);
	m_solidCheckBox->SetCheck(SOLID);
	m_smallCheckBox->SetCheck(SMALL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPaintDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CPaintDC dc(this); // device context for painting

		dc.Rectangle(0, 180, 1500, 800); // white rectangle for paint
		CBrush border(RGB(255, 255, 255));

		for (int i = 0; i < figs.GetSize(); i++)
		{
			figs[i]->MyDraw(dc);
		}
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPaintDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPaintDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	start = point;
	startDrag = point;
	isPressed = true;
	switch (futureFigureKind)
	{
	case 1:
		figs.Add(new FRectangle(start, start));
		break;
	case 2:
		figs.Add(new FEllipse(start, start));
		break;
	case 3:
		figs.Add(new FTriangle(start, start));
		break;
	case 4:
		figs.Add(new FLine(start, start));
		break;
	case 5:
		figs.Add(new FDStar(start, start));
		break;
	}

	if (isDragged)
	{
		dragIndex = -1;
		for (int i = 0; i < figs.GetSize() - 1; i++)
		{
			if (figs[i]->isInside(point) == true)
			{
				dragIndex = i;
			}
		}
	}

	if (colorMode)//If we want to change the design of the shape
	{
		ColoringShape(point);
		CButton* colorModeButton = (CButton*)GetDlgItem(CHANGECOLOR);
		colorModeButton->EnableWindow(true);
	}		

	if (deleteMode)
	{
		deleteShape(point);
		CButton* deleteFig = (CButton*)GetDlgItem(DELETEFIG);
		deleteFig->EnableWindow(true);
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CPaintDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	if (isPressed)
	{
		end = point;
		isPressed = false;
		if(!isDragged)
			figs[figs.GetSize() - 1]->Redefine(start, end);
		else
		{
			isDragged = false;
			dragIndex = -1;
			CButton* drag = (CButton*)GetDlgItem(DRAG);
			drag->EnableWindow(true);
		}
		InvalidateRect(rect); //simulates the WM_PAINT message to redraw window
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CPaintDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (isPressed)
	{
		end = point;
		if (isDragged)
		{
			CPoint c = figs[dragIndex]->getP1();
			figs[dragIndex]->onMove(point, c);
			InvalidateRect(rect);
		}
		else
		{
			figs[figs.GetSize() - 1]->Redefine(start, end);
			figs[figs.GetSize() - 1]->setBrushColor(colorOfTheBorder.GetColor());
			figs[figs.GetSize() - 1]->setFillColor(colorOfTheShape.GetColor());
			figs[figs.GetSize() - 1]->setPenStyle(penStyle);
			figs[figs.GetSize() - 1]->setPenSize(penSize);
			InvalidateRect(rect); //simulates the WM_PAINT message to redraw window
		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


// ***** Shape frame START *****

//When clicking on Rectangle radio button
void CPaintDlg::OnBnClickedRectangle(){ futureFigureKind = 1;}
void CPaintDlg::OnBnClickedEllipse() { futureFigureKind = 2; }
void CPaintDlg::OnBnClickedTriangle() { futureFigureKind = 3; }
void CPaintDlg::OnBnClickedLine() { futureFigureKind = 4; }
void CPaintDlg::OnBnClickedMagendavid() { futureFigureKind = 5; }

// ***** Shape frame END *****

// ***** Brush type frame START *****

void CPaintDlg::OnBnClickedSolid()
{
	int ChkBox = m_solidCheckBox->GetCheck();

	if (ChkBox == BST_CHECKED)
	{
		penStyle = PS_SOLID;
		m_solidCheckBox->SetCheck(BST_CHECKED);
		m_dashCheckBox->SetCheck(BST_UNCHECKED);
		m_dotsCheckBox->SetCheck(BST_UNCHECKED);
		m_dashDotsCheckBox->SetCheck(BST_UNCHECKED);
	}
}

void CPaintDlg::OnBnClickedDash()
{
	int ChkBox = m_dashCheckBox->GetCheck();

	if (ChkBox == BST_CHECKED)
	{
		penStyle = PS_DASH;
		m_dashCheckBox->SetCheck(BST_CHECKED);
		m_solidCheckBox->SetCheck(BST_UNCHECKED);
		m_dotsCheckBox->SetCheck(BST_UNCHECKED);
		m_dashDotsCheckBox->SetCheck(BST_UNCHECKED);
	}
}

void CPaintDlg::OnBnClickedDots()
{
	int ChkBox = m_dotsCheckBox->GetCheck();

	if (ChkBox == BST_CHECKED)
	{
		penStyle = PS_DOT;
		m_dashCheckBox->SetCheck(BST_UNCHECKED);
		m_solidCheckBox->SetCheck(BST_UNCHECKED);
		m_dashDotsCheckBox->SetCheck(BST_UNCHECKED);
		m_dotsCheckBox->SetCheck(BST_CHECKED);
	}
}

void CPaintDlg::OnBnClickedDashdot()
{
	int ChkBox = m_dashDotsCheckBox->GetCheck();

	if (ChkBox == BST_CHECKED)
	{
		penStyle = PS_DASHDOT;
		m_dashCheckBox->SetCheck(BST_UNCHECKED);
		m_solidCheckBox->SetCheck(BST_UNCHECKED);
		m_dotsCheckBox->SetCheck(BST_UNCHECKED);
		m_dashDotsCheckBox->SetCheck(BST_CHECKED);
	}
}

// ***** Brush type frame END *****

// ***** Brush size frame START *****

void CPaintDlg::OnBnClickedSmall()
{
	int ChkBox = m_smallCheckBox->GetCheck();

	if (ChkBox == BST_CHECKED)
	{
		penSize = 1;
		m_bigCheckBox->SetCheck(BST_UNCHECKED);
		m_mediumCheckBox->SetCheck(BST_UNCHECKED);
		m_smallCheckBox->SetCheck(BST_CHECKED);
	}
}

void CPaintDlg::OnBnClickedMedium()
{
	int ChkBox = m_mediumCheckBox->GetCheck();

	if (ChkBox == BST_CHECKED)
	{
		penSize = 3;
		m_bigCheckBox->SetCheck(BST_UNCHECKED);
		m_mediumCheckBox->SetCheck(BST_CHECKED);
		m_smallCheckBox->SetCheck(BST_UNCHECKED);
	}
}

void CPaintDlg::OnBnClickedBig()
{
	int ChkBox = m_bigCheckBox->GetCheck();

	if (ChkBox == BST_CHECKED)
	{
		penSize = 5;
		m_bigCheckBox->SetCheck(BST_CHECKED);
		m_mediumCheckBox->SetCheck(BST_UNCHECKED);
		m_smallCheckBox->SetCheck(BST_UNCHECKED);
	}
}

// ***** Brush size frame END *****

// ***** Menu frame START *****

void CPaintDlg::OnBnClickedSave()
{
	// FALSE to SAVE
	CFileDialog dlg(FALSE, _T(".figs"), NULL, 0, _T("Figures (*.figs)|*.figs|All Files (*.*)|*.*||"));
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName(); // return full path and filename
		CFile file(filename, CFile::modeCreate | CFile::modeWrite);
		CArchive ar(&file, CArchive::store);
		figs.Serialize(ar);
		ar.Close();
		file.Close();
	}
}

void CPaintDlg::OnBnClickedLoad()
{
	// TRUE to LOAD
	CFileDialog dlg(TRUE, _T(".figs"), NULL, 0, _T("Figures (*.figs)|*.figs|All Files (*.*)|*.*||"));
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName(); // return full path and filename
		CFile file(filename, CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		figs.Serialize(ar);
		ar.Close();
		file.Close();
		InvalidateRect(rect);
	}
}

void CPaintDlg::OnBnClickedClean()
{
	while (figs.GetSize() > 0)
	{
		delete figs.GetAt(0);
		figs.RemoveAt(0);
	}
	InvalidateRect(rect);
}

// ***** Menu frame END *****

// ***** Options control START *****

void CPaintDlg::OnBnClickedDrag()
{
	isDragged = true;
	CButton* drag = (CButton*)GetDlgItem(DRAG);
	drag->EnableWindow(false);
}

void CPaintDlg::OnBnClickedUndo()
{
	int length = figs.GetSize();
	if (length > 0)
	{
		figs.RemoveAt(length - 1);
	}

	Invalidate();
}

void CPaintDlg::OnBnClickedDeletefig()
{
	deleteMode = true;
	CButton* deleteFig = (CButton*)GetDlgItem(DELETEFIG);
	deleteFig->EnableWindow(false);
}

void CPaintDlg::deleteShape(CPoint point)
{
	deleteMode = false;
	int indexToDel = -1;
	for (int i = 0; i < figs.GetSize() - 1; i++)
	{
		if (figs[i]->isInside(point) == true)
		{
			indexToDel = i;
		}
	}

	if (indexToDel != -1)
	{
		delete figs.GetAt(indexToDel);
		figs.RemoveAt(indexToDel);
		InvalidateRect(rect);
	}
}
// ***** Options control END *****

// ***** Design control START *****
void CPaintDlg::OnBnClickedChangecolor()
{
	colorMode = true;
	CButton* colorModeButton = (CButton*)GetDlgItem(CHANGECOLOR);
	colorModeButton->EnableWindow(false);
}

void CPaintDlg::ColoringShape(CPoint point)
{
	colorMode = false;

	int indexToChange = -1;
	for (int i = 0; i < figs.GetSize() - 1; i++)
	{
		if (figs[i]->isInside(point) == true)
		{
			indexToChange = i;
		}
	}
	if (indexToChange != -1)
	{
		figs[indexToChange]->setFillColor(colorOfTheShape.GetColor());
		figs[indexToChange]->setBrushColor(colorOfTheBorder.GetColor());
		InvalidateRect(rect);
	}
}
// ***** Design control END *****





