#pragma once
#include "afxcmn.h"
#include "DataTemplate.h"
#include "AlterBaseTool.h"
#include "Cordins.h"

// PointView �Ի���

class PointView : public CDialog
{
	DECLARE_DYNAMIC(PointView)

public:
	PointView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PointView();

// �Ի�������
	enum { IDD = IDD_PointView };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_PointSet;
	afx_msg void OnBnClickedEditbnt();
	afx_msg void OnBnClickedDeletebnt();
	afx_msg void OnBnClickedOk();
	int getPoint(gisPoint&gp,CString id);
public:
	gisPoint * gp,selectgp,oldgp;
	int selectIndex;
	CString selectID;
	CString table;
	int count;
	int oldIndex;
	CZoomManager * pZoom;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void flash(CDC * pDC);
	void endflash(CDC * pDC);
	virtual BOOL OnInitDialog();
	bool hasInit;
	virtual void OnCancel();
};
