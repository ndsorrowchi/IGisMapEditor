// MapCordinDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IGisMapEditor.h"
#include "MapCordinDlg.h"
#include "afxdialogex.h"

UINT ID_TIMER1=30667;
// CMapCordinDlg �Ի���

IMPLEMENT_DYNAMIC(CMapCordinDlg, CDialog)

CMapCordinDlg::CMapCordinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMapCordinDlg::IDD, pParent)
	, m_ltx(0.0)
	, m_lty(0.0)
	, m_rbx(0.0)
	, m_rby(0.0)
{
	shown=false;
}

CMapCordinDlg::~CMapCordinDlg()
{
}

void CMapCordinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LTX, m_ltx);
	DDX_Text(pDX, IDC_LTY, m_lty);
	DDX_Text(pDX, IDC_RBX, m_rbx);
	DDX_Text(pDX, IDC_RBY, m_rby);
	DDX_Control(pDX, IDC_Map, m_map);
}


BEGIN_MESSAGE_MAP(CMapCordinDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CMapCordinDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMapCordinDlg::OnBnClickedCancel)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CMapCordinDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMapCordinDlg ��Ϣ�������


void CMapCordinDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(m_ltx<m_rbx&&m_rby<m_lty)
		{CDialog::OnOK();KillTimer(ID_TIMER1);}
	else
	{AfxMessageBox(L"�������������");}
}


void CMapCordinDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

		CImage img;
		img.Load(pathname);
		m_ltx=m_rby=0;
		m_lty=img.GetHeight();
		m_rbx=img.GetWidth();
		CDialog::OnCancel();
		KillTimer(ID_TIMER1);
}


BOOL CMapCordinDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetTimer(ID_TIMER1,1,NULL);
	shown=false;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CMapCordinDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(!shown)
	{
		CDC*pDC=m_map.GetDC();
		CRect r;
		m_map.GetClientRect(&r);
		CImage img;
		img.Load(pathname);
		::StretchBlt(pDC->m_hDC,0,0,r.Width(),r.Height(),img.GetDC(),0,0,img.GetWidth(),img.GetHeight(),SRCCOPY);
		img.ReleaseDC();
		shown=true;
	}
	CDialog::OnTimer(nIDEvent);
}


void CMapCordinDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		CDC*pDC=m_map.GetDC();
		CRect r;
		m_map.GetClientRect(&r);
		CImage img;
		img.Load(pathname);
		::StretchBlt(pDC->m_hDC,0,0,r.Width(),r.Height(),img.GetDC(),0,0,img.GetWidth(),img.GetHeight(),SRCCOPY);
		img.ReleaseDC();
}
