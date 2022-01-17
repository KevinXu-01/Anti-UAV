
// IRTagetRecSysView.h : CIRTagetRecSysView ��Ľӿ�
//

#include "TrackWnd.h"
#include "TrackCtrlDlg.h"


//Dalsa CameraLinkͼ��ɼ���֧��
#include "SapClassBasic.h"
//#include "SapClassGui.h"
#pragma comment(lib,"SapClassBasic.lib")
//#pragma comment(lib,"SapClassGui.lib")
#pragma once


//�ɼ�����������////////////////////////////////////////////////////////////////////////////////////////
#define MAXBUFFNUM  10

class CIRTagetRecSysView : public CView
{
protected: // �������л�����
	CIRTagetRecSysView();
	DECLARE_DYNCREATE(CIRTagetRecSysView)

// ���ԣ����ڱ���
public:
	CTrackWnd         m_wndTrack;  //����ͼ����ʾ��
	CMFCTabCtrl       m_wndCtrlTab;      //����Tab����
 	CTrackCtrlDlg     m_dlgTrackCtrl;    //����ҳ��

//���ԣ���־����
public:
	BYTE            m_bRunning;
	double          m_fCapFrameTime;    //֡��Ӧʱ��

//���ԣ�ͼ�����
public:
	//IRͼ�񻺳���
	UINT   m_nCurIRCaptureNo;
	BYTE*  m_pbyIrBuffs[MAXBUFFNUM]; //����8bit���ݣ�MAXBUFFNUM֡��640*512
	BYTE*  m_pbyIr;            //����8bit���ݣ���֡���Ѵ�ֱ����

	//RGBͼ�񻺳���
	UINT   m_nCurRGBCaptureNo;
	BYTE*  m_pbyRGBBuffs[MAXBUFFNUM]; //����8bit���ݣ�MAXBUFFNUM֡��640*480
	BYTE*  m_pbyRGB; 




public:
#ifndef HARDWARE_OK
	static ULONG WINAPI IRCapThread(PVOID);//��������ɼ��̣߳���Ӳ��ʱģ�⣩
#endif
	static ULONG WINAPI IRProcessThread(PVOID);//�㷨����ʾ�����Զ����߳�
	static ULONG WINAPI RECVMessage(PVOID);
	static void  IRCapCallback(SapXferCallbackInfo *pInfo);
	static void  RGBCapCallback(SapXferCallbackInfo *pInfo);
public:
	void SetWndSize();

	//Dalsa CameraLink����ɼ���Ӳ������++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	bool            m_bIRChanLinkOk;
	SapAcquisition* m_pSapAcqIR;     //Track�ӿڲɼ����
	SapBuffer*      m_pBuffersIR;    //Track�ӿڲɼ�buffer
	SapTransfer*    m_pXferIR;       //Track�ӿڴ�����
	static void     SignalCallbackIR(SapAcqCallbackInfo *pInfo);

    bool            m_bRGBChanLinkOk;
	SapAcquisition* m_pSapAcqRGB;     //Track�ӿڲɼ����
	SapBuffer*      m_pBuffersRGB;    //Track�ӿڲɼ�buffer
	SapTransfer*    m_pXferRGB;       //Track�ӿڴ�����
	static void     SignalCallbackRGB(SapAcqCallbackInfo *pInfo);

	
	BOOL            InitSapCom(CString strIRConfig,CString strRGBConfig);
	BOOL            CreateSapObjects(); //�������
	BOOL            DestroySapObjects();//���پ��
	void            GetSignalStatus();  //��ȡ����״̬

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CIRTagetRecSysView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	void DrawSearchRuler();

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	BOOL   m_bExe;
	//afx_msg LRESULT  PyMeaasgeFun(WPARAM wParam, LPARAM lParam);
	//void pyfunc(void* imgBuff);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void ButtonCMD();
	afx_msg LRESULT  TrackCMDMessage(WPARAM wParam, LPARAM lParam);
};

#ifndef _DEBUG  // IRTagetRecSysView.cpp �еĵ��԰汾
inline CIRTagetRecSysDoc* CIRTagetRecSysView::GetDocument() const
   { return reinterpret_cast<CIRTagetRecSysDoc*>(m_pDocument); }
#endif



