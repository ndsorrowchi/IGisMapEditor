#pragma once


// CCreateDBDlg �Ի���

class CCreateDBDlg : public CDialog
{
	DECLARE_DYNAMIC(CCreateDBDlg)

public:
	CCreateDBDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCreateDBDlg();

// �Ի�������
	enum { IDD = IDD_CREATEDBDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_server;
	CString m_user;
	CString m_pin;
	CString m_name;
	CString m_path;
	afx_msg void OnBnClickedSet();
	afx_msg void OnBnClickedOk();
};
