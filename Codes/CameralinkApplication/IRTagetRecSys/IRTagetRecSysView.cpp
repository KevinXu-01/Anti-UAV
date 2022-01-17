
// RGBTagetRecSysView.cpp : CIRTagetRecSysView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "IRTagetRecSys.h"
			#endif
#include "IRTagetRecSysDoc.h"
#include "IRTagetRecSysView.h"
#include "DetectTrack.h"
//#include <Python.h>
#include <iostream>
#include <WinSock2.h>

#pragma comment(lib,"ws2_32.lib")
#include <opencv2/opencv.hpp>
#include <core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define OPENCVMESSAGE WM_USER+100

using namespace std;
int udpEndSignal(char ipAddr[] , int Port);
// CIRTagetRecSysView

//���嶯̬ȫ�ֵ�DetectTrack
//static DroneTrack* drone_det = new DroneTrack;
//���� �ṹ��
GFKDTrackCMD trackCMD;
BOOL g_bOccupied = FALSE;

//����ָ��
BYTE *IMGData = NULL;

IMPLEMENT_DYNCREATE(CIRTagetRecSysView, CView)

BEGIN_MESSAGE_MAP(CIRTagetRecSysView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//ON_MESSAGE(OPENCVMESSAGE,PyMeaasgeFun)
	ON_MESSAGE(OPENCVMESSAGE,TrackCMDMessage)
END_MESSAGE_MAP()

// CIRTagetRecSysView ����/����

/*
void CIRTagetRecSysView::ButtonCMD()
{	
		CIRTagetRecSysView* pView = (CIRTagetRecSysView*)(GetParent()->GetParent());
#ifdef HARDWARE_OK
	if(trackCMD.bIrOrCCD == 1){
		pView->m_wndTrack.m_dibBMP.DeleteObject();
		pView->m_wndTrack.m_nImageWidth  =IR_IMAGE_COLS;  //����ͼ����ʾ���
		pView->m_wndTrack.m_nImageHeight =IR_IMAGE_ROWS;  //����ͼ����ʾ�߶�
		pView->m_wndTrack.m_dibBMP.CreateDIB(pView->m_wndTrack.m_nImageWidth,pView->m_wndTrack.m_nImageHeight,0,8);
	}
	else{
		pView->m_wndTrack.m_dibBMP.DeleteObject();
		pView->m_wndTrack.m_nImageWidth  =RGB_IMAGE_COLS;  //����ͼ����ʾ���
		pView->m_wndTrack.m_nImageHeight =RGB_IMAGE_ROWS;  //����ͼ����ʾ�߶�
		pView->m_wndTrack.m_dibBMP.CreateDIB(pView->m_wndTrack.m_nImageWidth,pView->m_wndTrack.m_nImageHeight,0,24);
	}
#endif

	if (!trackCMD.bStartOrStop)//�˳�����
	{   
#ifdef HARDWARE_OK	
		if(((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck())
		{
			pView->m_pXferIR->Freeze();	
		}
		else
		{
			pView->m_pXferRGB->Freeze();	
		}
#endif
		//GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
		//GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
		pView->m_bRunning =FALSE;
		//SetDlgItemText(IDC_BTN_WORK,"��ʼ����");
	}
	else //��ʼ����
	{
#ifdef HARDWARE_OK	
		//CameraLink�ɼ�������ͨ�������ɼ�
		//UDP Э�����
		if(trackCMD.bIrOrCCD == 1)
		{
			pView->m_pXferIR->Grab();	
		}
		else //if(trackCMD.bIrOrCCD == 2)
		{
			pView->m_pXferRGB->Grab();	
		}
#endif
		//GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
		//GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
		
		//SetDlgItemText(IDC_BTN_WORK,"ֹͣ����");
		//pView->m_wndCtrlTab.SetActiveTab(0);
		//Sleep(500);
		
		pView->m_bExe=FALSE;
		pView->m_bRunning =TRUE;	
	}
}
//*/

void CIRTagetRecSysView::ButtonCMD()
{
	CIRTagetRecSysView* pView = (CIRTagetRecSysView*)(GetParent()->GetParent());
	CString strText; 
	GetDlgItemText(IDC_BTN_WORK,strText);
	pView->GetParent()->SetWindowText("����Ŀ�����ʶ��ϵͳ - CETC");

	if (!trackCMD.bStartOrStop)//�˳�����
	{   
#ifdef HARDWARE_OK	
		if(((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck())
		{
	
			pView->m_pXferIR->Freeze();	
		}
		else
		{
			pView->m_pXferRGB->Freeze();	
		}
#endif
		GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
		pView->m_bRunning =FALSE;
		SetDlgItemText(IDC_BTN_WORK,"��ʼ����");
	}
	else //��ʼ����
	{
#ifdef HARDWARE_OK	
		//CameraLink�ɼ�������ͨ�������ɼ�
		//if(trackCMD==0)
		//UDP Э�����
		if(trackCMD.bIrOrCCD == 1)
		{
			pView->m_pXferIR->Grab();	
		}
		else //if(trackCMD.bIrOrCCD == 2)
		{
			pView->m_pXferRGB->Grab();	
		}
#endif
		GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
		
		SetDlgItemText(IDC_BTN_WORK,"ֹͣ����");
		pView->m_wndCtrlTab.SetActiveTab(0);
		//Sleep(500);
		
		pView->m_bExe=FALSE;
		pView->m_bRunning =TRUE;	
	}
}
CIRTagetRecSysView::CIRTagetRecSysView()
{
	// TODO: �ڴ˴���ӹ������
	m_fCapFrameTime=0.0;
	m_bRunning =FALSE;
	m_bExe = FALSE;
	m_pSapAcqIR  = NULL;
	m_pXferIR    = NULL;
	m_pBuffersIR = NULL;
	m_bIRChanLinkOk =false;


	m_pSapAcqRGB  = NULL;
	m_pXferRGB    = NULL;
	m_pBuffersRGB = NULL;
	m_bRGBChanLinkOk =false;
}

CIRTagetRecSysView::~CIRTagetRecSysView()
{
}

BOOL CIRTagetRecSysView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	//cs.style   &=~WS_BORDER;
	return CView::PreCreateWindow(cs);
}

// CIRTagetRecSysView ����

void CIRTagetRecSysView::OnDraw(CDC* /*pDC*/)
{
	
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}
// CIRTagetRecSysView ���

#ifdef _DEBUG
void CIRTagetRecSysView::AssertValid() const
{
	CView::AssertValid();
}

void CIRTagetRecSysView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

// CIRTagetRecSysView ��Ϣ�������
void CIRTagetRecSysView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	SetWndSize();

}
void CIRTagetRecSysView::SetWndSize()
{
	CRect rect;
	GetClientRect(rect);
	if (m_wndTrack.m_hWnd)
	{		
		int nTrackWndHeight =rect.bottom-4;
		int nTrackWndWidth = int(nTrackWndHeight*1.333);
		m_wndTrack.SetWindowPos(NULL,rect.left,2,nTrackWndWidth,nTrackWndHeight,SWP_NOACTIVATE | SWP_NOZORDER);	
		m_wndCtrlTab.SetWindowPos(NULL,rect.left+nTrackWndWidth+2,2,rect.right-nTrackWndWidth-4,nTrackWndHeight,SWP_NOACTIVATE | SWP_NOZORDER);	

	}
}
BOOL CIRTagetRecSysView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(0,0,rect.right,rect.bottom,RGB(0,110,0));

	CString strText;
	pDC->SetBkMode(TRANSPARENT);	
	pDC->SetTextColor(RGB(168,168,168));

	return TRUE;// CView::OnEraseBkgnd(pDC);
}
int CIRTagetRecSysView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here	
	//����ͼ���ڴ滺�������ڴ���䰴��С�ӳ�(120000)�Ŀ���һ�ο���λ
	m_pbyIr       =new BYTE[IR_IMAGE_COLS*IR_IMAGE_ROWS];    
	m_pbyRGB      =new BYTE[RGB_IMAGE_COLS*RGB_IMAGE_ROWS*3];
	for(int i=0;i<2;i++)//ֻ����ǰ2���ڴ���
	{
		m_pbyIrBuffs[i]  = new BYTE[IR_IMAGE_COLS*IR_IMAGE_ROWS];   
		if (m_pbyIrBuffs[i]==NULL)
		{
			MessageBox("�ڴ����ʧ�ܣ�",_T("��ʾ"),MB_OK|MB_ICONWARNING);
		}

		m_pbyRGBBuffs[i]  = new BYTE[RGB_IMAGE_COLS*RGB_IMAGE_ROWS*3];  
		if (m_pbyRGBBuffs[i]==NULL)
		{
			MessageBox("�ڴ����ʧ�ܣ�",_T("��ʾ"),MB_OK|MB_ICONWARNING);
		}
	}
	for(int i=2;i<MAXBUFFNUM;i++)//����Ļ��������ٷ����ڴ棬��ǰ2������
	{
		m_pbyIrBuffs[i]  = m_pbyIrBuffs[i%2];
		m_pbyRGBBuffs[i]  =m_pbyRGBBuffs[i%2];
	}
	m_nCurIRCaptureNo=0;
	m_nCurRGBCaptureNo=0;

	m_wndTrack.Create(NULL, _T(""), WS_CHILD | WS_VISIBLE, CRect(0,0,0,0), this, 3);
	m_wndCtrlTab.Create(CMFCTabCtrl::STYLE_3D_ONENOTE,CRect(0,0,0,0), this, 0,CMFCTabCtrl::LOCATION_TOP, FALSE);
	m_wndCtrlTab.EnableAutoColor (FALSE);
	m_wndCtrlTab.EnableTabSwap(FALSE);//�������ƶ�Tab֮��λ��
	m_dlgTrackCtrl.Create(IDD_TRACKCTRL,&m_wndCtrlTab);
	m_wndCtrlTab.AddTab(&m_dlgTrackCtrl,"���ٿ���",0, FALSE);

	return 0;
}

