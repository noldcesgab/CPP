// SettleFileViewerDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSettleFileViewerDlg dialog
class CSettleFileViewerDlg : public CDialog
{
// Construction
public:
	CSettleFileViewerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SETTLEFILEVIEWER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton2();
	
	CEdit m_edit1;
	CEdit m_edit3;
	CEdit m_edit4;
	CEdit m_edit5;
	CEdit m_edit6;
	CButton m_bBrowse;
	CButton m_bLoad;
	CListCtrl m_List2;


	bool LoadSettleDetail(CString strPath);
	char dec2hex(int digit);
    void hextolong(unsigned char *txnmsgsz, long *itxnmsgsz, int sz, bool unsign);
	void hextostrBCD(unsigned char *newstrCAN, char *strPTC, int sz);
	void hextostr(unsigned char *newstrPTC, char *strPTC, int sz);
public:
	afx_msg void OnLvnColumnclickList2(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnHdnItemdblclickList2(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
};
