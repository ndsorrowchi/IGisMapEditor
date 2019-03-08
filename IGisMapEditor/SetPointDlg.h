#pragma once
#include "afxwin.h"


// SetPointDlg �Ի���

class SetPointDlg : public CDialog
{
	DECLARE_DYNAMIC(SetPointDlg)

public:
	SetPointDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SetPointDlg();

// �Ի�������
	enum { IDD = IDD_SETPOINT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSelectcolor();
	CStatic colorView;
	CStatic resultView;
	int shapeSize;
	CPoint p;
	COLORREF m_color;
	CDC memDC;
	bool mouseMove;
	bool init;
	CString shapeType;
	void OnShowResultView();
	afx_msg void OnBnClickedRadiocircle();
	afx_msg void OnBnClickedRadiocrect();
	afx_msg void OnBnClickedRadiozrect();
	afx_msg void OnBnClickedRadiosj();
	afx_msg void OnBnClickedRadioelipese();
	afx_msg void OnDeltaposSpinaltersize(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
