#pragma once
#include "afxcmn.h"
#include "DataBase.h"
#include "FileView.h"

// CDeleteDlg �Ի���

class CDeleteDlg : public CDialog
{
	DECLARE_DYNAMIC(CDeleteDlg)

public:
	CDeleteDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeleteDlg();

// �Ի�������
	enum { IDD = IDD_DELETEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_viewtable;
	int nindex;
	CString lname;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CFileView *pView;
	DBConnection* db;
};
