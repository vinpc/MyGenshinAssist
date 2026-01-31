
// MyGenshinAssistDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MyGenshinAssist.h"
#include "MyGenshinAssistDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

constexpr unsigned int c_HotKeyIdAltQ = 0;
constexpr unsigned int c_HotKeyIdAltE = 1;

volatile BOOL CMyGenshinAssistDlg::s_isMaWeiKaWorking = FALSE;
volatile BOOL CMyGenshinAssistDlg::s_isMaWeiKaWorking1 = FALSE;
volatile BOOL CMyGenshinAssistDlg::s_isAutoTaskWorking = FALSE;
volatile BOOL CMyGenshinAssistDlg::s_isAutoAttacking = FALSE;
volatile BOOL CMyGenshinAssistDlg::s_isQiaSiKaWorking = FALSE;
volatile BOOL CMyGenshinAssistDlg::s_isHutaoWorking = FALSE;




// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyGenshinAssistDlg 对话框



CMyGenshinAssistDlg::CMyGenshinAssistDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYGENSHINASSIST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyGenshinAssistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyGenshinAssistDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMyGenshinAssistDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMyGenshinAssistDlg::OnBnClickedCancel)
	ON_WM_HOTKEY()
	ON_BN_CLICKED(IDC_RADIO2, &CMyGenshinAssistDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO1, &CMyGenshinAssistDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO4, &CMyGenshinAssistDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO3, &CMyGenshinAssistDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO5, &CMyGenshinAssistDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &CMyGenshinAssistDlg::OnBnClickedRadio6)
END_MESSAGE_MAP()


// CMyGenshinAssistDlg 消息处理程序

BOOL CMyGenshinAssistDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	((CButton*)GetDlgItem(IDC_RADIO5))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(TRUE);

	OnBnClickedOk();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMyGenshinAssistDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyGenshinAssistDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMyGenshinAssistDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyGenshinAssistDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	if (!m_isRegAltQ)
	{
		m_isRegAltQ =  RegisterHotKey(this->GetSafeHwnd(), c_HotKeyIdAltQ, MOD_ALT /*| MOD_NOREPEAT*/, 'Q');

		if (!m_isRegAltQ)
		{
			AfxMessageBox(_T("Register hotkey ALT-Q failed."), MB_OK | MB_ICONSTOP);
		}		
	}

	if (!m_isRegAltE)
	{
		m_isRegAltE = RegisterHotKey(this->GetSafeHwnd(), c_HotKeyIdAltE, MOD_ALT /*| MOD_NOREPEAT*/, 'E');

		if (!m_isRegAltE)
		{
			AfxMessageBox(_T("Register hotkey ALT-E failed."), MB_OK | MB_ICONSTOP);
		}
	}

	GetDlgItem(IDOK)->EnableWindow(FALSE);
}


void CMyGenshinAssistDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_isRegAltQ)
	{
		UnregisterHotKey(this->GetSafeHwnd(), c_HotKeyIdAltQ);
		m_isRegAltQ = FALSE;
	}

	if (m_isRegAltE)
	{
		UnregisterHotKey(this->GetSafeHwnd(), c_HotKeyIdAltE);
		m_isRegAltE = FALSE;
	}

	GetDlgItem(IDOK)->EnableWindow(TRUE);

	CDialogEx::OnCancel();
}


void CMyGenshinAssistDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString strMsg;
	strMsg.Format(_T("OnHotKey: id:%d, key1:%d, key2:%d\n"), nHotKeyId, nKey1, nKey2);
	OutputDebugString(strMsg);	

	switch (nHotKeyId)
	{
	case c_HotKeyIdAltQ:
		OnAltQ();
		break;
	case c_HotKeyIdAltE:
		OnAltE();
		break;
	default:
		break;
	}

	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}

DWORD GetRandomValue(DWORD dwMinVal, DWORD dwMaxVal)
{
	static BOOL s_init = FALSE;
	if (!s_init)
	{
		srand(GetTickCount());
		s_init = TRUE;
	}
	float percent = rand() / (float)RAND_MAX;
	auto delta = dwMaxVal - dwMinVal;
	auto result = dwMinVal + (DWORD)(delta * percent);
	return result;
}

