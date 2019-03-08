// AddLayerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IGisMapEditor.h"
#include "AddLayerDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "DataBase.h"

UINT ID_TIMERADD =900;
// CAddLayerDlg �Ի���

IMPLEMENT_DYNAMIC(CAddLayerDlg, CDialog)

CAddLayerDlg::CAddLayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddLayerDlg::IDD, pParent)
	, m_selectedinfo(_T(""))
	, m_selindex(-1)
	, m_selid(0)
{

}

CAddLayerDlg::~CAddLayerDlg()
{
}

void CAddLayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TABLES, m_lists);
	DDX_Text(pDX, IDC_SELECTED, m_selectedinfo);
}


BEGIN_MESSAGE_MAP(CAddLayerDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAddLayerDlg::OnBnClickedOk)
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, &CAddLayerDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CAddLayerDlg ��Ϣ�������


void CAddLayerDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_selindex!=-1)
	{
		KillTimer(ID_TIMERADD);
		CDialog::OnOK();
	}
	else AfxMessageBox(L"û��ѡ��ͼ��!");
}

CString GetTypeStr(int type)
{
	CString str;
	switch(type)
	{
	case 0:str=L"��ͼ��";break;
	case 1:str=L"��ͼ��";break;
	case 2:str=L"��ͼ��";break;
	case 3:str=L"ע��ͼ��";break;
	default:str=L"";break;
	}
	return str;
}

BOOL CAddLayerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetTimer(ID_TIMERADD,10,NULL);
	CMainFrame * pMainFrame = (CMainFrame *)::AfxGetMainWnd();
	if(!pMainFrame->db.isConnection())
	   pMainFrame->db.Open(server,name,user,pin);
	CRect r;
	CatalogTable tableSet[50];
	m_lists.GetClientRect(&r);
	m_lists.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_lists.InsertColumn(0,_T("ID"));
	m_lists.InsertColumn(1,_T("ͼ����"));
	m_lists.InsertColumn(2,_T("����"));

	m_lists.SetColumnWidth(0,40);
	m_lists.SetColumnWidth(1,r.Width()-100);
	m_lists.SetColumnWidth(2,60);
	int tableCount=pMainFrame->db.GetDataBaseTable(tableSet);
	int n=0;
	CString tmp;
	while(n<tableCount)
	{
		m_lists.InsertItem(n,tableSet[n].ID);
		m_lists.SetItemText(n,1,tableSet[n].tableName);
		tmp=GetTypeStr(tableSet[n].tableType-1);
		m_lists.SetItemText(n,2,tmp);
		n++;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CAddLayerDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
/*	m_selindex=m_lists.GetNextItem(-1,LVNI_SELECTED);
	if(m_selindex==-1){m_selectedinfo=L"û��ѡ��";}
	else
	{
		CString str=m_lists.GetItemText(m_selindex,1);
		m_selectedinfo=str;
	}
	UpdateData(FALSE);*/
	CDialog::OnMouseMove(nFlags, point);
}


void CAddLayerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_selindex=m_lists.GetNextItem(-1,LVNI_SELECTED);
	if(m_selindex==-1){m_selectedinfo=L"û��ѡ��";m_selid=0;}
	else
	{
		CString str=m_lists.GetItemText(m_selindex,1);
		m_selectedinfo=str;
		CString str2=m_lists.GetItemText(m_selindex,0);
		m_selid=strtoi(str2);
	}
	UpdateData(FALSE);
	CDialog::OnTimer(nIDEvent);
}


void CAddLayerDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer(ID_TIMERADD);
	CDialog::OnCancel();
}
