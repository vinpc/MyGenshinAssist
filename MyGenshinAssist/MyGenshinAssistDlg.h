
// MyGenshinAssistDlg.h: 头文件
//

#pragma once


// CMyGenshinAssistDlg 对话框
class CMyGenshinAssistDlg : public CDialogEx
{
// 构造
public:
	CMyGenshinAssistDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYGENSHINASSIST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

private:
	BOOL m_isRegAltQ = FALSE;
	BOOL m_isRegAltE = FALSE;

	static volatile BOOL s_isMaWeiKaWorking;
	static  unsigned int __stdcall _MaweikaWorkingThread(void* param);

	static volatile BOOL s_isMaWeiKaWorking1;
	static  unsigned int __stdcall _MaweikaWorkingThread1(void* param);

	static volatile BOOL s_isAutoTaskWorking;
	static unsigned int __stdcall _AutoTaskWorkingThread(void* param);

	static volatile BOOL s_isAutoAttacking;
	static unsigned int __stdcall _AutoAttackingThread(void* param);

	static volatile BOOL s_isQiaSiKaWorking;
	static unsigned int __stdcall _QiaSiKaWorkingThread(void* param);

	static volatile BOOL s_isHutaoWorking;
	static unsigned int __stdcall _HutaoWorkingThread(void* param);

public:
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
private:
	void OnAltQ();
	void OnAltE();

public:
	void CheckReset();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
};
