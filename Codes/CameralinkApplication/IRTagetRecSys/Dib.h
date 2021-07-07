#ifndef __DIB_H
#define __DIB_H
//
// CDIB -
// CDibDC -
//
// Implements a simple encapsulation of a DIB section and a DC.
//
//

//////////////////////////////////////////////////////////////////////
//
// CDIB
//
// �豸�޹�λͼ��
//
// ��ɹ���:
//
// �豸�޹�λͼ�Ĵ���,��ʾ,����,����
//
//////////////////////////////////////////////////////////////////////


class CDIB;
class CDibDC;

class CDIB : public CGdiObject
{
	DECLARE_DYNAMIC(CDIB)

public:
	//�ɾ������λͼ
	static CDIB* PASCAL FromHandle(HBITMAP hBitmap);

// Constructors
	CDIB();

	//����λͼ
	BOOL CreateDIB(int nWidth, int nHeight,int Palette,UINT nBitcount, const void* lpBits=NULL);

	//����λͼ
	BOOL CreateDIBIndirect(LPBITMAPINFO lpBitmap, const void* lpBits=NULL);

	//��׽����ͼ��
	BOOL CaptureDIB(CWnd * pWnd, const CRect& capRect = CRect(0,0,0,0));

// Attributes
	//�õ�λͼ
	operator HBITMAP() const;

	//����λͼ
	CDIB& operator = (CDIB& copy);

// Operations
	//����ͼ������
	DWORD SetDIBBits(DWORD dwCount, const void* lpBits);
	//�õ�ͼ������
	LPVOID GetDIBBits(DWORD dwCount = 0, LPVOID lpBits = NULL);

// Implementation
public:
	virtual ~CDIB();
#ifdef _DEBUG
	virtual void Dump(CDumpContext& dc) const;
#endif

// Newly added functions
public:
	//�õ�ʹ�õ���ɫ��
	int GetColorUsed();

	//���õ�ɫ��
	void SetPalette(UINT uStartIndex, UINT cEntries, CONST RGBQUAD *pColors);
	//���õ�ɫ��
	void SetPalette(CPalette* pPal);
	
	//�õ��豸
	CDC* GetDC(void);
	//�ͷ��豸
	static BOOL ReleaseDC(CDC *pdc);

	//�õ�λͼ
	int GetBitmap(BITMAP* pBitMap);
	//�õ�DibSection
	int GetDibSection(DIBSECTION* pDibSection);
	//�õ��̶��ڴ��ͼ������
	LPVOID GetMemImgData(const void *pMem);
	//�õ����
	int GetWidth();
	//�õ���Ԫ�ֽ���
	int CDIB::GetBytesPixel(void);
	//�õ��߶�
	int GetHeight();
	//�õ��ߴ�
	SIZE GetSize();
	//�õ�ÿ��ͼ���ֽ���
	int GetWidthBytes();
	//�õ�ͼ��λ��
	int GetBitCount();
	//�õ�ͼ������
	LPVOID GetBits();
	//�õ�ͼ����Ϣͷ
	LPBITMAPINFO GetBitmapInfo(void);

	int  GetDataFromIR(WORD* pIRData,BYTE nType,WORD wMaxLimit,WORD wMinLimit); //ת��Ϊ�Ҷ�ͼ
	int  Get2bitDataFromIR(WORD* pIRData,WORD wTh);
};

////////////////////////////////////////////////////////////////////
// inline functions

//////////////////////////////////////////////////////////////////
// 
// GetBitmap(BITMAP* pBitMap)
// 
// ��ɹ���:
//     �õ�λͼ
//
// �������:
//	   λͼָ�� pBitMap
//
// ���ز���:
//	   �Ƿ�ɹ�
//
//////////////////////////////////////////////////////////////////

//�õ�λͼ
inline int CDIB::GetBitmap(BITMAP* pBitMap)
{
	return(::GetObject(m_hObject, sizeof(BITMAP), pBitMap));
}


//////////////////////////////////////////////////////////////////
// 
// GetDibSection(DIBSECTION *pDibSection)
// 
// ��ɹ���:
//     �õ�DibSection
//
// �������:
//	   DibSectionָ�� pDibSection
//
// ���ز���:
//	   �Ƿ�ɹ�
//
//////////////////////////////////////////////////////////////////

//�õ�DibSection
inline int CDIB::GetDibSection(DIBSECTION *pDibSection)
{
	return(::GetObject(m_hObject, sizeof(DIBSECTION), pDibSection));
}


