
// CDatabaseDlg.h : header file
//

#pragma once
#include "odbcinst.h"
#include "afxdb.h"
#include <ntddndis.h>

class CUserContainer : public CObArray
{
public:
	CUserContainer();
	~CUserContainer();

	CDatabase* m_BaseConnection;

	void OnLoad();
	void DeleteAll();
	BOOL OnDeleteAll();
};

class CUserItem : public CObject
{
public:
	CUserItem();
	~CUserItem();

	CDatabase* m_BaseConnection;

	int m_nID;
	CString m_strFirstName; // Лично име
	CString m_strLastName; // Фамилно име
	CString m_strTelephoneNumber; // Телефонен номер
	CString m_strEmailAddress; // Електронна поща

	void Clear();
	BOOL OnSave();
	BOOL OnDelete();
};

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
	void CCDatabaseDlg::Clear();

	CEdit m_ecId;
	CEdit m_ecName;
	CEdit m_ecSurname;
	CEdit m_ecPhoneNum;
	CEdit m_ecEmailAddress;

	CListCtrl m_Grid;

	CDatabase m_ServerConnection;
	CUserContainer m_oaUserContainer;
	CUserItem m_oUserItems;
	void UpdateGrid(CUserContainer* oaUserContainer);
};