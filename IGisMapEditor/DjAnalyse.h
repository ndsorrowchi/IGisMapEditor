#pragma once


// DjAnalyse �Ի���

class DjAnalyse : public CDialog
{
	DECLARE_DYNAMIC(DjAnalyse)

public:
	DjAnalyse(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DjAnalyse();

// �Ի�������
	enum { IDD = IDD_DJAnalyse };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString ResultLayer;
	int layer1Count,layer2Count,selectIndex;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
};