//////////////////////////////////////////////////////////////////
// 
// HBITMAP()
// 
// ��ɹ���:
//     �õ�λͼ���
//
// �������:
//	   ��
//
// ���ز���:
//	   λͼ���
//
//////////////////////////////////////////////////////////////////

//�õ�λͼ���
inline CDIB::operator HBITMAP() const
{
	return (HBITMAP)(this == NULL ? NULL : m_hObject);
}


//////////////////////////////////////////////////////////////////
// 
// FromHandle(HBITMAP hDib)
// 
// ��ɹ���:
//     ��λͼ����õ�λͼ��
//
// �������:
//	   λͼ��� hDib
//
// ���ز���:
//	   λͼ��
//
//////////////////////////////////////////////////////////////////

//��λͼ����õ�λͼ��
inline CDIB* PASCAL CDIB::FromHandle(HBITMAP hDib)
{
	return((CDIB*)CGdiObject::FromHandle(hDib));
}


//////////////////////////////////////////////////////////////////
// 
// GetWidth(void)
// 
// ��ɹ���:
//     �õ����
//
// �������:
//	   ��
//
// ���ز���:
//	   ���
//
//////////////////////////////////////////////////////////////////

//�õ����
inline int CDIB::GetWidth(void)
{
	BITMAP bmp;
	GetBitmap(&bmp);
	return(bmp.bmWidth);
}

//////////////////////////////////////////////////////////////////
// 
// GetBitsPixel(void)
// 
// ��ɹ���:
//     �õ���Ԫ�ֽ���
//
// �������:
//	   ��
//
// ���ز���:
//	   ��Ԫ�ֽ���
//
//////////////////////////////////////////////////////////////////

//�õ���Ԫ�ֽ���
inline int CDIB::GetBytesPixel(void)
{
	BITMAP bmp;
	GetBitmap(&bmp);
	return(bmp.bmBitsPixel/8);
}
//////////////////////////////////////////////////////////////////
// 
// GetHeight(void)
// 
// ��ɹ���:
//     �õ��߶�
//
// �������:
//	   ��
//
// ���ز���:
//	   �߶�
//
//////////////////////////////////////////////////////////////////

//�õ��߶�
inline int CDIB::GetHeight(void)
{
	BITMAP bmp;
	GetBitmap(&bmp);
	return(bmp.bmHeight);
}


//////////////////////////////////////////////////////////////////
// 
// GetSize(void)
// 
// ��ɹ���:
//     �õ��ߴ�
//
// �������:
//	   ��
//
// ���ز���:
//	   �ߴ�
//
//////////////////////////////////////////////////////////////////

//�õ��ߴ�
inline SIZE CDIB::GetSize(void)
{
	BITMAP bmp;
	GetBitmap(&bmp);
	CSize size(bmp.bmWidth, bmp.bmHeight);
	return(size);
}


//////////////////////////////////////////////////////////////////
// 
// GetWidthBytes(void)
// 
// ��ɹ���:
//     �õ�ÿ���ֽ���
//
// �������:
//	   ��
//
// ���ز���:
//	   ÿ���ֽ���
//
//////////////////////////////////////////////////////////////////

//�õ�ÿ���ֽ���
inline int CDIB::GetWidthBytes(void)
{
	BITMAP bmp;
	GetBitmap(&bmp);
	return(bmp.bmWidthBytes);
}


//////////////////////////////////////////////////////////////////
// 
// GetBitCount(void)
// 
// ��ɹ���:
//     �õ�ͼ��λ��
//
// �������:
//	   ��
//
// ���ز���:
//	   ͼ��λ��
//
//////////////////////////////////////////////////////////////////

//�õ�ͼ��λ��
inline int CDIB::GetBitCount(void)
{
	BITMAP bmp;
	GetBitmap(&bmp);
	return(bmp.bmBitsPixel);
}


//////////////////////////////////////////////////////////////////
// 
// GetBits(void)
// 
// ��ɹ���:
//     �õ�ͼ������
//
// �������:
//	   ��
//
// ���ز���:
//	   ͼ������
//
//////////////////////////////////////////////////////////////////