void CMyGenshinAssistDlg::OnAltQ()
{
	//AfxMessageBox(_T("Alt-Q is detected."));
	if (((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck()) //火神自动ZSA
	{
		if (!s_isMaWeiKaWorking)
		{
			s_isMaWeiKaWorking = TRUE;
			//创建工作线程
			unsigned int tid;
			HANDLE hThread = (HANDLE)_beginthreadex(nullptr, 0, CMyGenshinAssistDlg::_MaweikaWorkingThread, this, CREATE_SUSPENDED, &tid);
			if (hThread == nullptr)
			{
				s_isMaWeiKaWorking = FALSE;
				return;
			}
			::ResumeThread(hThread);
			CloseHandle(hThread);
		}
		else
		{
			s_isMaWeiKaWorking = FALSE;
		}
	}
	else if(((CButton*)GetDlgItem(IDC_RADIO2))->GetCheck()) //半自动过剧情 
	{
		if (!s_isAutoTaskWorking)
		{
			s_isAutoTaskWorking = TRUE;
			//创建工作线程
			unsigned int tid;
			HANDLE hThread = (HANDLE)_beginthreadex(nullptr, 0, CMyGenshinAssistDlg::_AutoTaskWorkingThread, this, CREATE_SUSPENDED, &tid);
			if (hThread == nullptr)
			{
				s_isAutoTaskWorking = FALSE;
				return;
			}
			::ResumeThread(hThread);
			CloseHandle(hThread);
		}
		else
		{
			s_isAutoTaskWorking = FALSE;
		}
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO4))->GetCheck()) //快速普攻 
	{
		if (!s_isAutoAttacking)
		{
			s_isAutoAttacking = TRUE;
			//创建工作线程
			unsigned int tid;
			HANDLE hThread = (HANDLE)_beginthreadex(nullptr, 0, CMyGenshinAssistDlg::_AutoAttackingThread, this, CREATE_SUSPENDED, &tid);
			if (hThread == nullptr)
			{
				s_isAutoAttacking = FALSE;
				return;
			}
			::ResumeThread(hThread);
			CloseHandle(hThread);
		}
		else
		{
			s_isAutoAttacking = FALSE;
		}
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO5))->GetCheck()) //火神QZZPSZS
	{
		if (!s_isMaWeiKaWorking1)
		{
			s_isMaWeiKaWorking1 = TRUE;
			//创建工作线程
			unsigned int tid;
			HANDLE hThread = (HANDLE)_beginthreadex(nullptr, 0, CMyGenshinAssistDlg::_MaweikaWorkingThread1, this, CREATE_SUSPENDED, &tid);
			if (hThread == nullptr)
			{
				s_isMaWeiKaWorking1 = FALSE;
				return;
			}
			::ResumeThread(hThread);
			CloseHandle(hThread);
		}
		else
		{
			s_isMaWeiKaWorking1 = FALSE;
		}
	}
}

void CMyGenshinAssistDlg::OnAltE()
{
	//AfxMessageBox(_T("Alt-E is detected."));
	if (((CButton*)GetDlgItem(IDC_RADIO3))->GetCheck()) // 恰斯卡自动E并秒蓄 
	{
		if (!s_isQiaSiKaWorking)
		{
			s_isQiaSiKaWorking = TRUE;
			//创建工作线程
			unsigned int tid;
			HANDLE hThread = (HANDLE)_beginthreadex(nullptr, 0, CMyGenshinAssistDlg::_QiaSiKaWorkingThread, this, CREATE_SUSPENDED, &tid);
			if (hThread == nullptr)
			{
				s_isQiaSiKaWorking = FALSE;
				return;
			}
			::ResumeThread(hThread);
			CloseHandle(hThread);
		}
		else
		{
			s_isQiaSiKaWorking = FALSE;
		}
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO6))->GetCheck()) // 胡桃E后自动AAZ
	{
		if (!s_isHutaoWorking)
		{
			s_isHutaoWorking = TRUE;
			//创建工作线程
			unsigned int tid;
			HANDLE hThread = (HANDLE)_beginthreadex(nullptr, 0, CMyGenshinAssistDlg::_HutaoWorkingThread, this, CREATE_SUSPENDED, &tid);
			if (hThread == nullptr)
			{
				s_isHutaoWorking = FALSE;
				return;
			}
			::ResumeThread(hThread);
			CloseHandle(hThread);
		}
		else
		{
			s_isHutaoWorking = FALSE;
		}
	}
}

