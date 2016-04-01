
// ExecuteServiceDlg.h : header file
//

#pragma once


// CExecuteServiceDlg dialog
class CExecuteServiceDlg : public CDialogEx
{
// Construction
public:
	CExecuteServiceDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_EXECUTESERVICE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedBrowser();
    afx_msg void OnBnClickedOk2();
};
