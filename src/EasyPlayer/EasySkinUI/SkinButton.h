#ifndef BUTTON_HEAD_FILE
#define BUTTON_HEAD_FILE

#pragma once

#include "SkinUI.h"
#include "ISkinControl.h"

//按妞类型
enum UI_BUTTON_TYPE
{
	en_PushButton,
	en_CheckButton,
	en_RadioButton,
	en_IconButton,
	en_MenuButton
};

// CButtonEx

class SKINUI_CLASS CSkinButton : public CButton,public ISkinControl
{
	DECLARE_DYNAMIC(CSkinButton)

	//资源定义
public:
	CImageEx * m_pBackImgN, * m_pBackImgH, * m_pBackImgD, * m_pBackImgF;
	CImageEx * m_pCheckImgN, * m_pCheckImgH, * m_pCheckImgTickN, *m_pCheckImgTickH;
	CImageEx * m_pArrowImg, * m_pIconImg;

	//变量定义
protected:
	BOOL m_bFocus, m_bPress, m_bHover, m_bMouseTracking;

	UI_BUTTON_TYPE				m_nBtnType;

	HMENU						m_hMenu;
	HDC							m_hBackDC;
	bool						m_bPushed;
	// 记录当前的按钮状态 [8/28/2015-11:20:24 Dingshuai]
	bool						m_bCurPushState;

	LPCTSTR						m_lpszUrl;

	int							m_fontIndex;

	//函数定义
public:
	//构造函数
	CSkinButton();
	//析构函数
	virtual ~CSkinButton();

	//重载函数
protected:
	//消息循环
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//设置属性
	virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	//创建控件
	virtual BOOL CreateControl(CWnd* pParentWnd);

	//设置函数
public:
	//设置类型
	void SetButtonType(UI_BUTTON_TYPE type);
	//调整位置
	void SetSize(int nWidth,int nHeight);
	//设置菜单
	void SetMenu(HMENU hMenu);
	//设置菜单
	void SetPushed(bool bPush);
	//设置按钮Press状态
	void SetPress(BOOL bPress);

	//获取函数
public:
	//获取按钮Press状态
	BOOL GetPress();

	//资源加载
public:
	//设置资源
	BOOL SetBackImage(LPCTSTR lpNormal, LPCTSTR lpHoven, LPCTSTR lpDown, LPCTSTR lpFocus,CONST LPRECT lprcNinePart=NULL);
	//设置资源
	BOOL SetCheckImage(LPCTSTR lpNormal, LPCTSTR lpHoven, LPCTSTR lpTickNormal, LPCTSTR lpTickHoven);
	//设置资源
	BOOL SetIconImage(LPCTSTR lpszFileName);
	//设置资源
	BOOL SetMenuImage(LPCTSTR lpszFileName);

	//绘画函数
public:
	//PUSH按钮
	void DrawPushButton(CDC* pDC,RECT &rcClient);
	//Check按钮
	void DrawCheckButton(CDC* pDC,RECT &rcClient);
	//Check按钮
	void DrawIConButton(CDC* pDC,RECT &rcClient);
	//Check按钮
	void DrawMenuButton(CDC* pDC,RECT &rcClient);

	//消息函数
protected:
	//鼠标移动
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//鼠标离开
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	//重绘背景
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//销毁消息
	afx_msg void OnDestroy();
	//左键按下
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//左键抬起
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//设置焦点
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//焦点丢失
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//绘制消息
	afx_msg void OnPaint();
	//左键双击
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//设置状态check
	afx_msg LRESULT OnBMSetCheck(WPARAM, LPARAM);
	//获得是否在check 状态	
	afx_msg LRESULT OnBMGetCheck(WPARAM, LPARAM);


	// 扩展函数 [2/25/2016 Dingshuai]
public:
	void RelayEventCamMove(int nType);
	void SetBtnText(CString strBtnText); //设置文本文字
	CString GetBtnText();//获取文本


protected:
	DECLARE_MESSAGE_MAP()
};


#endif