//׷����Ϣ
/*
void CIRTagetRecSysView::pyfunc(void* imgBuff)
{
	//�ɼ���
	//if(m_dlgTrackCtrl.m_byImageType==1)
	if(trackCMD.bIrOrCCD == 2)
	{
		npy_intp Dim[3] = {IMG_RGB_HEIGHT, IMG_RGB_WIDTH, 3};
		drone_det->pMat = PyArray_SimpleNewFromData(3, Dim, NPY_UBYTE, imgBuff);
		PyTuple_SetItem(drone_det->pArgs,0, drone_det->pMat);   
		PyObject_CallObject(drone_det->pFunc, drone_det->pArgs);
	}
	//����ͼ��
	else
	{
		npy_intp Dim[2] = {IMG_IR_HEIGHT, IMG_IR_WIDTH};
		drone_det->pMat = PyArray_SimpleNewFromData(2, Dim, NPY_UBYTE, imgBuff);
		PyTuple_SetItem(drone_det->pArgs,0, drone_det->pMat);   
		PyObject_CallObject(drone_det->pFunc, drone_det->pArgs);
	}

}
*/
/*
LRESULT  CIRTagetRecSysView::PyMeaasgeFun(WPARAM wParam, LPARAM lParam)
{
	m_bExe =TRUE;
	//....
	//pyfunc((void*)IMGData);
	//ButtonCMD();
	m_bExe =FALSE;
	return 0;
}
*/
LRESULT  CIRTagetRecSysView::TrackCMDMessage(WPARAM wParam, LPARAM lParam)
{
	ButtonCMD();
	//pyfunc((void*)IMGData);
	return 0;
}//*/

