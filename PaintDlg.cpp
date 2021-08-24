
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
	brushColor = RGB(0, 0, 0);
	fillColor = RGB(255, 255, 255);
	rect.SetRect(30, 150, 680, 410);

}

void CPaintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPaintDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_RADIO1, &CPaintDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CPaintDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CPaintDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CPaintDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CPaintDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_BUTTON1, &CPaintDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPaintDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CPaintDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CPaintDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CPaintDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CPaintDlg message handlers

BOOL CPaintDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CheckRadioButton(IDC_RADIO1, IDC_RADIO5, IDC_RADIO1);

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
		for (int i = 0; i < figs.GetSize(); i++)
		{
			//Handle CPen and CBrush outside
			CPen pen;
			CPen* oldPen;
			pen.CreatePen(figs[i]->getPenStyle(), 1, figs[i]->getBrushColor());
			oldPen = dc.SelectObject(&pen);
			CBrush brush(figs[i]->getFillColor());
			CBrush* oldBrush;
			oldBrush = dc.SelectObject(&brush);
			
			figs[i]->Draw(&dc);
			
			dc.SelectObject(oldPen);
			dc.SelectObject(oldBrush);
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
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CPaintDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	if (isPressed)
	{
		end = point;
		isPressed = false;
		figs[figs.GetSize() - 1]->Redefine(start, end);
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
		figs[figs.GetSize() - 1]->Redefine(start, end);
		figs[figs.GetSize() - 1]->setBrushColor(brushColor);
		figs[figs.GetSize() - 1]->setFillColor(fillColor);
		InvalidateRect(rect); //simulates the WM_PAINT message to redraw window
	}
	CDialogEx::OnMouseMove(nFlags, point);
}

void CPaintDlg::OnBnClickedRadio1() { futureFigureKind = 1; }

void CPaintDlg::OnBnClickedRadio2() { futureFigureKind = 2; }

void CPaintDlg::OnBnClickedRadio3() { futureFigureKind = 3; }

void CPaintDlg::OnBnClickedRadio4() { futureFigureKind = 4; }

void CPaintDlg::OnBnClickedRadio5() { futureFigureKind = 5; }

void CPaintDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	
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

void CPaintDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	
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


void CPaintDlg::OnBnClickedButton3()
{
	while (figs.GetSize() > 0)
	{
		delete figs.GetAt(0);
		figs.RemoveAt(0);
	}
	InvalidateRect(rect);
}


void CPaintDlg::OnBnClickedButton4()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		brushColor = dlg.GetColor();
	}
}


void CPaintDlg::OnBnClickedButton5()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		fillColor = dlg.GetColor();
	}
}

