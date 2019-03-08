
// IGisMapEditorDoc.h : CIGisMapEditorDoc ��Ľӿ�
//


#pragma once

class CFileView;
class CMainFrame;
class CIGisMapEditorView;

class CIGisMapEditorDoc : public CDocument
{
protected: // �������л�����
	CIGisMapEditorDoc();
	DECLARE_DYNCREATE(CIGisMapEditorDoc)

// ����
public:

// ����
public:
	CMainFrame* GetMain();
	CIGisMapEditorView* GetView(void);
// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CIGisMapEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CString spn;
	CString opn;
// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
};