void CIRTagetRecSysView::OnInitialUpdate()
{

	CView::OnInitialUpdate();
	/*
	Py_SetPythonHome(L"C:\\Users\\aaa\\Anaconda3");
	Py_Initialize();
	//PyEval_InitThreads();
	import_array();
	drone_det->pModule = PyImport_ImportModule("detective2_vs_test2");
	drone_det->pDict = PyModule_GetDict(drone_det->pModule);
	drone_det->pFunc = PyDict_GetItemString(drone_det->pDict, "global_init");
	PyObject_CallObject(drone_det->pFunc, NULL);
	drone_det->pFunc = PyDict_GetItemString(drone_det->pDict, "recvimg1");
	drone_det->pArgs = PyTuple_New(1);
	*/
	// TODO: Add your specialized code here and/or call the base class
#ifdef HARDWARE_OK
	//��ʼ��������Camera�ɼ���,ע����漸��˳���ܷ�
	CString strConfigSearch;
	if(!InitSapCom(IR_CONFIG_FILENAME,RGB_CONFIG_FILENAME))
	{
		MessageBox("���������ǲɼ���ʧ�ܣ�",_T("��ʾ"),MB_OK|MB_ICONWARNING);
	}
	//����ͼ��ɼ��ص�����
	m_pXferIR  = new SapAcqToBuf(m_pSapAcqIR, m_pBuffersIR, IRCapCallback, this);//IR�ɼ��ӿڻص�; 
	m_pXferRGB  = new SapAcqToBuf(m_pSapAcqRGB, m_pBuffersRGB, RGBCapCallback, this);//RGB�ɼ��ӿڻص�; 
	if (!CreateSapObjects())//����CL�ɼ��������Դ
	{  
		MessageBox("���������ǲɼ���ʧ�ܣ�",_T("��ʾ"),MB_OK|MB_ICONWARNING);
		return; 
	}

	//end

#endif
	//������������߳�
#ifndef HARDWARE_OK
	//��������ɼ��߳�
	::CreateThread (NULL, 0, IRCapThread, this, NULL, NULL);
#endif
	//�������������߳�
	::CreateThread (NULL, 0, RECVMessage, this, NULL, NULL);
	//�����������߳�

	::CreateThread (NULL, 0, IRProcessThread, this, NULL, NULL);

	//////
// 	trackCMD.bIrOrCCD = 1;
// 	trackCMD.bStartOrStop = 1;
}
//��ʼ��CL�ɼ���,���زɼ�������
BOOL CIRTagetRecSysView::InitSapCom(CString strIRConfig,CString strRGBConfig)
{
	DestroySapObjects();
	
	//��ȡ��ǰ.exe�ļ�����Ŀ¼
	CHAR   FullPath[MAX_PATH];
	CString strMainDir;
	GetModuleFileName(NULL,FullPath,MAX_PATH); 
	strMainDir = (CString)FullPath; 
	int position = strMainDir.ReverseFind('\\'); 
	strMainDir  = strMainDir.Left(position); 

	//IRģʽ,���ö˿�2ͼ��
	strIRConfig= strMainDir+strIRConfig;//�����ļ�2

	SapLocation loc("Xcelera-CL_PX4_1",1);//�˿�2
	SapAcquisition IRAcq;
	IRAcq.SetLocation(loc);
	IRAcq.SetConfigFile(strIRConfig);
	m_pSapAcqIR  = new SapAcquisition(IRAcq);
	m_pBuffersIR = new SapBufferWithTrash(2,m_pSapAcqIR,SapBuffer::TypeScatterGather);//����������Ϣ����IR�ɼ�ͨ��buffer;

	//RGBģʽ,���ö˿�1ͼ��
	strRGBConfig= strMainDir+strRGBConfig;//�����ļ�1
	SapLocation loc2("Xcelera-CL_PX4_1",0);//�˿�1
	SapAcquisition RGBAcq;
	RGBAcq.SetLocation(loc2);
	RGBAcq.SetConfigFile(strRGBConfig);
	m_pSapAcqRGB  = new SapAcquisition(RGBAcq);
	m_pBuffersRGB = new SapBufferWithTrash(2,m_pSapAcqRGB,SapBuffer::TypeScatterGather);//����������Ϣ����RGB�ɼ�ͨ��buffer;

	//GetSignalStatus();   //�õ���ǰ�ź�״̬;
	return TRUE;
}
void CIRTagetRecSysView::GetSignalStatus()
{
	SapAcquisition::SignalStatus signalStatus;
	if (m_pSapAcqIR)
	{
		if(m_pSapAcqIR->IsSignalStatusAvailable())
		{
			m_pSapAcqIR->GetSignalStatus(&signalStatus, SignalCallbackIR, this);//�����ź�1״̬�ص�;
		}	
	}
	if (m_pSapAcqRGB)
	{
		if(m_pSapAcqRGB->IsSignalStatusAvailable())
		{
			m_pSapAcqRGB->GetSignalStatus(&signalStatus, SignalCallbackRGB, this);//�����ź�1״̬�ص�;
		}	
	}
}
void CIRTagetRecSysView::SignalCallbackIR(SapAcqCallbackInfo *pInfo)
{
	CIRTagetRecSysView *pView = (CIRTagetRecSysView *) pInfo->GetContext();
	SapAcquisition::SignalStatus signalStatus = pInfo->GetSignalStatus();
	//pView->m_bIRChanLinkOk =(signalStatus != SapAcquisition::SignalNone);
}
void CIRTagetRecSysView::SignalCallbackRGB(SapAcqCallbackInfo *pInfo)
{
	CIRTagetRecSysView *pView = (CIRTagetRecSysView *) pInfo->GetContext();
	SapAcquisition::SignalStatus signalStatus = pInfo->GetSignalStatus();
	//pView->m_bRGBChanLinkOk =(signalStatus != SapAcquisition::SignalNone);
}