unsigned int __stdcall CMyGenshinAssistDlg::_MaweikaWorkingThread(void* param)
{
	CMyGenshinAssistDlg* pDlg = (CMyGenshinAssistDlg*)param;
	pDlg->s_isMaWeiKaWorking = TRUE;
	Sleep(GetRandomValue(200, 250));
	INPUT InputData = { 0 };
	InputData.type = INPUT_KEYBOARD;
	InputData.ki.wVk = _T('Q');
	//InputData.ki.wScan = VkKeyScan(InputData.ki.wVk);
	InputData.ki.dwFlags = 0;
	//InputData[0].ki.dwExtraInfo = GetMessageExtraInfo();
	int cbSize = sizeof(INPUT);
	CString strMsg;
	auto ret = SendInput(1, &InputData, cbSize);
	if (!ret)
	{
		auto err = GetLastError();
		strMsg.Format(_T("SendInput failed: %d\n"), err);
		OutputDebugString(strMsg);
	}
	DWORD dwSleep = GetRandomValue(100, 150);
	Sleep(dwSleep);
	InputData.ki.dwFlags = KEYEVENTF_KEYUP;
	ret = SendInput(1, &InputData, cbSize);
	if (!ret)
	{
		auto err = GetLastError();
		strMsg.Format(_T("SendInput failed: %d\n"), err);
		OutputDebugString(strMsg);
	}
	strMsg.Format(_T("Sleep time :%d\n"), dwSleep);
	OutputDebugString(strMsg);

	Sleep(1800);

	//火神开E再开Q极限能打十几套zsa，特别是6火还能回一次夜魂，但伤害最高是那死生之炉期间的免费7秒，大概是打6套，后面是消耗夜魂打
	//如果不是为了破盾，建议6套后就取消
	for (int i = 0; i < 7 && pDlg->s_isMaWeiKaWorking; ++i)  
	{		
		//Z
		ZeroMemory(&InputData, sizeof(InputData));
		InputData.type = INPUT_MOUSE;
		InputData.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		ret = SendInput(1, &InputData, cbSize);  
		dwSleep = GetRandomValue(800, 800);     
		Sleep(dwSleep);
		InputData.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		ret = SendInput(1, &InputData, cbSize);

		//S
		ZeroMemory(&InputData, sizeof(InputData));
		InputData.type = INPUT_MOUSE;
		InputData.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		ret = SendInput(1, &InputData, cbSize);
		dwSleep = GetRandomValue(125, 125);
		Sleep(dwSleep);
		InputData.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		ret = SendInput(1, &InputData, cbSize);

		if (i == 5)
		{
			break;
		}

		//A
		ZeroMemory(&InputData, sizeof(InputData));
		InputData.type = INPUT_MOUSE;
		InputData.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		ret = SendInput(1, &InputData, cbSize);
		dwSleep = GetRandomValue(125, 125);
		Sleep(dwSleep);
		InputData.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		ret = SendInput(1, &InputData, cbSize);

		Sleep(200);
	}

	pDlg->s_isMaWeiKaWorking = FALSE;
	return 0;
}

