#pragma once
#include "afxwin.h"


// CNewLayerDlg �Ի���

class CNewLayerDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewLayerDlg)

public:
	CNewLayerDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewLayerDlg();

// �Ի�������
	enum { IDD = IDD_NEWLAYERDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_name;
	CComboBox m_combo;
	int m_nindex;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
