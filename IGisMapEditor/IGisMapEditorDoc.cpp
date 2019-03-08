
// IGisMapEditorDoc.cpp : CIGisMapEditorDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "IGisMapEditor.h"
#endif

#include "IGisMapEditorDoc.h"

#include "FileView.h"
#include "MainFrm.h"
#include "IGisMapEditorView.h"
#include <locale>

using namespace std;
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CIGisMapEditorDoc

IMPLEMENT_DYNCREATE(CIGisMapEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CIGisMapEditorDoc, CDocument)
	ON_COMMAND(ID_FILE_NEW, &CIGisMapEditorDoc::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CIGisMapEditorDoc::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CIGisMapEditorDoc::OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, &CIGisMapEditorDoc::OnFileSaveAs)
END_MESSAGE_MAP()


// CIGisMapEditorDoc ����/����

CIGisMapEditorDoc::CIGisMapEditorDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CIGisMapEditorDoc::~CIGisMapEditorDoc()
{
}

BOOL CIGisMapEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}

CMainFrame* CIGisMapEditorDoc::GetMain()
{
	CMainFrame* pmain=(CMainFrame*)AfxGetMainWnd();
	return pmain;
}
CIGisMapEditorView* CIGisMapEditorDoc::GetView(void)
{
		CIGisMapEditorView* pview=(CIGisMapEditorView*)(this->GetMain()->GetActiveView());
		return pview;
}


// CIGisMapEditorDoc ���л�

void CIGisMapEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CIGisMapEditorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CIGisMapEditorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CIGisMapEditorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CIGisMapEditorDoc ���

#ifdef _DEBUG
void CIGisMapEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CIGisMapEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CIGisMapEditorDoc ����


void CIGisMapEditorDoc::OnFileNew()
{
	// TODO: �ڴ���������������
	CFileView* pf=GetMain()->GetTree();
	if(pf->thelayers.size()>0||pf->thepics.size()>0)
	{
		int mmm=AfxMessageBox(L"�������ڵĹ�����",MB_YESNOCANCEL|MB_ICONQUESTION);
		if(IDYES==mmm)
		{
			OnFileSave();
			pf->RemoveAll(false);
		}
		else if(mmm==IDNO)
		{
			pf->RemoveAll(false);
		}
		else
		{;
		}
	}
	else
	{
		;
	}
}


void CIGisMapEditorDoc::OnFileOpen()
{
	// TODO: �ڴ���������������
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );    setlocale( LC_CTYPE, "chs" );
	OnFileNew();
	CFileDialog g(TRUE);
	g.m_ofn.lpstrTitle=L"��";
	g.m_ofn.lpstrDefExt=L"igp";
	g.m_ofn.lpstrFilter=L"IGis project(*.igp)\0*.igp\0\0";
	if(IDOK==g.DoModal())//f.WriteString((LPCTSTR)(m_server+L"\n"));
	{
		opn=g.GetPathName();
		CStdioFile f;
		f.Open(opn,CFile::modeRead);
		CFileView* pf=GetMain()->GetTree();
		int np;//=pf->thepics.size();
		int nl;//=pf->thelayers.size();
		CString temp;
		//temp.Format(L"%d",np);
		f.ReadString(temp);
		np=strtoi(temp);
		//Basepic* p;
		int i=0;
		while(i<np)
		{
			//p=pf->thepics.PicPtr(i);
			double ltx,lty,rbx,rby;
			f.ReadString(temp);
			CString s=temp;
			f.ReadString(temp);
			ltx=strtof(temp);
			f.ReadString(temp);
			lty=strtof(temp);
			f.ReadString(temp);
			rbx=strtof(temp);
			f.ReadString(temp);
			rby=strtof(temp);
			pf->addBmpEx(s,ltx,lty,rbx,rby);
			i++;
		}
		f.ReadString(temp);
		nl=strtoi(temp);
		CString server,dbname;
		f.ReadString(server);
		f.ReadString(dbname);
		if(!(GetMain()->db.isConnection())||GetMain()->dbname!=dbname||GetMain()->server!=server)
		{
			AfxMessageBox(L"�����ӵ����ݿ�"+dbname+L"(������:"+server+L")");
			if(GetMain()->db.isConnection())
			{AfxMessageBox(L"��Ͽ�����");GetMain()->Disconn(true);}
			GetMain()->OnSetdbconnect();
		}
		//Layer *q;
		if(GetMain()->db.isConnection()&&GetMain()->server==server&&GetMain()->dbname==dbname)
		{
			i=0;
			while(i<nl)
			{
				//q=pf->thelayers.LayerPtr(i);
				//f.WriteString((LPCTSTR)(q->GetName()+L"\n"));	
				CString temp2;
				f.ReadString(temp2);
				pf->addLayerEx(temp2,server,dbname,GetMain()->user,GetMain()->code);
				i++;
			}
			f.Close();
			
		}
		else
		{
			AfxMessageBox(L"�޷���ͼ��");
		}
	spn=opn;
	}
	setlocale( LC_CTYPE, old_locale );    free( old_locale );//
}