//火神zszszzps 13z 60帧 不稳定
//unsigned int __stdcall CMyGenshinAssistDlg::_MaweikaWorkingThread1(void* param)
//{
//	CMyGenshinAssistDlg* pDlg = (CMyGenshinAssistDlg*)param;
//	pDlg->s_isMaWeiKaWorking1 = TRUE;
//	Sleep(GetRandomValue(200, 250));
//	INPUT InputData = { 0 };
//	InputData.type = INPUT_KEYBOARD;
//	InputData.ki.wVk = _T('Q');
//	//InputData.ki.wScan = VkKeyScan(InputData.ki.wVk);
//	InputData.ki.dwFlags = 0;
//	//InputData[0].ki.dwExtraInfo = GetMessageExtraInfo();
//	int cbSize = sizeof(INPUT);
//	CString strMsg;
//	auto ret = SendInput(1, &InputData, cbSize);
//	Sleep(50);
//	InputData.ki.dwFlags = KEYEVENTF_KEYUP;
//	ret = SendInput(1, &InputData, cbSize);
//
//	Sleep(1650); //Q后等待下落到位
//
//	//ZZ
//	ZeroMemory(&InputData, sizeof(InputData));
//	InputData.type = INPUT_MOUSE;
//	InputData.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
//	ret = SendInput(1, &InputData, cbSize);
//	Sleep(400); 
//	InputData.mi.dwFlags = MOUSEEVENTF_LEFTUP;
//	ret = SendInput(1, &InputData, cbSize);	
//
//	Sleep(50);
//
//	ZeroMemory(&InputData, sizeof(InputData));
//	InputData.type = INPUT_MOUSE;
//	InputData.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
//	ret = SendInput(1, &InputData, cbSize);
//
//	Sleep(200);
//
//	InputData.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
//	ret = SendInput(1, &InputData, cbSize);
//
//	Sleep(50);
//
//	InputData.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
//	ret = SendInput(1, &InputData, cbSize);
//
//	Sleep(70);
//
//	InputData.mi.dwFlags = MOUSEEVENTF_LEFTUP;
//	ret = SendInput(1, &InputData, cbSize);
//
//	for (int i = 0; i < 3 && pDlg->s_isMaWeiKaWorking1; ++i)
//	{
//		Sleep(50); //松开左键后0.5秒自动打出P
//
//		ZeroMemory(&InputData, sizeof(InputData));
//		InputData.type = INPUT_MOUSE;
//		InputData.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
//		ret = SendInput(1, &InputData, cbSize);
//
//		Sleep(200);
//
//		InputData.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
//		ret = SendInput(1, &InputData, cbSize);
//		Sleep(50);
//		InputData.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
//		ret = SendInput(1, &InputData, cbSize);
//
//		Sleep(1000);
//
//		InputData.mi.dwFlags = MOUSEEVENTF_LEFTUP;
//		ret = SendInput(1, &InputData, cbSize);
//
//		Sleep(520);
//
//		InputData.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
//		ret = SendInput(1, &InputData, cbSize);
//
//		Sleep(200);
//
//		InputData.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
//		ret = SendInput(1, &InputData, cbSize);
//		Sleep(50);
//		InputData.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
//		ret = SendInput(1, &InputData, cbSize);
//
//		Sleep(70);
//		
//		InputData.mi.dwFlags = MOUSEEVENTF_LEFTUP;
//		ret = SendInput(1, &InputData, cbSize);
//	}
//
//
//	pDlg->s_isMaWeiKaWorking1 = FALSE;
//	return 0;
//}

