#pragma once

#include "MainVideoWnd.h"
// ����EasyPlayer������ [3/6/2016 dingshuai]
#include "EasyPlayerManager.h"

#define WM_TIMER_START_ID 1001
#define WM_TIMER_CONFIG_ID 1002

// EasyPlayerWebActiveXCtrl.h : CEasyPlayerWebActiveXCtrl ActiveX �ؼ����������

// CEasyPlayerWebActiveXCtrl : �й�ʵ�ֵ���Ϣ������� EasyPlayerWebActiveXCtrl.cpp��

class CEasyPlayerWebActiveXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CEasyPlayerWebActiveXCtrl)

// ���캯��
public:
	CEasyPlayerWebActiveXCtrl();

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// ʵ��
protected:
	~CEasyPlayerWebActiveXCtrl();

	BEGIN_OLEFACTORY(CEasyPlayerWebActiveXCtrl)        // �๤���� guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR *);
	END_OLEFACTORY(CEasyPlayerWebActiveXCtrl)

	DECLARE_OLETYPELIB(CEasyPlayerWebActiveXCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CEasyPlayerWebActiveXCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CEasyPlayerWebActiveXCtrl)		// �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// �¼�ӳ��
	DECLARE_EVENT_MAP()

// ���Ⱥ��¼� ID
public:
	enum {
		eventidOnPlayEvent = 1L,
		dispidSetOSD = 4L,
		dispidClose = 3L,
		dispidConfig = 2L,
		dispidStart = 1L
	};

	CMainVideoWnd m_pActiveDlg; 
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
protected:
	LONG Start(LPCTSTR sURL, LPCTSTR sRenderFormat, LPCTSTR sUserName, LPCTSTR sPassword, LPCTSTR sHardDecord, LPCTSTR sRtpOverTcp);
	void Config(LPCTSTR sFrameCache, LPCTSTR sPlaySound, LPCTSTR sShowToScale, LPCTSTR sShowStatisticInfo);
	void SetOSD(LPCTSTR show, LPCTSTR alpha, LPCTSTR red, LPCTSTR green, LPCTSTR blue, LPCTSTR left, LPCTSTR top, LPCTSTR right, LPCTSTR bottom, LPCTSTR strOSD);
	void Close(void);
	static int CALLBACK EasyPlayerCallBack( int _channelId, int *_channelPtr, int _frameType, char *pBuf, EASY_FRAME_INFO* _frameInfo);

private:
	EasyPlayerManager m_player;
	bool m_bInit;

	char szURL[512] ;
	char szUserName[128] ;
	char szPassword[128] ;

	int nHardDecode;
    RENDER_FORMAT eRenderFormat;

	int	   nFrameCache ;
	BOOL bPlaySound ;
	BOOL bShowToScale ;
	BOOL bShowStatisticInfo ;
	int nRtpOverTcp;
public:
	virtual void OnSetClientSite();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void OnPlayEvent(LPCTSTR sPlayerErrorString)
	{
		FireEvent(eventidOnPlayEvent, EVENT_PARAM(VTS_BSTR), sPlayerErrorString);
	}
};

