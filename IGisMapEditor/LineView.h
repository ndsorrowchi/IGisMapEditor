#pragma once
#include "afxcmn.h"
#include "DataTemplate.h"
#include "Cordins.h"

// LineView �Ի���

class LineView : public CDialog
{
	DECLARE_DYNAMIC(LineView)

public:
	LineView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LineView();

// �Ի�������
	enum { IDD = IDD_LineView };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl LineSet;
	afx_msg void OnBnClickedAlterbnt();
	int getLine(gisLine&gl,CString id);
	afx_msg void OnBnClickedDeletebnt();
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
public:
	gisLine * gl,selectgl,oldgl;
	int selectIndex;
	CString selectID;
	CString table;
	int count;
	int oldIndex;
	CZoomManager * pZoom;
	void flash(CDC * pDC);
	void endflash(CDC * pDC);
	bool hasInit;
	CString getLineType(gisLine &gl);
	virtual void OnCancel();
};