BOOL CIRTagetRecSysView::CreateSapObjects()
{
	CWaitCursor wait;

	//�ɼ����ӿ�1
	// Create acquisition object 
	if (m_pSapAcqIR && !*m_pSapAcqIR && !m_pSapAcqIR->Create())
	{
		DestroySapObjects();//�ͷ���Դ
		return FALSE;
	}
	// Create buffer object
	if (m_pBuffersIR&& !*m_pBuffersIR && !m_pBuffersIR->Create())
	{
		DestroySapObjects();
		return FALSE;
	}
	// Create transfer object
	if (m_pXferIR && !*m_pXferIR && !m_pXferIR->Create())
	{
		DestroySapObjects();
		return FALSE;
	}
		//�ɼ����ӿ�2
	// Create acquisition object 
	if (m_pSapAcqRGB && !*m_pSapAcqRGB && !m_pSapAcqRGB->Create())
	{
		DestroySapObjects();//�ͷ���Դ
		return FALSE;
	}
	// Create buffer object
	if (m_pBuffersRGB&& !*m_pBuffersRGB && !m_pBuffersRGB->Create())
	{
		DestroySapObjects();
		return FALSE;
	}
	// Create transfer object
	if (m_pXferRGB && !*m_pXferRGB && !m_pXferRGB->Create())
	{
		DestroySapObjects();
		return FALSE;
	}
	return TRUE;
}
BOOL CIRTagetRecSysView::DestroySapObjects()  
{
	if (m_pXferIR && *m_pXferIR) 
	{
		m_pXferIR->Destroy();
		m_pXferIR=NULL;
	}
	if (m_pBuffersIR && *m_pBuffersIR) 
	{
		m_pBuffersIR->Destroy();
		m_pBuffersIR=NULL;
	}
	if (m_pSapAcqIR && *m_pSapAcqIR)
	{
		m_pSapAcqIR->Destroy();
		m_pSapAcqIR=NULL;
	}

	if (m_pXferRGB && *m_pXferRGB) 
	{
		m_pXferRGB->Destroy();
		m_pXferRGB=NULL;
	}
	if (m_pBuffersRGB && *m_pBuffersRGB) 
	{
		m_pBuffersRGB->Destroy();
		m_pBuffersRGB=NULL;
	}
	if (m_pSapAcqRGB && *m_pSapAcqRGB)
	{
		m_pSapAcqRGB->Destroy();
		m_pSapAcqRGB=NULL;
	}
	return TRUE;
}
//IR�ɼ�ͨ���ص�����
void CIRTagetRecSysView::IRCapCallback(SapXferCallbackInfo *pInfo)
{	
	CIRTagetRecSysView *pView= (CIRTagetRecSysView*) pInfo->GetContext();
	//static int frame_num = 0;
	//�ص�ץȡ����
	if (pInfo->IsTrash())
	{
		CString str;
		str.Format("Number of missed frames : %d", pInfo->GetEventCount());
		//AfxMessageBox("XferCallback1");
	}
	else
	{
		//ץȡ��һ֡IRͼ��������
		BYTE* pbyIRImgBuffer=NULL;
		pView->m_pBuffersIR->GetAddress((void**)&pbyIRImgBuffer);//��òɼ��ӿ�1��ͼ�񻺳���ָ��
		
		//����
		memcpy(pView->m_pbyIrBuffs[pView->m_nCurIRCaptureNo],pbyIRImgBuffer, IR_IMAGE_COLS*IR_IMAGE_ROWS);

		static int startTime = GetTickCount();
		int endTime = GetTickCount();
		pView->m_fCapFrameTime = (endTime-startTime);	
		startTime =endTime;
		if (pView->m_nCurIRCaptureNo==(MAXBUFFNUM-1))
		{
		    pView->m_nCurIRCaptureNo=0;
	   	}
		else
		{
			pView->m_nCurIRCaptureNo++;
		}	
		pView->m_nCurRGBCaptureNo=0;
	}
}
//RGB�ɼ�ͨ���ص�����
void CIRTagetRecSysView::RGBCapCallback(SapXferCallbackInfo *pInfo)
{	
	CIRTagetRecSysView *pView= (CIRTagetRecSysView*) pInfo->GetContext();
	//static int frame_num = 0;
	if (pInfo->IsTrash())
	{
		CString str;
		str.Format("Number of missed frames : %d", pInfo->GetEventCount());
		//AfxMessageBox("XferCallback1");
	}
	else
	{
		//ץȡ��һ֡yuvͼ��������
		BYTE* pbyYUV422ImgBuffer=NULL;
		pView->m_pBuffersRGB->GetAddress((void**)&pbyYUV422ImgBuffer);//��òɼ��ӿ�2��ͼ�񻺳���ָ��
		
		BYTE* pbyRGB=pView->m_pbyRGBBuffs[pView->m_nCurRGBCaptureNo];
		for(int i=0;i<RGB_IMAGE_COLS*RGB_IMAGE_ROWS/2;i++)
		{
			BYTE  Y0 = pbyYUV422ImgBuffer[4*i];
			BYTE  Cr =  pbyYUV422ImgBuffer[4*i+1];
			BYTE  Y1 = pbyYUV422ImgBuffer[4*i+2];
			BYTE  Cb =  pbyYUV422ImgBuffer[4*i+3];		
			
			//pixel1
			double r=1.164*(Y0-16) +1.596*(Cr-128);//R;
			pbyRGB[3*(2*i)+2]=r;
			if(r>=255.0)
			{
				pbyRGB[3*(2*i)+2]=255;
			}
			else if(r<=0.0)
			{
				pbyRGB[3*(2*i)+2]=0;
			}
			double g=1.164*(Y0-16) -0.813*(Cr-128)-0.392*(Cb-128);//G
			pbyRGB[3*(2*i)+1]=g;
		    if(g>=255.0)
			{
				pbyRGB[3*(2*i)+1]=255;
			}
			else if(g<=0.0)
			{
				pbyRGB[3*(2*i)+1]=0;
			}
			double b= 1.164*(Y0-16)+2.017*(Cb-128);//B
			pbyRGB[3*(2*i)]=b;
		    if(b>=255.0)
			{
				pbyRGB[3*(2*i)]=255;
			}
			else if(b<=0.0)
			{
				pbyRGB[3*(2*i)]=0;
			}

			//pixel2
			r=1.164*(Y1-16) +1.596*(Cr-128);//R;
			pbyRGB[3*(2*i+1)+2]=r;
			if(r>=255.0)
			{
				pbyRGB[3*(2*i+1)+2]=255;
			}
			else if(r<=0.0)
			{
				pbyRGB[3*(2*i+1)+2]=0;
			}
			g=1.164*(Y1-16) -0.813*(Cr-128)-0.392*(Cb-128);//G
			pbyRGB[3*(2*i+1)+1]=g;
		    if(g>=255.0)
			{
				pbyRGB[3*(2*i+1)+1]=255;
			}
			else if(g<=0.0)
			{
				pbyRGB[3*(2*i+1)+1]=0;
			}
			b= 1.164*(Y1-16)+2.017*(Cb-128);//B
			pbyRGB[3*(2*i+1)]=b;
		    if(b>=255.0)
			{
				pbyRGB[3*(2*i+1)]=255;
			}
			else if(b<=0.0)
			{
				pbyRGB[3*(2*i+1)]=0;
			}
		}
		static int startTime = GetTickCount();
		int endTime = GetTickCount();
		pView->m_fCapFrameTime = (endTime-startTime);	
		startTime =endTime;
		if (pView->m_nCurRGBCaptureNo==(MAXBUFFNUM-1))
		{
		    pView->m_nCurRGBCaptureNo=0;
	   	}
		else
		{
			pView->m_nCurRGBCaptureNo++;
		}	
		pView->m_nCurIRCaptureNo=0;
	}
}
//��ע����������߳̽�����Ӳ��ʱ�������
#ifndef HARDWARE_OK
ULONG CIRTagetRecSysView::IRCapThread(LPVOID lpParam) 
{
	CIRTagetRecSysView* pView = (CIRTagetRecSysView*)lpParam;
	UINT nStartTime = GetTickCount();
	UINT nCurTime   = GetTickCount();
	UINT nDataPackNum=0;
	int nImageW=0;
	int nImageH=0;
	BYTE* pbyIRImgBuffer=new BYTE[TRACK_PACKET_COLS*IR_IMAGE_ROWS];  //����8bit����
	while(TRUE)
	{
		nStartTime = GetTickCount();
		if (pView->m_bRunning==false&&pView->m_bRunning==false)
		{
			Sleep(100);
			continue;
		}
			for(int i=0;i<IR_IMAGE_ROWS;i++)
			{
				for(int j=0;j<TRACK_PACKET_COLS;j++)
			    {
				    pbyIRImgBuffer[j*IR_IMAGE_ROWS+i] =rand()%256;
		     	}
			}
		    //ͼ��ֱ���񣨳������ǵ����ģ�
		    for(int i=0;i<IR_IMAGE_ROWS;i++)
		    {
			    memcpy(pView->m_pbyIrBuffs[pView->m_nCurIRCaptureNo]+(IR_IMAGE_ROWS-1-i)*IR_IMAGE_COLS,pbyIRImgBuffer+i*TRACK_PACKET_COLS, IR_IMAGE_COLS);
		    }
		    static int startTime = GetTickCount();
	    	int endTime = GetTickCount();
	    	pView->m_fCapFrameTime = (endTime-startTime);	
			startTime =endTime;
			if (pView->m_nCurIRCaptureNo==(MAXBUFFNUM-1))
			{
				pView->m_nCurIRCaptureNo=0;
			}
			else
			{
				pView->m_nCurIRCaptureNo++;
			}	
			Sleep(100);
		 }
	return 0;
}
#endif

