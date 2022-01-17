//#include <Python.h>
#include <WinSock2.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
//#include <numpy/arrayobject.h>

#pragma once

#define IMG_IR_HEIGHT 512
#define IMG_IR_WIDTH 640

#define IMG_RGB_HEIGHT 1080
#define IMG_RGB_WIDTH 1920
//���巢�ͽṹ��
typedef struct _GFKDTrackAimInfo
{
	int msgCode;
	int nAimType;
	int nAimX;    //Ŀ�����Ͻ�
	int nAimY;
	int nAimW;	  //Ŀ��߿�
	int nAinH;
	int nTrackType;
	int nState;
}GFKDTrackAimInfo;
//������ܽṹ��
typedef struct _GFKDTrackCMD
{
	int msgCode;
	int bIrOrCCD;
	int nFieldAngle;
	int nVal;
	int bStartOrStop;
	int nCenterY;
	int nCenterX;
}GFKDTrackCMD;

/*
class DroneTrack
{
public:
	GFKDTrackAimInfo AimInfo;
	GFKDTrackCMD TrackCMD;
	PyObject *pModule, *pDict;
	PyObject *pMat,*pArgs, *pFunc;
	PyObject *DetectClass, *TrackClass;
	PyObject *DetectIns, *TrackIns;
	
	PyObject *myint;

public:
	PyObject *pIns;
	//���캯�������Զ�����python���л������������������ͷ�python����
	DroneTrack();
	~DroneTrack();
	void RecvSignal();         //���ܽṹ���ź�
	void SendCoord();          //���ͽṹ����Ϣ
	void CvtPyObject(void* ImgBuff);        //C++ͼ��ת����Python����
	void DroneDetection();	   //����̺߳���������python���
	void DroneTracking();	   //׷���̺߳���������python׷��
};
*/