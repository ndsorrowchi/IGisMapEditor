#pragma once
#include "afxcmn.h"


// CAddLayerDlg �Ի���

class CAddLayerDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddLayerDlg)

public:
	CAddLayerDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddLayerDlg();

// �Ի�������
	enum { IDD = IDD_ADDLAYERDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	CListCtrl m_lists;
public:
	CString m_selectedinfo;
	int m_selindex;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CString server;
	CString name;
	CString user;
	CString pin;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCancel();
	int m_selid;
};