//�õ�ͼ������
inline LPVOID CDIB::GetBits(void)
{
	BITMAP bmp;
	GetBitmap(&bmp);
	return(bmp.bmBits);
}
inline int CDIB::GetDataFromIR(WORD* pIRData,BYTE nType,WORD wMaxLimit,WORD wMinLimit) //ת��Ϊ�Ҷ�ͼ,0:ֱ��ͼ;1��ֱ��ӳ��
{
	int w= GetWidth();
	int h =GetHeight();		
	BYTE* pImage =(BYTE*)GetBits();
	int kk =0;

	if (nType==0)
	{
		UCHAR  m_pbyHist[65536];
		UCHAR  m_pLUT[65536];

		BYTE* pImage =(BYTE*)GetBits();
		DWORD sum=0,HistSum=0;
		DWORD HistSumH=0,HistSumL=0,HistMean=0;

		memset(m_pLUT,0,65536*sizeof(UCHAR));
		memset(m_pbyHist,0,65536*sizeof(UCHAR));

		int kk =0;	
		while (kk<(h*w))
		{
			WORD wIrValue =pIRData[kk];
			if(wIrValue>=wMaxLimit)
			{
				wIrValue=wMaxLimit;
			}
			if(wIrValue<=wMinLimit)
			{
				wIrValue=wMinLimit;
			}
			if(m_pbyHist[wIrValue]<255) 
			{
				m_pbyHist[wIrValue]++;
			}
			kk++;
		}
		HistSum=0;
		for (int  i=0;i<65536;i++)
		{
			if (m_pbyHist[i]<3)
			{
				m_pbyHist[i]=0;
			}
			HistSum+=m_pbyHist[i];
		}
		sum=0;
		int nTemp;
		for (int i=0;i<65536;i++)
		{
			sum+=m_pbyHist[i];
			if (HistSum!=0)
			{
				m_pLUT[i]=255.00*sum/HistSum;
				nTemp=m_pLUT[i];
				if(nTemp<0)
				{
					nTemp=0;
				}
				else if(nTemp>255)
				{
					nTemp=255;
				}
				m_pLUT[i]=nTemp;
			}
		}
		for(int i =0;i<w;i++)
		{
			for(int j =0;j<h;j++)
			{
				if (pIRData[j*w+i]==65535)
				{
					pImage[((h-1-j)*(w)+i)] =255;
				}
				else if (pIRData[j*w+i]==0)
				{
					pImage[((h-1-j)*(w)+i)] =0;
				}
				else
				{
					pImage[((h-1-j)*(w)+i)] = m_pLUT[pIRData[j*w+i]];
				}				
			}
		}
	}
	else
	{
		WORD maxV=0,minV=65536;
		while (kk<(h*w))
		{
			if(pIRData[kk]>=maxV)
			{
				maxV=pIRData[kk];
			}
			if(minV>=pIRData[kk])
			{
				minV=pIRData[kk];
			}
			kk++;
		}
		if(maxV>=wMaxLimit)
		{
			maxV=wMaxLimit;
		}
		if(minV<=wMinLimit)
		{
			minV=wMinLimit;
		}
		int nsample = 0; 
		float span = (float)(maxV - minV+ 1);
		for(int i =0;i<w;i++)
		{
			for(int j =0;j<h;j++)
			{
				if (pIRData[j*w+i]==65535)
				{
					nsample =255;
				}
				else if (pIRData[j*w+i]==0)
				{
					nsample =0;
				}
				else if (pIRData[j*w+i]>maxV)
				{
					nsample=255;
				}
				else if (pIRData[j*w+i]<minV)
				{
					nsample=0;
				}
				else
				{
					nsample =(int)(((pIRData[j*w+i]-minV)*1.0/span)*255);
				}
				pImage[((h-1-j)*(w)+i)] = nsample;
			}
		}
	}
	return TRUE;
}
inline int CDIB::Get2bitDataFromIR(WORD* pIRData,WORD wTh) //ת��Ϊ�Ҷȶ�ֵͼ
{
	int w= GetWidth();
	int h =GetHeight();		
	BYTE* pImage =(BYTE*)GetBits();
	int kk =0;
	for(int i =0;i<w;i++)
	{
		for(int j =0;j<h;j++)
		{
			if (pIRData[j*w+i]>wTh)
			{
				pImage[((h-1-j)*(w)+i)] = 255;
			}
			else
			{
				pImage[((h-1-j)*(w)+i)]=0;
			}
		}
	}
	return TRUE;
}
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//
// CDibDC
//
// �豸�޹�λͼ�豸��(�汾1.0)
//
// ��ɹ���:
//     ���豸�޹�λͼ�������
//
//////////////////////////////////////////////////////////////////////


class CDibDC : public CDC
{
	DECLARE_DYNAMIC(CDibDC)

// Constructors
public:
	CDibDC();

// Attributes
protected:
	HBITMAP m_hOld;

// Implementation
public:
	CPalette * GetPalette();
	virtual ~CDibDC();
	
	friend class CDIB;
};

#endif //__DIB_H