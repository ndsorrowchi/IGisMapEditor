// SetPointDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IGisMapEditor.h"
#include "SetPointDlg.h"
#include "afxdialogex.h"
#include "SColorDlg.h"

// SetPointDlg �Ի���

IMPLEMENT_DYNAMIC(SetPointDlg, CDialog)

SetPointDlg::SetPointDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SetPointDlg::IDD, pParent)
	, shapeSize(1)
	, mouseMove(false)
	, shapeType(L"")
{
	m_color=RGB(0,0,0);
	p.x=500;
	p.y=250;
	init=false;
}

SetPointDlg::~SetPointDlg()
{
}

void SetPointDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Color, colorView);
	DDX_Control(pDX, IDC_View, resultView);
	DDX_Text(pDX, IDC_POINTSIZE, shapeSize);
}


BEGIN_MESSAGE_MAP(SetPointDlg, CDialog)
	ON_BN_CLICKED(IDOK, &SetPointDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &SetPointDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SelectColor, &SetPointDlg::OnBnClickedSelectcolor)
	ON_BN_CLICKED(IDC_RadioCircle, &SetPointDlg::OnBnClickedRadiocircle)
	ON_BN_CLICKED(IDC_RadioCRect, &SetPointDlg::OnBnClickedRadiocrect)
	ON_BN_CLICKED(IDC_RadioZRect, &SetPointDlg::OnBnClickedRadiozrect)
	ON_BN_CLICKED(IDC_RadioSJ, &SetPointDlg::OnBnClickedRadiosj)
	ON_BN_CLICKED(IDC_RadioElipese, &SetPointDlg::OnBnClickedRadioelipese)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINAlterSize, &SetPointDlg::OnDeltaposSpinaltersize)
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// SetPointDlg ��Ϣ�������


void SetPointDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}


void SetPointDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}


void SetPointDlg::OnBnClickedSelectcolor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CColorDialog cldlg;//(NULL,CC_RGBINIT,this);
	cldlg.m_cc.Flags|=CC_RGBINIT;
	//CColorDlg cldlg;
	if(IDOK==cldlg.DoModal())
	{
		this->m_color=cldlg.GetColor();
		CRect r;
		colorView.GetClientRect(&r);
		CDC *pDC=colorView.GetDC();
		CBrush brush(m_color);
		pDC->FillRect(&r,&brush);
		colorView.ReleaseDC(pDC);
		this->OnShowResultView();
	}
}


void SetPointDlg::OnShowResultView()
{
	CRect r;
	this->resultView.GetClientRect(&r);
	CClientDC pDC(&this->resultView);
	int x = r.Width()/2;
	int y = r.Height()/2;
	CPen * pen =new CPen(PS_SOLID,1,WHITE_PEN);
	CPen * pOldPen=pDC.SelectObject(pen);
	CBrush * brush = CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH));
	CBrush * pOldBrush = pDC.SelectObject(brush);
	pDC.Rectangle(&r);
	pDC.SelectObject(pOldBrush);
	pDC.SelectObject(pOldPen);
	pen = new CPen(PS_SOLID,1,this->m_color);
	brush = new CBrush(this->m_color);
	pOldBrush = pDC.SelectObject(brush);
	pOldPen = pDC.SelectObject(pen);
	if(this->shapeType=="Circle")
	    pDC.Ellipse(x-(this->shapeSize+5),y-(this->shapeSize+5),x+(this->shapeSize+5),y+(this->shapeSize+5));
	else if(this->shapeType=="cRect")
		pDC.Rectangle(x-(this->shapeSize+5),y-(this->shapeSize+3),x+(this->shapeSize+5),y+(this->shapeSize+3));
	else if(this->shapeType=="zRect")
		pDC.Rectangle(x-(this->shapeSize+5),y-(this->shapeSize+5),x+(this->shapeSize+5),y+(this->shapeSize+5));
	else if(this->shapeType=="SJ")
	{
		CPoint point[3];
		point[0]=CPoint(x,y-(this->shapeSize+5));
		point[1]=CPoint(x-(this->shapeSize+5),y+(this->shapeSize+5));
		point[2]=CPoint(x+(this->shapeSize+5),y+(this->shapeSize+5));
		pDC.Polygon(point,3);
	}
	else if(this->shapeType=="Ellipes")
		pDC.Ellipse(x-(this->shapeSize+5),y-(this->shapeSize+1),x+(this->shapeSize+5),y+(this->shapeSize+1));
	pDC.SelectObject(pOldBrush);
	pDC.SelectObject(pOldPen);
	this->resultView.ReleaseDC(&pDC);
}