//火神Q内12Z 60帧 很稳定
unsigned int __stdcall CMyGenshinAssistDlg::_MaweikaWorkingThread1(void* param)
{
	CMyGenshinAssistDlg* pDlg = (CMyGenshinAssistDlg*)param;
	pDlg->s_isMaWeiKaWorking1 = TRUE;
	Sleep(GetRandomValue(200, 250));
	INPUT InputData = { 0 };
	InputData.type = INPUT_KEYBOARD;
	InputData.ki.wVk = _T('Q');
	//InputData.ki.wScan = VkKeyScan(InputData.ki.wVk);
	InputData.ki.dwFlags = 0;
	//InputData[0].ki.dwExtraInfo = GetMessageExtraInfo();
	int cbSize = sizeof(INPUT);
	CString strMsg;
	auto ret = SendInput(1, &InputData, cbSize);
	Sleep(50);
	InputData.ki.dwFlags = KEYEVENTF_KEYUP;
	ret = SendInput(1, &InputData, cbSize);

	Sleep(1650); //Q后等待下落到位

	//ZZ
	//ZeroMemory(&InputData, sizeof(InputData));
	//InputData.type = INPUT_MOUSE;
	//InputData.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	//ret = SendInput(1, &InputData, cbSize);
	//Sleep(1320);
	//InputData.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	//ret = SendInput(1, &InputData, cbSize);

	for (int i = 0; i < 4 && pDlg->s_isMaWeiKaWorking1; ++i)
	{
		ZeroMemory(&InputData, sizeof(InputData));
		InputData.type = INPUT_MOUSE;
		InputData.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		ret = SendInput(1, &InputData, cbSize);

		Sleep(0);

		ZeroMemory(&InputData, sizeof(InputData));
		InputData.type = INPUT_KEYBOARD;
		InputData.ki.wVk = _T('S');
		ret = SendInput(1, &InputData, cbSize);

		Sleep(160);

		ZeroMemory(&InputData, sizeof(InputData));
		InputData.type = INPUT_MOUSE;
		InputData.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		ret = SendInput(1, &InputData, cbSize);

		Sleep(200);

		ZeroMemory(&InputData, sizeof(InputData));
		InputData.type = INPUT_MOUSE;
		InputData.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		ret = SendInput(1, &InputData, cbSize);

		Sleep(0);

		ZeroMemory(&InputData, sizeof(InputData));
		InputData.type = INPUT_MOUSE;
		InputData.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		ret = SendInput(1, &InputData, cbSize);

		Sleep(0);

		ZeroMemory(&InputData, sizeof(InputData));
		InputData.type = INPUT_KEYBOARD;
		InputData.ki.wVk = _T('S');
		InputData.ki.dwFlags = KEYEVENTF_KEYUP;
		ret = SendInput(1, &InputData, cbSize);

		if (i == 3)
		{
			break;
		}

		Sleep(50);

		ZeroMemory(&InputData, sizeof(InputData));
		InputData.type = INPUT_MOUSE;
		InputData.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		ret = SendInput(1, &InputData, cbSize);

		Sleep(150);

		ZeroMemory(&InputData, sizeof(InputData));
		InputData.type = INPUT_MOUSE;
		InputData.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		ret = SendInput(1, &InputData, cbSize);

		Sleep(20);

		ZeroMemory(&InputData, sizeof(InputData));
		InputData.type = INPUT_MOUSE;
		InputData.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		ret = SendInput(1, &InputData, cbSize);

		Sleep(1100);

		ZeroMemory(&InputData, sizeof(InputData));
		InputData.type = INPUT_MOUSE;
		InputData.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		ret = SendInput(1, &InputData, cbSize);

		Sleep(570);
	}


	pDlg->s_isMaWeiKaWorking1 = FALSE;
	return 0;
}


unsigned int __stdcall CMyGenshinAssistDlg::_AutoTaskWorkingThread(void* param)
{
	CMyGenshinAssistDlg* pDlg = (CMyGenshinAssistDlg*)param;

	Sleep(GetRandomValue(200, 250));

	for (;pDlg->s_isAutoTaskWorking;)
	{
		Sleep(GetRandomValue(0, 30));

		//F键按下
		INPUT InputData = { 0 };
		InputData.type = INPUT_KEYBOARD;
		InputData.ki.wVk = _T('F');
		//InputData.ki.wScan = VkKeyScan(InputData.ki.wVk);
		InputData.ki.dwFlags = 0;
		//InputData[0].ki.dwExtraInfo = GetMessageExtraInfo();
		int cbSize = sizeof(INPUT);
		auto ret = SendInput(1, &InputData, cbSize);
		//保持一定时间
		Sleep(GetRandomValue(0, 50));
		//F键弹起
		InputData.ki.dwFlags = KEYEVENTF_KEYUP;
		ret = SendInput(1, &InputData, cbSize);

		//Sleep(GetRandomValue(0, 30));

		//InputData.ki.wVk = _T('S');
		//InputData.ki.dwFlags = 0;
		//ret = SendInput(1, &InputData, cbSize);
		//InputData.ki.dwFlags = KEYEVENTF_KEYUP;
		//Sleep(GetRandomValue(0, 50));
		//ret = SendInput(1, &InputData, cbSize);

		////鼠标滚轮向下
		//ZeroMemory(&InputData, sizeof(InputData));
		//InputData.type = INPUT_MOUSE;
		//InputData.mi.mouseData = -1;
		//InputData.mi.dwFlags = MOUSEEVENTF_WHEEL;
		//ret = SendInput(1, &InputData, cbSize);
	}

	pDlg->s_isAutoTaskWorking = FALSE;
	return 0;
}

