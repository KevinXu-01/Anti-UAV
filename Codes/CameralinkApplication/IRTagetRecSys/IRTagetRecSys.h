
// IRTagetRecSys.h : IRTagetRecSys Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CIRTagetRecSysApp:
// �йش����ʵ�֣������ IRTagetRecSys.cpp
//

class CIRTagetRecSysApp : public CWinAppEx
{
public:
	CIRTagetRecSysApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CIRTagetRecSysApp theApp;