ULONG CIRTagetRecSysView::RECVMessage(LPVOID lpParam)
{
	CIRTagetRecSysView* pView = (CIRTagetRecSysView*)lpParam;
	//�����׽�����Ϣ�ṹ��
	WSADATA wsadata;
	//����window socket�汾��Ϊ2.2
	WORD sockVersion = MAKEWORD(2, 2);
	//��������windos socket 
	if (WSAStartup(sockVersion, &wsadata) != 0)
	{
		printf("WSAStartup failed \n");
		return 0;
	}
	SOCKET sClient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	//�����Է���ַ(������)
	sockaddr_in serverAddr;
	//�������ص�ַ���ͻ��ˣ�
	sockaddr_in clientAddr;
	//���ñ��ض˿ڵ�ַ
	clientAddr.sin_family = AF_INET;
	//�ֳ�ע��˿�����
	clientAddr.sin_port = htons(9921);
	clientAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	if (SOCKET_ERROR == sClient)
	{
		printf("socket failed !\n");
		return 0;
	}
	//�󶨱���
	if (bind(sClient, (SOCKADDR *)&clientAddr, sizeof(clientAddr)))
	{
		//system("pause");
		return 0;
	}
	//��ȡ˫����ַ����
	int slen = sizeof(serverAddr);
	int clen = sizeof(clientAddr);
	//���û�������С���Ի���������,һ������1024���ֽ�
	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	int iRcv = 0;
	//ȫ�ֽṹ��
	int N=0;

	char ipAddr[] = "127.0.0.1";
	int Port = 9999;
	int endSuccess;

	while(TRUE)
	{
		Sleep(10);
		/*
		if (pView->m_bRunning==FALSE)
		{

			Sleep(100);
			continue;
		}//*/
		//��������ź�
		TRACE("WAITING");
		//��������
		iRcv = recvfrom(sClient, buffer, sizeof(buffer), 0, (SOCKADDR*)&serverAddr, &slen);
		memcpy(&trackCMD, buffer, 28);
		TRACE("irccd=%d---start=%d\n", trackCMD.bIrOrCCD, trackCMD.bStartOrStop);
		if (iRcv == SOCKET_ERROR)
		{
			printf("recvfrom failed:%d\n", WSAGetLastError());
		}
		else
		{	
			printf("SenderIP  :%s\n", inet_ntoa(serverAddr.sin_addr));
		}
		//CIRTagetRecSysView::ButtonCMD();
		//::SendMessage(pView->GetSafeHwnd(),OPENCVMESSAGE,NULL,NULL);

		//���յ�python���͵��ź�֮����д���
		//::PostMessageA(pView->GetSafeHwnd(),WM_COMMAND,MAKEWPARAM(IDC_BTN_WORK,OnBnClickedBtnWork),NULL);
		pView->m_dlgTrackCtrl.PerformClick();
		
		//if(!trackCMD.bStartOrStop){
	    //	
		//	endSuccess = udpEndSignal(ipAddr, Port);
		//	TRACE("endsig:%d\n",endSuccess);
		//}
		
	}
	
	closesocket(sClient);
	WSACleanup();
	//system("pause");
	return 0;
}