void CIGisMapEditorDoc::OnFileSave()
{
	// TODO: �ڴ���������������
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );    setlocale( LC_CTYPE, "chs" );
	if(spn!=L"")
	{
		
		CStdioFile f;
		CFileFind ff;
		if(ff.FindFile(spn)==TRUE)
		{CFile::Remove(spn);}
		f.Open(spn,CFile::modeCreate|CFile::modeWrite);
		CFileView* pf=GetMain()->GetTree();
		int np=pf->thepics.size();
		int nl=pf->thelayers.size();
		CString temp;
		temp.Format(L"%d",np);
		f.WriteString((LPCTSTR)(temp+L"\n"));
		Basepic* p;int i=0;
		while(i<np)
		{
			p=pf->thepics.PicPtr(i);
			f.WriteString((LPCTSTR)(p->GetName()+L"\n"));
			temp.Format(L"%f",p->ltx);
			f.WriteString((LPCTSTR)(temp+L"\n"));
			temp.Format(L"%f",p->lty);
			f.WriteString((LPCTSTR)(temp+L"\n"));
			temp.Format(L"%f",p->rbx);
			f.WriteString((LPCTSTR)(temp+L"\n"));
			temp.Format(L"%f",p->rby);
			f.WriteString((LPCTSTR)(temp+L"\n"));			
			i++;
		}
		temp.Format(L"%d",nl);
		f.WriteString((LPCTSTR)(temp+L"\n"));
		f.WriteString((LPCTSTR)(GetMain()->server+L"\n"));
		f.WriteString((LPCTSTR)(GetMain()->dbname+L"\n"));
		Layer *q;i=0;
		while(i<nl)
		{
			q=pf->thelayers.LayerPtr(i);
			f.WriteString((LPCTSTR)(q->GetName()+L"\n"));			
			i++;
		}
		f.Close();
	}
	else
	{
		OnFileSaveAs();
	}
	setlocale( LC_CTYPE, old_locale );    free( old_locale );//
}


void CIGisMapEditorDoc::OnFileSaveAs()
{
	// TODO: �ڴ���������������
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );    setlocale( LC_CTYPE, "chs" );
	CFileDialog g(FALSE);
	g.m_ofn.lpstrTitle=L"���Ϊ";
	g.m_ofn.lpstrDefExt=L"igp";
	g.m_ofn.lpstrFilter=L"IGis project(*.igp)\0*.igp\0\0";
	if(IDOK==g.DoModal())//f.WriteString((LPCTSTR)(m_server+L"\n"));
	{
		spn=g.GetPathName();
		CStdioFile f;
		CFileFind ff;
		if(ff.FindFile(spn)==TRUE)
		{CFile::Remove(spn);}
		f.Open(spn,CFile::modeCreate|CFile::modeWrite);
		CFileView* pf=GetMain()->GetTree();
		int np=pf->thepics.size();
		int nl=pf->thelayers.size();
		CString temp;
		temp.Format(L"%d",np);
		f.WriteString((LPCTSTR)(temp+L"\n"));
		Basepic* p;int i=0;
		while(i<np)
		{
			p=pf->thepics.PicPtr(i);
			f.WriteString((LPCTSTR)(p->GetName()+L"\n"));
			temp.Format(L"%f",p->ltx);
			f.WriteString((LPCTSTR)(temp+L"\n"));
			temp.Format(L"%f",p->lty);
			f.WriteString((LPCTSTR)(temp+L"\n"));
			temp.Format(L"%f",p->rbx);
			f.WriteString((LPCTSTR)(temp+L"\n"));
			temp.Format(L"%f",p->rby);
			f.WriteString((LPCTSTR)(temp+L"\n"));			
			i++;
		}
		temp.Format(L"%d",nl);
		f.WriteString((LPCTSTR)(temp+L"\n"));
		f.WriteString((LPCTSTR)(GetMain()->server+L"\n"));
		f.WriteString((LPCTSTR)(GetMain()->dbname+L"\n"));
		Layer *q;i=0;
		while(i<nl)
		{
			q=pf->thelayers.LayerPtr(i);
			f.WriteString((LPCTSTR)(q->GetName()+L"\n"));			
			i++;
		}
		f.Close();
	}
	setlocale( LC_CTYPE, old_locale );    free( old_locale );//
}
