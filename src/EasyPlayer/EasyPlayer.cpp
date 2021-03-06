
// EasyPlayer.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "EasyPlayer.h"
#include "EasyPlayerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEasyPlayerApp

BEGIN_MESSAGE_MAP(CEasyPlayerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CEasyPlayerApp 构造

CEasyPlayerApp::CEasyPlayerApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CEasyPlayerApp 对象

CEasyPlayerApp theApp;


// CEasyPlayerApp 初始化

BOOL CEasyPlayerApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	InitHookScrollBar();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CEasyPlayerDlg dlg;
	m_pMainWnd = &dlg;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

BOOL CEasyPlayerApp::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
	{
		return TRUE;
	}

	return CWinApp::PreTranslateMessage(pMsg);
}

int CEasyPlayerApp::ExitInstance()
{
	RemoveHookScrollBar();
	return CWinApp::ExitInstance();
}

const ModuleFileInfomations& GetModuleFileInformations()
{
	static ModuleFileInfomations __s_mi;
	static BOOL bLoad = FALSE;

	if(!bLoad)
	{
		// Get application's full path.

		::GetModuleFileName(NULL, __s_mi.strFullPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
		__s_mi.strFullPath.ReleaseBuffer();

		// Break full path into seperate components.
		_tsplitpath_s(
			__s_mi.strFullPath, 
			__s_mi.strDrive.GetBufferSetLength(_MAX_DRIVE + 1), _MAX_DRIVE + 1,
			__s_mi.strDir.GetBufferSetLength(_MAX_DIR + 1), _MAX_DIR + 1,
			__s_mi.strName.GetBufferSetLength(_MAX_FNAME + 1), _MAX_FNAME + 1,
			__s_mi.strExt.GetBufferSetLength(_MAX_EXT + 1), _MAX_EXT + 1);

		__s_mi.strDrive.ReleaseBuffer();//盘符
		__s_mi.strDir.ReleaseBuffer();//目录中间路径
		__s_mi.strName.ReleaseBuffer();//文件名称
		__s_mi.strExt.ReleaseBuffer();//文件扩展名(.exe)

		TCHAR   sDrive[_MAX_DRIVE];   
		TCHAR   sDir[_MAX_DIR];   
		TCHAR   sFilename[_MAX_FNAME],Filename[_MAX_FNAME];   
		TCHAR   sExt[_MAX_EXT];   

		GetModuleFileName(AfxGetInstanceHandle(),   Filename,   _MAX_PATH);   
		_tsplitpath_s(Filename,   sDrive,   sDir,   sFilename,   sExt); 

		CString  homeDir(CString(sDrive) + CString(sDir));   
		int      nLen = homeDir.GetLength(); 

		if(homeDir.GetAt(nLen-1) != _T('\\'))   
			homeDir   +=   _T('\\');   

		__s_mi.strPath = homeDir;

		bLoad = TRUE;
	}

	return __s_mi;
}