SOCKET createSocket() { //����һ��socket, ������Ϊipv4, UDP, ��û�н���󶨵��ض��˿�
	//�������ò�ͬ��Winsock�汾��
	WORD version = MAKEWORD(2, 2);
	//һ�����ݽṹ������ṹ�������洢��WSAStartup�������ú󷵻ص�Windows Sockets���ݡ�
	WSADATA wsadata;
	/*WSAStartup������Ӧ�ó����DLL���õĵ�һ��Windows Sockets������
	������Ӧ�ó����DLLָ��Windows Sockets API�İ汾�ż�����ض�Windows Socketsʵ�ֵ�ϸ�ڡ�
	Ӧ�ó����DLLֻ����һ�γɹ���WSAStartup()����֮����ܵ��ý�һ����Windows Sockets API������
    */
	if (WSAStartup(version, &wsadata))
	{
		cout << "WSAStartup failed " << endl;
		cout << "2s�����̨����رգ�" << endl;
		Sleep(2000);
		exit(0);
	}
	//�жϰ汾
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wVersion) != 2)
	{
		cout << "wVersion not 2.2" << endl;
		cout << "2s�����̨����رգ�" << endl;
		Sleep(2000);
		exit(0);
	}
	//�����ͻ���UDP�׽���
	SOCKET client;
	client = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (SOCKET_ERROR == client)
	{
		cout << "socket failed" << endl;
		cout << "2s�����̨����رգ�" << endl;
		Sleep(2000);
		exit(0);
	}
	else {
		return client;
	}
}


int udpEndSignal(char ipAddr[] , int Port)
{

	SOCKET client = createSocket();
	sockaddr_in caddr; //define an addr to use in recvfrom(), which is not specified
	sockaddr_in saddr;
	int slen = sizeof(saddr);
	int clen = sizeof(caddr);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(Port);
	saddr.sin_addr.S_un.S_addr = inet_addr(ipAddr);
	char end[] = "STOP";
	int iSend = 0;
	iSend = sendto(client, end, strlen(end), 0, (SOCKADDR*)&saddr, slen);

	closesocket(client);
	WSACleanup();

	return iSend;

}