unsigned int __stdcall CMyGenshinAssistDlg::_AutoAttackingThread(void* param)
{
	CMyGenshinAssistDlg* pDlg = (CMyGenshinAssistDlg*)param;

	//Sleep(GetRandomValue(200, 250));

	for (; pDlg->s_isAutoAttacking;)
	{
		Sleep(GetRandomValue(20, 30));

		//F键按下
		INPUT InputData = { 0 };
		int cbSize = sizeof(INPUT);

		//模拟鼠标左键按下弹起
		InputData.type = INPUT_MOUSE;
		InputData.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		auto ret = SendInput(1, &InputData, cbSize);
		Sleep(GetRandomValue(20, 30));
		InputData.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		ret = SendInput(1, &InputData, cbSize);
	}

	pDlg->s_isAutoAttacking = FALSE;
	return 0;
}



unsigned int __stdcall CMyGenshinAssistDlg::_QiaSiKaWorkingThread(void* param)
{
	CMyGenshinAssistDlg* pDlg = (CMyGenshinAssistDlg*)param;

	Sleep(GetRandomValue(200, 250));

	//E键按下
	INPUT InputData = { 0 };
	InputData.type = INPUT_KEYBOARD;
	InputData.ki.wVk = _T('E');
	//InputData.ki.wScan = VkKeyScan(InputData.ki.wVk);
	InputData.ki.dwFlags = 0; 
	//InputData[0].ki.dwExtraInfo = GetMessageExtraInfo();
	int cbSize = sizeof(INPUT);
	auto ret = SendInput(1, &InputData, cbSize);
	//保持一定时间
	Sleep(GetRandomValue(50, 100));
	//E键弹起
	InputData.ki.dwFlags = KEYEVENTF_KEYUP;
	ret = SendInput(1, &InputData, cbSize);

	//恰斯卡满命从起飞到夜魂耗尽，10秒时间共计能打32发子弹，每发子弹计312.5毫秒,算它320毫秒

	//蓄两发
	ZeroMemory(&InputData, sizeof(InputData));
	InputData.type = INPUT_MOUSE;
	InputData.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	ret = SendInput(1, &InputData, cbSize);
	auto dwSleep = GetRandomValue(640, 680);
	Sleep(dwSleep);
	InputData.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	ret = SendInput(1, &InputData, cbSize);

	Sleep(GetRandomValue(0, 30));

	for (int i = 0; i < 3 && pDlg->s_isQiaSiKaWorking; ++i)
	{
		//秒蓄
		ZeroMemory(&InputData, sizeof(InputData));
		InputData.type = INPUT_MOUSE;
		InputData.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		ret = SendInput(1, &InputData, cbSize);
		dwSleep = GetRandomValue(50, 100);
		Sleep(dwSleep);
		InputData.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		ret = SendInput(1, &InputData, cbSize);

		Sleep(GetRandomValue(0, 30));
		if (!pDlg->s_isQiaSiKaWorking)
		{
			break;
		}

		//蓄4发
		ZeroMemory(&InputData, sizeof(InputData));
		InputData.type = INPUT_MOUSE;
		InputData.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		ret = SendInput(1, &InputData, cbSize);
		dwSleep = GetRandomValue(1680, 1720);
		Sleep(dwSleep);
		InputData.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		ret = SendInput(1, &InputData, cbSize);

		Sleep(GetRandomValue(0, 30));
		if (!pDlg->s_isQiaSiKaWorking)
		{
			break;
		}


		//蓄4发
		ZeroMemory(&InputData, sizeof(InputData));
		InputData.type = INPUT_MOUSE;
		InputData.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		ret = SendInput(1, &InputData, cbSize);
		dwSleep = GetRandomValue(1280, 1320);
		Sleep(dwSleep);
		InputData.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		ret = SendInput(1, &InputData, cbSize);

		Sleep(GetRandomValue(0, 30));
	}

	pDlg->s_isQiaSiKaWorking = FALSE;
	return 0;
}

