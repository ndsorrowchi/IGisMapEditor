#pragma once
#include "DataBase.h"

// CConnectDbDlg �Ի���

class CConnectDbDlg : public CDialog
{
	DECLARE_DYNAMIC(CConnectDbDlg)

public:
	CConnectDbDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CConnectDbDlg();

// �Ի�������
	enum { IDD = IDD_CONNDBDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_server;
	CString m_name;
	CString m_user;
	CString m_pin;
	BOOL m_remember;
	BOOL m_rememberPin;
	DBConnection *pdb;
	virtual BOOL OnInitDialog();
};
