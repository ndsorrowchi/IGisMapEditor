#pragma once

#include "DataTemplate.h"
#include "DataBase.h"
#include "Cordins.h"
#include "afxcmn.h"

// PolygonView �Ի���

class PolygonView : public CDialogEx
{
	DECLARE_DYNAMIC(PolygonView)

public:
	PolygonView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PolygonView();

// �Ի�������
	enum { IDD = IDD_PolygonView };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
public:
	gisPolygon * gPoly,selectgPoly,oldgPoly;
	int selectIndex;
	CString selectID;
	CString table;
	int count;
	int oldIndex;
	CZoomManager * pZoom;
	void flash(CDC * pDC);
	void endflash(CDC * pDC);
	bool hasInit;
	CString getBorderType(gisPolygon &g);
	virtual void OnCancel();
	CListCtrl PolyView;
	afx_msg void OnBnClickedButton2();
	int getPolygon(gisPolygon & g,CString id);
};