int udpSend(char ipAddr[] , int Port, BYTE * IMG, int length, int frameSize)
{
	SOCKET client = createSocket();
	
	sockaddr_in caddr; //define an addr to use in recvfrom(), which is not specified
	sockaddr_in saddr;

	//���ն˵�ַ����
	int slen = sizeof(saddr);
	int clen = sizeof(caddr);
	//Ŀ�ĵ�ַ
	//���÷�������ַ
	saddr.sin_family = AF_INET;
    saddr.sin_port = htons(Port);
	saddr.sin_addr.S_un.S_addr = inet_addr(ipAddr);
	
	/* //uncomment to bind client socket, which is unnecessary
	caddr.sin_family = AF_INET;
	caddr.sin_port = htons(Port-5);
	caddr.sin_addr.S_un.S_addr = inet_addr(ipAddr);
	/*
	int ret = bind(client, (SOCKADDR *)&caddr, clen);
	if (ret == SOCKET_ERROR) {  
			cout << "client bind failed��" << endl;   
			cout << "2s���˳�����̨��" << endl;
			closesocket(client);
			WSACleanup();
			Sleep(2000);
			return -4;
	}
	//*/
	char data[100] = { 0 };                    //����һЩ���ֽڵ����ݻ�����
	char begin[] = "I BEGIN";       //����ͼƬǰ��ȷ����Ϣ
	//char end[] = "STOP";         //���ͼƬ���͵�֪ͨ��Ϣ

	int iSend = 0;                             //���ͺ�����״̬
	int iRecv = 0;
		
	//����ͼƬǰ�Ⱥͷ���������к�����׼��״̬���ж���Ϣ�����Ƿ�ɹ��������ɹ�������������ڹر�״̬
	iSend = sendto(client, begin, strlen(begin), 0, (SOCKADDR*)&saddr, slen);

	if (iSend == SOCKET_ERROR) {  
			cout << "���������ڹر�״̬�����Ժ����ԣ�" << endl;   
			cout << "20s���˳�����̨��" << endl;
			closesocket(client);
			WSACleanup();
			Sleep(20000);
			return -4;
	}
	iRecv = recvfrom(client, data, sizeof(data), 0, (SOCKADDR*)&caddr, &clen);
	//cout << "Client: " << begin << endl;

	memset(data, 0, sizeof(data));

	//cout << "Img length: " << length << endl;

	iSend = sendto(client, (char *)&length, sizeof(int), 0, (SOCKADDR*)&saddr, slen); //���ȷ���ͼƬ��С(��λbyte)�����ն�
	if (iSend == SOCKET_ERROR) { 
			cout << "�ļ�������Ϣ����ʧ�ܣ�" << endl;   
			cout << "10s���˳�����̨��" << endl;
			closesocket(client);
			WSACleanup();
			Sleep(10000);
			return -4;
	}
	iRecv = recvfrom(client, data, sizeof(data), 0, (SOCKADDR*)&caddr, &clen);
	//cout << "��������BEGIN SEND PICTURE��������" << endl;
	//int i = 0;

	iSend = sendto(client, (char*)IMG, length, 0, (SOCKADDR*)&saddr, slen);
	//* �Ƿ�ͼƬ�ֶη���(ÿ��frameSize Bytes)
	while (length > 0) {
			//cout << i << endl;

			//����ͼƬ��һ���֣����ͳɹ�����ͼƬ�ܳ��ȼ�ȥ��ǰ���͵�ͼƬƬ�ϳ���
			if (length >= frameSize){
				iSend = sendto(client, (char*)IMG, frameSize, 0, (SOCKADDR*)&saddr, slen);
				IMG += frameSize;
			}
			else{
				iSend = sendto(client, (char*)IMG, length, 0, (SOCKADDR*)&saddr, slen);
				IMG += length;
			}

			if (iSend == SOCKET_ERROR) {
				cout << "����ͼƬ����" << endl;
				cout << "2s���˳�����̨��" << endl;
				closesocket(client);
				WSACleanup();
				Sleep(2000);
				return -8;
			}
            iRecv = recvfrom(client, data, sizeof(data), 0, (SOCKADDR*)&caddr, &clen);
			length -= frameSize;
			//i++;
	}
	//iRecv = recvfrom(client, data, sizeof(data), 0, (SOCKADDR*)&caddr, &clen);
    //*/
	closesocket(client);
	WSACleanup();
	//cout<< "SEND FINISH" << endl;
	return 0;
}

