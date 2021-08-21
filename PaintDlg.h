
// PaintDlg.h : header file
//

#pragma once
#include "Figure.h"
#include "FRectangle.h"
#include "FEllipse.h"
#include "FTriangle.h"
#include "FLine.h"
#include "FDStar.h"

// CPaintDlg dialog
class CPaintDlg : public CDialogEx
{
// Construction
public:
	CPaintDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAINT_DIALOG };
#endif

	CPoint start, end;
	bool isPressed = false;
	CTypedPtrArray< CObArray, Figure*> figs;
	int futureFigureKind = 1; 

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	CRect rect;
	CBrush m_brush;	

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};
