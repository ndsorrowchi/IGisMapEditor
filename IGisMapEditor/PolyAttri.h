#pragma once
#include "DataTemplate.h"
#include "DataBase.h"
#include "Cordins.h"
#include "afxcmn.h"
#include "MainFrm.h"

// PolyAttri �Ի���

class PolyAttri : public CDialog
{
	DECLARE_DYNAMIC(PolyAttri)

public:
	PolyAttri(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PolyAttri();

// �Ի�������
	enum { IDD = IDD_PolyAttri };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAlter();
	afx_msg void OnBnClickedDelbnt();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
public:
	gisPolygon * gPoly,selectgPoly,oldgPoly;
	int selectIndex;
	CString selectID;
	Layer * layer;
	int count;
	int oldIndex;
	CZoomManager * pZoom;
	void flash(CDC * pDC);
	void endflash(CDC * pDC);
	bool hasInit;
	CString getBorderType(gisPolygon &g);
	int getPolygon(gisPolygon & g,CString id);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	CListCtrl PolyTable;
};
