#pragma once


// CRegionTypeDlg �Ի���

class CRegionTypeDlg : public CDialog
{
	DECLARE_DYNAMIC(CRegionTypeDlg)

public:
	CRegionTypeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRegionTypeDlg();

// �Ի�������
	enum { IDD = IDD_SETPOLYGON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSidecl();
	afx_msg void OnBnClickedSolid();
	afx_msg void OnBnClickedDash();
	afx_msg void OnBnClickedDot();
	afx_msg void OnBnClickedDashdot();
	afx_msg void OnBnClickedDashdotdot();
	afx_msg void OnBnClickedRgncl();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	void OnBnClickedViewit();
	CStatic m_viewTotal;
	int m_sideType;
	COLORREF m_sideColor;
	COLORREF m_fillColor;
	CStatic m_viewRgnSide;
	CStatic m_viewRgnFill;
	CPoint p;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
};