unsigned int __stdcall CMyGenshinAssistDlg::_HutaoWorkingThread(void* param)
{
	CMyGenshinAssistDlg* pDlg = (CMyGenshinAssistDlg*)param;

	Sleep(GetRandomValue(200, 250));

	//E键按下
	INPUT InputData = { 0 };
	InputData.type = INPUT_KEYBOARD;
	InputData.ki.wVk = _T('E');
	//InputData.ki.wScan = VkKeyScan(InputData.ki.wVk);
	InputData.ki.dwFlags = 0;
	//InputData[0].ki.dwExtraInfo = GetMessageExtraInfo();
	int cbSize = sizeof(INPUT);
	auto ret = SendInput(1, &InputData, cbSize);
	//保持一定时间
	Sleep(GetRandomValue(50, 50));
	//E键弹起
	InputData.ki.dwFlags = KEYEVENTF_KEYUP;
	ret = SendInput(1, &InputData, cbSize);

	Sleep(GetRandomValue(50, 50));

	for (int i = 0; i < 11 && pDlg->s_isHutaoWorking; ++i)
	{
		//A
		ZeroMemory(&InputData, sizeof(InputData));
		InputData.type = INPUT_MOUSE;
		InputData.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		ret = SendInput(1, &InputData, cbSize);
		DWORD dwSleep= GetRandomValue(50, 50);
		Sleep(dwSleep);
		InputData.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		ret = SendInput(1, &InputData, cbSize);

		Sleep(GetRandomValue(50, 50));
		if (!pDlg->s_isHutaoWorking)
		{
			break;
		}

		//A
		ZeroMemory(&InputData, sizeof(InputData));
		InputData.type = INPUT_MOUSE;
		InputData.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		ret = SendInput(1, &InputData, cbSize);
		dwSleep = GetRandomValue(50, 50);
		Sleep(dwSleep);
		InputData.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		ret = SendInput(1, &InputData, cbSize);

		Sleep(GetRandomValue(50, 50));
		if (!pDlg->s_isHutaoWorking)
		{
			break;
		}

		//Z
		ZeroMemory(&InputData, sizeof(InputData));
		InputData.type = INPUT_MOUSE;
		InputData.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		ret = SendInput(1, &InputData, cbSize);
		dwSleep = GetRandomValue(265, 265);
		Sleep(dwSleep);
		InputData.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		ret = SendInput(1, &InputData, cbSize);

		Sleep(GetRandomValue(50, 50));
		if (!pDlg->s_isHutaoWorking)
		{
			break;
		}

		//闪
		ZeroMemory(&InputData, sizeof(InputData));
		InputData.type = INPUT_MOUSE;
		InputData.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		ret = SendInput(1, &InputData, cbSize);
		dwSleep = GetRandomValue(20, 20);
		Sleep(dwSleep);
		InputData.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		ret = SendInput(1, &InputData, cbSize);

		Sleep(GetRandomValue(20, 20));
		if (!pDlg->s_isHutaoWorking)
		{
			break;
		}


		//S键
		ZeroMemory(&InputData, sizeof(InputData));
		InputData.type = INPUT_KEYBOARD;
		InputData.ki.wVk = _T('S');
		ret = SendInput(1, &InputData, cbSize);
		//保持一定时间
		Sleep(GetRandomValue(50, 50));
		//S键弹起
		InputData.ki.dwFlags = KEYEVENTF_KEYUP;
		ret = SendInput(1, &InputData, cbSize);
		Sleep(GetRandomValue(50, 50));
		if (!pDlg->s_isHutaoWorking)
		{
			break;
		}

		//W键
		ZeroMemory(&InputData, sizeof(InputData));
		InputData.type = INPUT_KEYBOARD;
		InputData.ki.wVk = _T('W');
		ret = SendInput(1, &InputData, cbSize);
		//保持一定时间
		Sleep(GetRandomValue(50, 50));
		//S键弹起
		InputData.ki.dwFlags = KEYEVENTF_KEYUP;
		ret = SendInput(1, &InputData, cbSize);
		Sleep(GetRandomValue(50, 50));
		if (!pDlg->s_isHutaoWorking)
		{
			break;
		}

	}

	pDlg->s_isHutaoWorking = FALSE;
	return 0;
}

