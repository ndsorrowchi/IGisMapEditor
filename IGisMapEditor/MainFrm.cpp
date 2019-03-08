
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "IGisMapEditor.h"
#include "IGisMapEditorView.h"
#include "MainFrm.h"
#include "ConnectDbDlg.h"
#include "CreateDBDlg.h"
#include "DeleteDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MY_WM_NOTIFYICON (WM_USER+1001)

UINT	ID_INDICATOR_X;
UINT	ID_INDICATOR_Y;
UINT	ID_INDICATOR_STATUS;
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_MESSAGE(MY_WM_NOTIFYICON, &CMainFrame::OnNotifyIcon)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_COMMAND(ID_NOTIFY_CLOSE, &CMainFrame::OnNotifyClose)
	ON_WM_CLOSE()
	ON_COMMAND(ID_APP_EXIT, &CMainFrame::OnAppExit)
	ON_COMMAND(ID_SETDBCONNECT, &CMainFrame::OnSetdbconnect)
	ON_COMMAND(ID_CLEARCONNECTION, &CMainFrame::OnClearconnection)
	ON_COMMAND(ID_CREATEDB, &CMainFrame::OnCreatedb)
	ON_COMMAND(ID_DeleteTable, &CMainFrame::OnDeletetable)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_SEPARATOR,
	ID_SEPARATOR,
	ID_SEPARATOR,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,	

};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	m_bMin=true;
	server=dbname=user=code=L"";
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	// �������ڻ��������û�����Ԫ�ص��Ӿ�������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("δ�ܴ����˵���\n");
		return -1;      // δ�ܴ���
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// ��ֹ�˵����ڼ���ʱ��ý���
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), IDR_MAINFRAME) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
//===========
	if (!m_wndBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), IDR_DBTOOLBAR) ||
		!m_wndBar.LoadToolBar(IDR_DBTOOLBAR))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}
	//CString nstrToolBarName;
	//bNameValid = nstrToolBarName.LoadString(IDS_TOOLBAR_MY);
	//ASSERT(bNameValid);
	m_wndBar.SetWindowText(L"IGisDBToolBar");

	//CString nstrCustomize;
	//bNameValid = nstrCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	//ASSERT(bNameValid);
	m_wndBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
//========
//===========
	if (!m_zoomBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), IDR_ZOOMBAR) ||
		!m_zoomBar.LoadToolBar(IDR_ZOOMBAR))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}
	//CString nstrToolBarName;
	//bNameValid = nstrToolBarName.LoadString(IDS_TOOLBAR_MY);
	//ASSERT(bNameValid);
	m_zoomBar.SetWindowText(L"IGisZoomBar");

	//CString nstrCustomize;
	//bNameValid = nstrCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	//ASSERT(bNameValid);
	m_zoomBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
//========
//===========
	if (!m_editBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), IDR_EDITBAR) ||
		!m_editBar.LoadToolBar(IDR_EDITBAR))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}
	//CString nstrToolBarName;
	//bNameValid = nstrToolBarName.LoadString(IDS_TOOLBAR_MY);
	//ASSERT(bNameValid);
	m_editBar.SetWindowText(L"IGisEditBar");

	//CString nstrCustomize;
	//bNameValid = nstrCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	//ASSERT(bNameValid);
	m_editBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
//========
//===========
	if (!m_extBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), IDR_EXTBAR) ||
		!m_extBar.LoadToolBar(IDR_EXTBAR))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}
	//CString nstrToolBarName;
	//bNameValid = nstrToolBarName.LoadString(IDS_TOOLBAR_MY);
	//ASSERT(bNameValid);
	m_extBar.SetWindowText(L"IGisExtBar");

	//CString nstrCustomize;
	//bNameValid = nstrCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	//ASSERT(bNameValid);
	m_extBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
