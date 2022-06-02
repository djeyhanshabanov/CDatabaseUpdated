
// CDatabaseDlg.h : header file
//

#pragma once
#include "odbcinst.h"
#include "afxdb.h"
#include <ntddndis.h>



// CCDatabaseDlg dialog
class CCDatabaseDlg : public CDialogEx
{
// Construction
public:
	CCDatabaseDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDATABASE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	void ResetListControl();                            // Method

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
	enum Action : uint8_t
	{
		C = 1,
		R = 2,
		D = 3,
		U = 4,
		DA = 5,
		N = 0 
	};
	CListCtrl m_ListControl;	
	CString m_Id;                   // Variable (Value)
	CString m_Name;                 // Variable (Value)
	CString m_Surname;              // Variable (Value)
	CString m_PhoneNum;             // Variable (Value)
	CString m_EmailAddress;         // Variable (Value)
	afx_msg void OnEnChangeEditId();
	afx_msg void OnEnChangeEditName();
	afx_msg void OnEnChangeEditSurname();
	afx_msg void OnEnChangeEditPhoneNum();
	afx_msg void OnEnChangeEditEmailAddress();
	afx_msg void OnBnClickedAddButton();
	afx_msg void OnBnClickedUpdateButton();
	afx_msg void OnBnClickedDeleteButton();
	afx_msg void OnBnClickedButtonDeleteAllData();
	afx_msg void OnBnClickedReadData();
	afx_msg void OnLvnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg afx_msg void OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	void CCDatabaseDlg::CRUD(int action);
	CEdit m_Id1;                    // Variable (Control)
	CEdit m_Name1;                  // Variable (Control)
	CEdit m_Surname1;               // Variable (Control)
	CEdit m_PhoneNum1;              // Variable (Control)
	CEdit m_EmailAddress1;          // Variable (Control)
	void CCDatabaseDlg::Clear();
};