ULONG CIRTagetRecSysView::IRProcessThread(LPVOID lpParam) 
{
	CIRTagetRecSysView* pView = (CIRTagetRecSysView*)lpParam;
	UINT nStartTime = GetTickCount();
	UINT nCurTime   = GetTickCount();
	UINT nDataPackNum=0;
	int nImageW=0;
	int nImageH=0;
	CString strText;
	UINT nCurIRCaptureNo=MAXBUFFNUM-1;
	UINT nCurRGBCaptureNo=MAXBUFFNUM-1;
	char ipAddr[] = "127.0.0.1";
	int Port = 9999;
	int frameSize = 8192;
	int sendSucessFlag;
	int endSuccess=-100;

	while(TRUE)
	{
		Sleep(0);
		nStartTime   = GetTickCount();
		if (pView->m_bRunning==FALSE)
		{
			nCurIRCaptureNo =MAXBUFFNUM-1;
			nCurRGBCaptureNo=MAXBUFFNUM-1;
			
			if(endSuccess==-100){
				endSuccess = udpEndSignal(ipAddr, Port);
			    //TRACE("endsig:%d\n",endSuccess);
			}
			Sleep(100);
			continue;
		}
		//+++++++++++++++++++++++++++++++++++++++++++����ģʽͼ����+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		pView->m_bRunning = TRUE;
		if (pView->m_bRunning==TRUE)
		{	endSuccess=-100;		
			//if(pView->m_dlgTrackCtrl.m_byImageType==0)//����
			if(trackCMD.bIrOrCCD == 1)
			{
				int nCurIRCaptureNoNew=MAXBUFFNUM-1;
				if (pView->m_nCurIRCaptureNo>0)
				{
					nCurIRCaptureNoNew =pView->m_nCurIRCaptureNo-1;
				}
				//�жϵ�ǰ֡�Ƿ��Ѿ������,δ���������
				if (nCurIRCaptureNo!=nCurIRCaptureNoNew)
				{
					nCurIRCaptureNo=nCurIRCaptureNoNew;
					//����8bit������������������		
					
					memcpy(pView->m_pbyIr,pView->m_pbyIrBuffs[nCurIRCaptureNo], IR_IMAGE_COLS*IR_IMAGE_ROWS);	
					BYTE* pImage =(BYTE*)pView->m_wndTrack.m_dibBMP.GetBits();
					BYTE* pImagSOURCE=pView->m_pbyIrBuffs[nCurIRCaptureNo];
					for(int i=0;i<IR_IMAGE_COLS;i++)
					{
						for(int j=0;j<IR_IMAGE_ROWS;j++)
						{
							pImage[(IR_IMAGE_ROWS-1-j)*IR_IMAGE_COLS+i] = pImagSOURCE[j*IR_IMAGE_COLS+i];	
						}
					}		
					//+++++++++++++++++++++�����㷨�����ڴ����++++++++++++++++++++++++++++++++++++++++++++++++++	
					//������������������ڴ���Ϊm_pbyIr

					if(pView->m_bExe == false)
					{
						//ÿ��ֻ��������֡
						IMGData = pView->m_pbyIr;
						if(trackCMD.bStartOrStop)
						{
                            sendSucessFlag = udpSend(ipAddr, Port, IMGData, 640*512, frameSize);
							//::SendMessage(pView->GetSafeHwnd(),OPENCVMESSAGE,NULL,NULL);
						}
							
					}
					//drone_det->CvtPyObject((void*)pView->m_pbyIr);
					//+++++++++++++++++++++����ͼ��ʾ++++++++++++++++++++++++++++++++++++++++++++++++	

// 					pView->m_wndTrack.m_bRunning =pView->m_bRunning;
// 					pView->m_wndTrack.m_fCapFrameTime =pView->m_fCapFrameTime;
// 					pView->m_wndTrack.DrawWnd();
				}
			}
			else
			{
				int nCurRGBCaptureNoNew=MAXBUFFNUM-1;
				if (pView->m_nCurRGBCaptureNo>0)
				{
					nCurRGBCaptureNoNew =pView->m_nCurRGBCaptureNo-1;
				}
				//�жϵ�ǰ֡�Ƿ��Ѿ������,δ���������
				if (nCurRGBCaptureNo!=nCurRGBCaptureNoNew)
				{
					nCurRGBCaptureNo=nCurRGBCaptureNoNew;
					//����8bit������������������						
					memcpy(pView->m_pbyRGB,pView->m_pbyRGBBuffs[nCurRGBCaptureNo], RGB_IMAGE_COLS*RGB_IMAGE_ROWS*3);	
					//+++++++++++++++++++++�����㷨�����ڴ����++++++++++++++++++++++++++++++++++++++++++++++++++	
					//������������������ڴ���Ϊm_pbyIr

					if(pView->m_bExe == false)
					{
						//ÿ��ֻ��������֡
						IMGData = pView->m_pbyRGB;
						
						cv::Mat rgbImage(cv::Size(1920,1080),CV_8UC3,IMGData);
						//TRACE("GET ORG MAT");
						cv::Mat ResImg(cv::Size(640,384),CV_8UC3);
						//TRACE("GET RES MAT");
						cv::resize(rgbImage,ResImg, cv::Size(640,384),CV_INTER_CUBIC);
						//TRACE("RESIZE");
						BYTE* rgbImageDate = ResImg.data;
						//TRACE("PASS PTR");
						//cv::imwrite("wodeshixiong.jpg", ResImg);
						if(trackCMD.bStartOrStop){
							sendSucessFlag = udpSend(ipAddr, Port, rgbImageDate, 640*384*3, frameSize);
						}
							//::SendMessage(pView->GetSafeHwnd(),OPENCVMESSAGE,NULL,NULL);
					}
					//drone_det->CvtPyObject((void*)pView->m_pbyIr);

					//+++++++++++++++++++++��ɫͼ��ʾ++++++++++++++++++++++++++++++++++++++++++++++++	
					/*
					BYTE* pImage =(BYTE*)pView->m_wndTrack.m_dibBMP.GetBits();
					for(int i=0;i<RGB_IMAGE_COLS;i++)
					{
						for(int j=0;j<RGB_IMAGE_ROWS;j++)
						{
							pImage[3*((RGB_IMAGE_ROWS-1-j)*RGB_IMAGE_COLS+i)] = pView->m_pbyRGB[3*(j*RGB_IMAGE_COLS+i)];
							pImage[3*((RGB_IMAGE_ROWS-1-j)*RGB_IMAGE_COLS+i)+1] = pView->m_pbyRGB[3*(j*RGB_IMAGE_COLS+i)+1];
							pImage[3*((RGB_IMAGE_ROWS-1-j)*RGB_IMAGE_COLS+i)+2] = pView->m_pbyRGB[3*(j*RGB_IMAGE_COLS+i)+2];
							
						}
					}
					pView->m_wndTrack.m_bRunning =pView->m_bRunning;
					pView->m_wndTrack.m_fCapFrameTime =pView->m_fCapFrameTime;
					pView->m_wndTrack.DrawWnd();
					*/
				}
			}
		}
	}
	return 0;
}
