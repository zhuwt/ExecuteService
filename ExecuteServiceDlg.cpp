
// ExecuteServiceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ExecuteService.h"
#include "ExecuteServiceDlg.h"
#include "afxdialogex.h"
#include "Resource.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExecuteServiceDlg dialog


using namespace std;
CExecuteServiceDlg::CExecuteServiceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExecuteServiceDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExecuteServiceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExecuteServiceDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDOK, &CExecuteServiceDlg::OnBnClickedOk)
    ON_BN_CLICKED(ID_BROWSER, &CExecuteServiceDlg::OnBnClickedBrowser)
    ON_BN_CLICKED(IDOK2, &CExecuteServiceDlg::OnBnClickedOk2)
END_MESSAGE_MAP()


// CExecuteServiceDlg message handlers

BOOL CExecuteServiceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	ShowWindow(SW_MINIMIZE);

    CString info(_T("服务安装命令一般与当前系统安装的.Net Framework版本相关,程序名称为:InstallUtil.exe\r\n"));
    info.Append(_T("默认路径为：C：\\Windows\\Microsoft.NET\\Framework\\），也可能2.0、3.0、4.0，都可以使用\r\n"));
    info.Append(_T("比如：C:\\Windows\\Microsoft.NET\\Framework\\v4.0.30319\r\n"));
    info.Append(_T("InstallUtil.exe \"C:\\Program Files\\MyPro\\test.exe\""));
    this->GetDlgItem(IDC_EDIT_INFORMATION)->SetWindowText(info);

    this->GetDlgItem(IDC_EDIT_COMMAND_PATH)->SetWindowText(_T("C:\\WINDOWS\\Microsoft.NET\\Framework\\v2.0.50727\\installutil.exe"));

    ShowWindow(SW_SHOWNORMAL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CExecuteServiceDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CExecuteServiceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CExecuteServiceDlg::OnBnClickedBrowser()
{
	static TCHAR BASED_CODE szFilter[] = _T("Execut Files (*.exe)|*.exe|");
    CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL, 0, TRUE);
    dlg.DoModal();

    CString fileName = dlg.GetPathName();
    GetDlgItem(IDC_EDIT_SERVICE_PATH)->SetWindowText(fileName);
}

void CExecuteServiceDlg::OnBnClickedOk()
{
    CString servicePath;
    this->GetDlgItem(IDC_EDIT_SERVICE_PATH)->GetWindowText(servicePath);
    if (servicePath.IsEmpty())
    {
        AfxMessageBox(_T("Please select a service program."));
        return ;
    }

    CString installerPath;
    this->GetDlgItem(IDC_EDIT_COMMAND_PATH)->GetWindowText(installerPath);

	//原来这里执行的时候两条命令之间使用&&来连接，现在改为&来连接的。
	//原因是：&&用来连接两条命令，但是如果命令执行失败，窗口就自动退出，执行中断随后结束。
	//		  &也是用来连接两条命令的，但是如果命令执行失败，还是会继续运行后续的命令。
    CString command;
    command.Format(_T("%s \"%s\" & pause"),installerPath,servicePath); 

    const wchar_t *p = command.GetBuffer();
    command.ReleaseBuffer();

	if (_wsystem(p) == -1)
		MessageBox(L"Looks like command running error. >_<");
    //system("pause");

}

void CExecuteServiceDlg::OnBnClickedOk2()
{
    CString servicePath;
    this->GetDlgItem(IDC_EDIT_SERVICE_PATH)->GetWindowText(servicePath);
    if (servicePath.IsEmpty())
    {
        AfxMessageBox(_T("Please select a service program."));
        return ;
    }

    CString installerPath;
    this->GetDlgItem(IDC_EDIT_COMMAND_PATH)->GetWindowText(installerPath);

	//原来这里执行的时候两条命令之间使用&&来连接，现在改为&来连接的。
	//原因是：&&用来连接两条命令，但是如果命令执行失败，窗口就自动退出，执行中断随后结束。
	//		  &也是用来连接两条命令的，但是如果命令执行失败，还是会继续运行后续的命令。
    CString command;
    command.Format(_T("%s %s /u & pause"),installerPath,servicePath);

    const wchar_t *p = command.GetBuffer();
    command.ReleaseBuffer();

    if (_wsystem(p) == -1)
		MessageBox(L"Looks like command running error. >_<");
}
