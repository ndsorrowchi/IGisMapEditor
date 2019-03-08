#pragma once
#include "afxwin.h"


// CLineTypeDlg �Ի���

class CLineTypeDlg : public CDialog
{
	DECLARE_DYNAMIC(CLineTypeDlg)

public:
	CLineTypeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLineTypeDlg();

// �Ի�������
	enum { IDD = IDD_SETLINE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedColorbtn();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CStatic m_result;
	CStatic m_colorPic;
	afx_msg void OnBnClickedDash();
	afx_msg void OnBnClickedDot();
	afx_msg void OnBnClickedDashdot();
	afx_msg void OnBnClickedDashdotdot();
	afx_msg void OnBnClickedSolid();
	int m_width;
	COLORREF m_color;
	DWORD PENSTYLE;
	void ViewEffect(void);
	void SetTypeCheck(void);
	CPoint p;
	int penStyle;
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	BOOL m_curve;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedButton2();
};
