// NewLayerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IGisMapEditor.h"
#include "NewLayerDlg.h"
#include "afxdialogex.h"


// CNewLayerDlg �Ի���

IMPLEMENT_DYNAMIC(CNewLayerDlg, CDialog)

CNewLayerDlg::CNewLayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewLayerDlg::IDD, pParent)
	, m_name(_T(""))
	, m_nindex(0)
{

}

CNewLayerDlg::~CNewLayerDlg()
{
}

void CNewLayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Control(pDX, IDC_TYPE, m_combo);
}


BEGIN_MESSAGE_MAP(CNewLayerDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CNewLayerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CNewLayerDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


BOOL CNewLayerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_combo.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

// CNewLayerDlg ��Ϣ�������



void CNewLayerDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(m_name!=L"")
	{
		m_nindex=m_combo.GetCurSel();
		CDialog::OnOK();
	}
	else
		MessageBox(L"����д������ͼ������",L"ERROR",MB_ICONWARNING|MB_OK);
}


void CNewLayerDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}