void SetPointDlg::OnBnClickedRadiocircle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->shapeType="Circle";
	this->OnShowResultView();
	((CButton*)GetDlgItem(IDC_RadioCircle))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RadioCRect))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RadioZRect))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RadioSJ))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RadioElipese))->SetCheck(FALSE);
}


void SetPointDlg::OnBnClickedRadiocrect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->shapeType="cRect";
	this->OnShowResultView();
	((CButton*)GetDlgItem(IDC_RadioCircle))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RadioCRect))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RadioZRect))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RadioSJ))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RadioElipese))->SetCheck(FALSE);
}


void SetPointDlg::OnBnClickedRadiozrect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->shapeType="zRect";
	this->OnShowResultView();
	((CButton*)GetDlgItem(IDC_RadioCircle))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RadioCRect))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RadioZRect))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RadioSJ))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RadioElipese))->SetCheck(FALSE);
}


void SetPointDlg::OnBnClickedRadiosj()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->shapeType="SJ";
	this->OnShowResultView();
	((CButton*)GetDlgItem(IDC_RadioCircle))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RadioCRect))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RadioZRect))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RadioSJ))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RadioElipese))->SetCheck(FALSE);
}


void SetPointDlg::OnBnClickedRadioelipese()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->shapeType="Ellipes";
	this->OnShowResultView();
	((CButton*)GetDlgItem(IDC_RadioCircle))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RadioCRect))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RadioZRect))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RadioSJ))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RadioElipese))->SetCheck(TRUE);
}


void SetPointDlg::OnDeltaposSpinaltersize(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(pNMUpDown-> iDelta == 1) // �����ֵΪ1 , ˵�������Spin�����¼�ͷ 
	{ 
		if(this->shapeSize>1) this->shapeSize--;
		UpdateData(FALSE);
	} 
	else if(pNMUpDown-> iDelta == -1) // �����ֵΪ-1 , ˵�������Spin�����ϼ�ͷ 
	{ 
		if(this->shapeSize<20) this->shapeSize++;
		UpdateData(FALSE);
	}
	this->OnShowResultView();
}


BOOL SetPointDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if(this->shapeType=="Circle")
		((CButton*)GetDlgItem(IDC_RadioCircle))->SetCheck(TRUE);
	else if(this->shapeType=="SJ")
		((CButton*)GetDlgItem(IDC_RadioSJ))->SetCheck(TRUE);
	else if(this->shapeType=="cRect")
		((CButton*)GetDlgItem(IDC_RadioCRect))->SetCheck(TRUE);
	else if(this->shapeType=="zRect")
		((CButton*)GetDlgItem(IDC_RadioZRect))->SetCheck(TRUE);
	else if(this->shapeType=="Ellipes")
		((CButton*)GetDlgItem(IDC_RadioElipese))->SetCheck(TRUE);
	this->SetWindowPos(&wndTopMost,p.x,p.y,100,100,SWP_NOSIZE);
	SetTimer(0,100,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void SetPointDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	this->OnShowResultView();
	CRect r;
	colorView.GetClientRect(&r);
	CDC *pDC=colorView.GetDC();
	CBrush brush(m_color);
	pDC->FillRect(&r,&brush);
	colorView.ReleaseDC(pDC);
}


void SetPointDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(!init)
	{
		this->OnShowResultView();
		CRect r;
		colorView.GetClientRect(&r);
		CDC *pDC=colorView.GetDC();
		CBrush brush(m_color);
		pDC->FillRect(&r,&brush);
		colorView.ReleaseDC(pDC);
		init=true;
	}
	CDialog::OnTimer(nIDEvent);
}