/*
unsigned int __stdcall CMyGenshinAssistDlg::WorkingThread(void* param)
{
	CMyGenshinAssistDlg* pDlg = (CMyGenshinAssistDlg*)param;
	pDlg->s_isWorking = TRUE;
	Sleep(300);
	INPUT InputData = { 0 };
	InputData.type = INPUT_KEYBOARD;
	InputData.ki.wVk = _T('Q');
	//InputData.ki.wScan = VkKeyScan(InputData.ki.wVk);
	InputData.ki.dwFlags = 0;
	//InputData[0].ki.dwExtraInfo = GetMessageExtraInfo();
	int cbSize = sizeof(INPUT);
	CString strMsg;
	auto ret = SendInput(1, &InputData, cbSize);
	if (!ret)
	{
		auto err = GetLastError();
		strMsg.Format(_T("SendInput failed: %d\n"), err);
		OutputDebugString(strMsg);
	}
	DWORD dwSleep = GetRandomValue(100, 150);
	Sleep(dwSleep);
	InputData.ki.dwFlags = KEYEVENTF_KEYUP;
	ret = SendInput(1, &InputData, cbSize);
	if (!ret)
	{
		auto err = GetLastError();
		strMsg.Format(_T("SendInput failed: %d\n"), err);
		OutputDebugString(strMsg);
	}
	strMsg.Format(_T("Sleep time :%d\n"), dwSleep);
	OutputDebugString(strMsg);

	Sleep(2000);

	for (int i = 0; i < 6; ++i)
	{
		Sleep(200);
		//重击
		ZeroMemory(&InputData, sizeof(InputData));
		InputData.type = INPUT_MOUSE;
		InputData.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		ret = SendInput(1, &InputData, cbSize);
		dwSleep = GetRandomValue(800, 800);
		Sleep(dwSleep);
		InputData.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		ret = SendInput(1, &InputData, cbSize);

		//闪
		ZeroMemory(&InputData, sizeof(InputData));
		InputData.type = INPUT_MOUSE;
		InputData.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		ret = SendInput(1, &InputData, cbSize);
		dwSleep = GetRandomValue(125, 125);
		Sleep(dwSleep);
		InputData.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		ret = SendInput(1, &InputData, cbSize);
	
		//A
		ZeroMemory(&InputData, sizeof(InputData));
		InputData.type = INPUT_MOUSE;
		InputData.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		ret = SendInput(1, &InputData, cbSize);
		dwSleep = GetRandomValue(125, 125);
		Sleep(dwSleep);
		InputData.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		ret = SendInput(1, &InputData, cbSize);

	}

	pDlg->s_isWorking = FALSE;
	return 0;
}
*/

void CMyGenshinAssistDlg::CheckReset()
{
	s_isMaWeiKaWorking = FALSE;
	s_isMaWeiKaWorking1 = FALSE;
	s_isAutoTaskWorking = FALSE;
	s_isAutoAttacking = FALSE;
	s_isQiaSiKaWorking = FALSE;
	s_isHutaoWorking = FALSE;
}

void CMyGenshinAssistDlg::OnBnClickedRadio2()
{
	CheckReset();
}


void CMyGenshinAssistDlg::OnBnClickedRadio1()
{
	CheckReset();
}


void CMyGenshinAssistDlg::OnBnClickedRadio4()
{
	CheckReset();
}


void CMyGenshinAssistDlg::OnBnClickedRadio3()
{
	CheckReset();
}


void CMyGenshinAssistDlg::OnBnClickedRadio5()
{
	CheckReset();
}


void CMyGenshinAssistDlg::OnBnClickedRadio6()
{
	CheckReset();
}