//========	
	// �����û�����Ĺ���������:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	m_wndStatusBar.SetPaneInfo(0,0,SBPS_STRETCH,50);
	m_wndStatusBar.SetPaneInfo(1,ID_INDICATOR_X,SBPS_NORMAL,100);// ����X������Ϣ����(indicators)���Ϊ100
	m_wndStatusBar.SetPaneInfo(2,ID_INDICATOR_Y,SBPS_NORMAL,100);// ����Y������Ϣ����(indicators)���Ϊ100
	m_wndStatusBar.SetPaneInfo(3,ID_INDICATOR_STATUS,SBPS_NORMAL,150);// ����Y������Ϣ����(indicators)���Ϊ50

	// TODO: �������ϣ���������Ͳ˵�����ͣ������ɾ��������
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
//	m_wndMenuBar.EnableDocking(CBRS_ALIGN_TOP);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndBar.EnableDocking(CBRS_ALIGN_ANY);
	m_zoomBar.EnableDocking(CBRS_ALIGN_ANY);
	m_editBar.EnableDocking(CBRS_ALIGN_ANY);
	m_extBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);
	DockPane(&m_wndBar);
	DockPane(&m_zoomBar);
	DockPane(&m_extBar);
	DockPaneLeftOf(&m_editBar,&m_zoomBar);//DockPane(&m_editBar);
