
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
	CPoint startDrag, endDrag;
	bool isPressed = false;
	bool isDragged = false;
	bool colorMode = false;
	bool deleteMode = false;
	int dragIndex;
	CTypedPtrArray< CObArray, Figure*> figs;
	int futureFigureKind = 1; 
	CRect rect;
	CMFCColorButton colorOfTheShape, colorOfTheBorder;
	int penStyle, penSize;
	CButton* m_solidCheckBox, *m_dashCheckBox, *m_dotsCheckBox, *m_dashDotsCheckBox, *m_smallCheckBox, *m_mediumCheckBox, *m_bigCheckBox;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	

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
	afx_msg void OnBnClickedRectangle();
	afx_msg void OnBnClickedEllipse();
	afx_msg void OnBnClickedTriangle();
	afx_msg void OnBnClickedLine();
	afx_msg void OnBnClickedMagendavid();
	afx_msg void OnBnClickedSolid();
	afx_msg void OnBnClickedDash();
	afx_msg void OnBnClickedDots();
	afx_msg void OnBnClickedDashdot();
	afx_msg void OnBnClickedSmall();
	afx_msg void OnBnClickedMedium();
	afx_msg void OnBnClickedBig();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();
	afx_msg void OnBnClickedClean();
	afx_msg void OnBnClickedDrag();
	afx_msg void OnBnClickedChangecolor();
	void ColoringShape(CPoint point);
	void deleteShape(CPoint point);
	afx_msg void OnBnClickedDeletefig();
	afx_msg void OnBnClickedUndo();
};
