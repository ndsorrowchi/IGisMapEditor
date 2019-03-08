// CreateDBDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IGisMapEditor.h"
#include "CreateDBDlg.h"
#include "afxdialogex.h"

#include "DataBase.h"

// CCreateDBDlg �Ի���

IMPLEMENT_DYNAMIC(CCreateDBDlg, CDialog)

CCreateDBDlg::CCreateDBDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateDBDlg::IDD, pParent)
	, m_server(_T(""))
	, m_user(_T(""))
	, m_pin(_T(""))
	, m_name(_T(""))
	, m_path(_T(""))
{

}

CCreateDBDlg::~CCreateDBDlg()
{
}

void CCreateDBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SERVER, m_server);
	DDX_Text(pDX, IDC_USER, m_user);
	DDX_Text(pDX, IDC_PIN, m_pin);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_PATH, m_path);
}


BEGIN_MESSAGE_MAP(CCreateDBDlg, CDialog)
	ON_BN_CLICKED(IDC_SET, &CCreateDBDlg::OnBnClickedSet)
	ON_BN_CLICKED(IDOK, &CCreateDBDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CCreateDBDlg ��Ϣ�������

/*
void CCreateDBDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	DBConnection db;
	bool x=db.CreateDataBase(m_server,m_name,m_user,m_pin,m_path);
	if(x)
	{
		CDialog::OnOK();
	}
	else
	{MessageBox(L"δ�ܴ�����������Ϣ",L"����",MB_ICONERROR|MB_OK);}
}


void CCreateDBDlg::OnBnClickedSet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CFileDialog dlg(FALSE);
	dlg.m_ofn.lpstrDefExt=L"mdf";
	dlg.m_ofn.lpstrFilter=L"Sql DB Files(*.mdf)\0*.mdf\0\0";
	dlg.m_ofn.lpstrTitle=L"���ô洢λ��";
	if(IDOK==dlg.DoModal())
	{
		m_name=dlg.GetFileTitle();
		CString temp=dlg.GetPathName();
		int npos=temp.ReverseFind(L'\\');
		m_path=temp.Left(npos+1);
		UpdateData(FALSE);
	}
}
*/

void CCreateDBDlg::OnBnClickedSet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CFileDialog dlg(FALSE);
	dlg.m_ofn.lpstrDefExt=L"mdf";
	dlg.m_ofn.lpstrFilter=L"Sql DB Files(*.mdf)\0*.mdf\0\0";
	dlg.m_ofn.lpstrTitle=L"���ô洢λ��";
	if(IDOK==dlg.DoModal())
	{
		m_name=dlg.GetFileTitle();
		CString temp=dlg.GetPathName();
		int npos=temp.ReverseFind(L'\\');
		m_path=temp.Left(npos+1);
		UpdateData(FALSE);
	}
}


void CCreateDBDlg::OnBnClickedOk()
{// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	DBConnection db;
	bool x=db.CreateDataBase(m_server,m_name,m_user,m_pin,m_path);
	if(x)
	{
		CDialog::OnOK();
	}
	else
	{MessageBox(L"δ�ܴ�����������Ϣ",L"����",MB_ICONERROR|MB_OK);}	
}