//	DockPane(&m_wndMenuBar);
//	DockPaneLeftOf(&m_wndToolBar,&m_wndBar);

	// ���� Visual Studio 2005 ��ʽͣ��������Ϊ
	CDockingManager::SetDockingMode(DT_SMART);
	// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// ���ز˵���ͼ��(�����κα�׼��������):
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	// ����ͣ������
	if (!CreateDockingWindows())
	{
		TRACE0("δ�ܴ���ͣ������\n");
		return -1;
	}

	m_wndFileView.EnableDocking(CBRS_ALIGN_ANY);
	//m_wndClassView.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndFileView);
	CDockablePane* pTabbedBar = NULL;
	//m_wndClassView.AttachToTabWnd(&m_wndFileView, DM_SHOW, TRUE, &pTabbedBar);


	// ���ù�������ͣ�����ڲ˵��滻
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// ���ÿ���(��ס Alt �϶�)�������Զ���
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// �����û�����Ĺ�����ͼ��
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}

	// ���ò˵����Ի�(���ʹ�õ�����)
	// TODO: �������Լ��Ļ������ȷ��ÿ�������˵�������һ���������
	CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail(ID_SORTING_SORTALPHABETIC);
	lstBasicCommands.AddTail(ID_SORTING_SORTBYTYPE);
	lstBasicCommands.AddTail(ID_SORTING_SORTBYACCESS);
	lstBasicCommands.AddTail(ID_SORTING_GROUPBYTYPE);

	CMFCToolBar::SetBasicCommands(lstBasicCommands);
	//icon
	HICON m_hIcon;
	m_hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE); // Set big icon
	SetIcon(m_hIcon, FALSE); // Set small icon
	//notify icon
    m_ntIcon.cbSize = sizeof(NOTIFYICONDATA);                            //�ýṹ������Ĵ�С
    m_ntIcon.hIcon = AfxGetApp()->LoadIconW(IDR_MAINFRAME);  //ͼ�꣬ͨ����ԴID�õ�
    m_ntIcon.hWnd = this->m_hWnd;                                                 //��������ͼ��֪ͨ��Ϣ�Ĵ��ھ��
	WCHAR atip[128] = L"IGis-MapEditor";//���������ʱ��ʾ����ʾ
	//strcpy(m_ntIcon.szTip, 128, atip);
	memcpy(m_ntIcon.szTip,atip,128*sizeof(WCHAR));
    m_ntIcon.uCallbackMessage = MY_WM_NOTIFYICON;                //Ӧ�ó��������ϢID��
    m_ntIcon.uFlags = NIF_MESSAGE|NIF_ICON|NIF_TIP;               //ͼ������ԣ����ó�ԱuCallbackMessage��hIcon��szTip��Ч
    ::Shell_NotifyIconW(NIM_ADD, &m_ntIcon);                                 //��ϵͳ֪ͨ�����������ͼ��

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	// ��������ͼ

	CString strFileView;
	bNameValid = strFileView.LoadString(IDS_FILE_VIEW);
	ASSERT(bNameValid);
	if (!m_wndFileView.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ������ļ���ͼ������\n");
		return FALSE; // δ�ܴ���
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hFileViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndFileView.SetIcon(hFileViewIcon, FALSE);
	
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* ɨ��˵�*/);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// ���ཫִ�������Ĺ���

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// Ϊ�����û������������Զ��尴ť
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}

 LRESULT CMainFrame::OnNotifyIcon(WPARAM wparam, LPARAM lparam)
{
   if(lparam == WM_LBUTTONDOWN)
	{
        if(m_bMin == true)
         {
              AfxGetMainWnd()->ShowWindow(SW_SHOW);
              AfxGetMainWnd()->ShowWindow(SW_RESTORE);
              //����ò��ֻ��д����������ܱ�֤�ָ����ں󣬸ô��ڴ��ڻ״̬������ǰ�棩
              m_bMin = false;
         }
         else
         {
              AfxGetMainWnd()->ShowWindow(SW_MINIMIZE);
			  AfxGetMainWnd()->ShowWindow(SW_HIDE);
              m_bMin = true;
         }  
                         //������Ӷ�����������Ĵ������崦�����4��
    }
    else if(lparam == WM_RBUTTONDOWN)
    {
		CMenu popMenu;
        popMenu.LoadMenuW(IDR_NOTIFY_MENU);   //IDR_MENU_POPUP����ResourceView�д������༭��һ���˵�
        CMenu* pmenu = popMenu.GetSubMenu(0);   //�����Ĳ˵�ʵ������IDR_MENU_POPUP�˵���ĳ����Ӳ˵��������ǵ�һ��
        CPoint pos;
        GetCursorPos(&pos);            //�����˵���λ�ã�����������ĵ�ǰλ��
        //��ʾ�ò˵�����һ������������ֵ�ֱ��ʾ�������ұ���ʾ����Ӧ����һ�
        pmenu->TrackPopupMenu(TPM_RIGHTALIGN|TPM_RIGHTBUTTON, pos.x, pos.y, AfxGetMainWnd(), 0);  
                        //������Ӷ�����Ҽ�����Ĵ������崦�����5��
    }
    return 0;
 }

 void CMainFrame::OnDestroy()
 {
	 CFrameWndEx::OnDestroy();

	 // TODO: �ڴ˴������Ϣ����������
	 ::Shell_NotifyIcon(NIM_DELETE, &m_ntIcon);

 }


 void CMainFrame::OnSize(UINT nType, int cx, int cy)
 {
	 CFrameWndEx::OnSize(nType, cx, cy);

	 // TODO: �ڴ˴������Ϣ����������
	 if(nType==SIZE_MINIMIZED)
		 m_bMin=true;
	 else
		 m_bMin=false;
 }


 void CMainFrame::OnNotifyClose()
 {
	 // TODO: �ڴ���������������
	 //Call Close Function
	 CFrameWndEx::OnClose();
 }


 void CMainFrame::OnClose()
 {
	 // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	 int nres=MessageBox(L"ȷ��Ҫ�˳���\n���������С�������̣�",L"��ϣ��",MB_YESNOCANCEL|MB_ICONQUESTION);
	 switch(nres)
	 {
	 case IDYES:OnAppExit();break;
	 case IDNO:
		 {
			  AfxGetMainWnd()->ShowWindow(SW_MINIMIZE);
			  AfxGetMainWnd()->ShowWindow(SW_HIDE);
              m_bMin = true;
		 }break;
	 default:break;
	 }
	 //up
	//CFrameWndEx::OnClose();
 }


 void CMainFrame::OnAppExit()
 {
	 // TODO: �ڴ���������������

	 //up
	 CFrameWndEx::OnClose();
 }


 CVisibleManager* CMainFrame::GetVisibles(void)
 {
	 VManager.Init(m_wndFileView);
	 return &(VManager);
 }


 CIGisMapEditorView* CMainFrame::GetView(void)
 {
	 CIGisMapEditorView* pview=(CIGisMapEditorView*)(this->GetActiveView());
	 return pview;
 }

 void CMainFrame::OnCreatedb()
 {
	 // TODO: �ڴ���������������
	 CCreateDBDlg dlg;
	 if(IDOK==dlg.DoModal())
	 {
		MessageBox(L"�ɹ��������ݿ�",L"��ʾ",MB_ICONINFORMATION|MB_OK);
		 return;
	 }
 }

 void CMainFrame::OnSetdbconnect()
 {
	 // TODO: �ڴ���������������
	 CConnectDbDlg dlg;
	 dlg.pdb=&db;
	 if(IDOK==dlg.DoModal())
	 {
		 server=dlg.m_server;
		 dbname=dlg.m_name;
		 user=dlg.m_user;
		 code=dlg.m_pin;
//		 this->db.Open(this->server,this->dbname,this->user,this->code);
	 }
 }
 void CMainFrame::OnClearconnection()
 {
	 Disconn();
 }

 void CMainFrame::Disconn(bool nocall)
 {
	 // TODO: �ڴ���������������
	 if(!nocall)
	 {
		 int nres=MessageBox(L"ȷ����ֹ������",L"�Ͽ����ݿ�����",MB_YESNO|MB_ICONQUESTION);
		 if(nres==IDYES)
		 {
			 this->db.disConnection();
			server=dbname=user=code=L"";
		 }
	 }
	 else
	 {
		 if(db.isConnection())
			 this->db.disConnection();
			server=dbname=user=code=L"";
	 }
 }
 void CMainFrame::showXy(double x,double y)
 {
	 CString cx,cy;
	 cx.Format(L"X: %.6f",x);
	 cy.Format(L"Y: %.6f",y);
	 m_wndStatusBar.SetPaneText(1,cx,TRUE);
	 m_wndStatusBar.SetPaneText(2,cy,TRUE);
 }
 void CMainFrame::showStatus(int s)
 {
	 CString str=L"��ǰ״̬��	";
	 switch(s)
	 {
	 case 0:str+=L"��༭";break;
	 case 1:str+=L"�߱༭";break;
	 case 2:str+=L"���༭";break;
	 case 3:str+=L"ע�Ǳ༭";break;
	 default:str+=L"��ͨ/���";break;
	 }
	 m_wndStatusBar.SetPaneText(3,str,TRUE);
 }

 Layer* CMainFrame::GetEditingLayerPtr(void)
 {
	 return m_wndFileView.GetEditingPtr();
 }


 Basepic* CMainFrame::GetVisibleMapPtr(void)
 {
	 return m_wndFileView.GetViewpicPtr();
 }


 CFileView* CMainFrame::GetTree(void)
 {
	 return &m_wndFileView;
 }




 void CMainFrame::OnDeletetable()
 {
	 // TODO: �ڴ���������������
	 if(!db.isConnection())
	 {
		 AfxMessageBox(L"���ݿ�δ����");
	 }
	 else
	 {
		 CDeleteDlg g;
		 g.db=&db;
		 g.pView=&m_wndFileView;
		 if(IDOK==g.DoModal())
		 {
			 if(IDOK==MessageBox(L"ȷ��Ҫɾ��"+g.lname+L"��",L"ѯ��",MB_OKCANCEL|MB_ICONQUESTION))
			 db.DropTable(g.lname);
			 else
				 return ;
		 }
	 }
 }
