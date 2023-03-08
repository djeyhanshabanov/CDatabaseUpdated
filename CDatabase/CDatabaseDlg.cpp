// CDatabaseDlg.cpp : implementation file

#include "pch.h"
#include "framework.h"
#include "CDatabase.h"
#include "CDatabaseDlg.h"
#include "afxdialogex.h"
#include "odbcinst.h"
#include "afxdb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////
// CUserContainer
CUserContainer::CUserContainer()
{
	m_BaseConnection = NULL;
};

CUserContainer::~CUserContainer()
{
	DeleteAll();
};

void CUserContainer::OnLoad()
{
	if (m_BaseConnection == NULL)
	{
		return;
	}

	CRecordset pRecordset(m_BaseConnection);

	CString strQuery, strBuff; 
	strQuery = "SELECT ID, uname, usurname, uphonenum, uemailaddress FROM usertable";
	m_BaseConnection->ExecuteSQL(strQuery);

	pRecordset.Open(CRecordset::forwardOnly, strQuery, CRecordset::readOnly);

	CUserItem* pUserItem = NULL;
	while (!pRecordset.IsEOF())
	{
		pUserItem = new CUserItem;

		pRecordset.GetFieldValue(_T("ID"), strBuff);
		pUserItem->m_nID = _wtoi(strBuff);
		pRecordset.GetFieldValue(_T("uname"), pUserItem->m_strFirstName);
		pRecordset.GetFieldValue(_T("usurname"), pUserItem->m_strLastName);
		pRecordset.GetFieldValue(_T("uphonenum"), pUserItem->m_strTelephoneNumber);
		pRecordset.GetFieldValue(_T("uemailaddress"), pUserItem->m_strEmailAddress);

		Add(pUserItem);
		pRecordset.MoveNext();
	}
};

void CUserContainer::DeleteAll()
{
	CUserItem* pUserItem;
	for (int n = 0; n <= (GetSize() - 1); n++)
	{
		pUserItem = (CUserItem*)GetAt(n);
		delete pUserItem;
	}

	RemoveAll();
};

BOOL CUserContainer::OnDeleteAll()
{
	if (m_BaseConnection == NULL)
	{
		return FALSE;
	}

	CRecordset pRecordset(m_BaseConnection);

	CString strQuery;
	strQuery.Format(L"DELETE FROM usertable");

	m_BaseConnection->ExecuteSQL(strQuery);

	return TRUE;
};

/////////////////////////////////////////////////////////
// CUserItem

CUserItem::CUserItem()
{
	m_BaseConnection = NULL;
	Clear();
};

CUserItem::~CUserItem()
{
};

void CUserItem::Clear()
{
	m_nID = -1;
	m_strFirstName.Empty();
	m_strLastName.Empty();
	m_strTelephoneNumber.Empty();
	m_strEmailAddress.Empty();
};

BOOL CUserItem::OnSave()
{
	if (m_BaseConnection == NULL)
	{
		return FALSE;
	}

	CRecordset pRecordset(m_BaseConnection);

	CString strQuery;

	if (m_nID <= 0)
	{
		strQuery.Format(L"INSERT INTO usertable(uname, usurname, uphonenum, uemailaddress) VALUES('%s', '%s', '%s', '%s')"
			, m_strFirstName, m_strLastName, m_strTelephoneNumber, m_strEmailAddress);
	}
	else
	{
		strQuery.Format(L"UPDATE usertable SET uname= '%s', usurname= '%s', uphonenum= '%s', uemailaddress= '%s' WHERE ID= %s"
			, m_strFirstName, m_strLastName, m_strTelephoneNumber, m_strEmailAddress, m_nID);
	}

	m_BaseConnection->ExecuteSQL(strQuery);

	return TRUE;
};

BOOL CUserItem::OnDelete()
{
	if (m_BaseConnection == NULL)
	{
		return FALSE;
	}

	CRecordset pRecordset(m_BaseConnection);

	CString strQuery;
	strQuery.Format(L"DELETE FROM usertable WHERE ID= %s", m_nID);

	m_BaseConnection->ExecuteSQL(strQuery);

	return TRUE;
};

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:

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


// CCDatabaseDlg dialog



CCDatabaseDlg::CCDatabaseDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CDATABASE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCDatabaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_Grid);
	DDX_Control(pDX, IDC_EDIT_ID, m_ecId);
	DDX_Control(pDX, IDC_EDIT_NAME, m_ecName);
	DDX_Control(pDX, IDC_EDIT_SURNAME, m_ecSurname);
	DDX_Control(pDX, IDC_EDIT_PHONE_NUM, m_ecPhoneNum);
	DDX_Control(pDX, IDC_EDIT_EMAIL_ADDRESS, m_ecEmailAddress);
}

BEGIN_MESSAGE_MAP(CCDatabaseDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CCDatabaseDlg::OnLvnItemchangedList)
	ON_EN_CHANGE(IDC_EDIT_ID, &CCDatabaseDlg::OnEnChangeEditId)
	ON_EN_CHANGE(IDC_EDIT_NAME, &CCDatabaseDlg::OnEnChangeEditName)
	ON_EN_CHANGE(IDC_EDIT_SURNAME, &CCDatabaseDlg::OnEnChangeEditSurname)
	ON_EN_CHANGE(IDC_EDIT_PHONE_NUM, &CCDatabaseDlg::OnEnChangeEditPhoneNum)
	ON_EN_CHANGE(IDC_EDIT_EMAIL_ADDRESS, &CCDatabaseDlg::OnEnChangeEditEmailAddress)
	ON_BN_CLICKED(IDC_ADD_BUTTON, &CCDatabaseDlg::OnBnClickedAddButton)
	ON_BN_CLICKED(IDC_UPDATE_BUTTON, &CCDatabaseDlg::OnBnClickedUpdateButton)
	ON_BN_CLICKED(IDC_DELETE_BUTTON, &CCDatabaseDlg::OnBnClickedDeleteButton)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_ALL_DATA, &CCDatabaseDlg::OnBnClickedButtonDeleteAllData)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CCDatabaseDlg::OnLvnItemchangedList)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CCDatabaseDlg::OnNMClickList1)
	ON_BN_CLICKED(IDC_READ_DATA, &CCDatabaseDlg::OnBnClickedReadData)
END_MESSAGE_MAP()


// CCDatabaseDlg message handlers

BOOL CCDatabaseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CString SqlString;
	CString userid, username, usersurname, userphonenumber, useremailaddress;
	CString sDriver = L"MICROSOFT ACCESS DRIVER (*.mdb)";
	CString sDsn, sMc;
	CString sFile;
	CString path = _T("\\userdb.mdb");
	TCHAR buffer[MAX_PATH] = { 0 };
	GetCurrentDirectory(MAX_PATH, buffer);
	sFile.Append(buffer);
	sFile.Append(path);
	sMc.Format(_T("."));

	sDsn.Format(L"ODBC;DRIVER={%s};DSN='';DBQ=%s;", sDriver, sFile);

	m_ServerConnection.Open(NULL, false, false, sDsn);
	m_oaUserContainer.m_BaseConnection = &m_ServerConnection;
	m_oUserItems.m_BaseConnection = &m_ServerConnection;
	m_oaUserContainer.OnLoad();

	UpdateGrid(&m_oaUserContainer);

	return TRUE;               // return TRUE  unless you set the focus to a control
}


void CCDatabaseDlg::OnSysCommand(UINT nID, LPARAM lParam)
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


void CCDatabaseDlg::OnPaint()
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


HCURSOR CCDatabaseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCDatabaseDlg::OnEnChangeEditId()
{
}

void CCDatabaseDlg::OnEnChangeEditName()
{
}


void CCDatabaseDlg::OnEnChangeEditSurname()
{
}


void CCDatabaseDlg::OnEnChangeEditPhoneNum()
{
}


void CCDatabaseDlg::OnEnChangeEditEmailAddress()
{
}

////////////////////////////////////////////////////////
////////////// READING DATA FROM DATABASE //////////////
////////////////////////////////////////////////////////
void CCDatabaseDlg::OnBnClickedReadData()
{
	m_oaUserContainer.DeleteAll();
	m_oaUserContainer.OnLoad();
}

///////////////////////////////////////////////////////
//////////////// ADDING DATA TO DATABASE //////////////
///////////////////////////////////////////////////////
void CCDatabaseDlg::OnBnClickedAddButton()
{
	CUserItem* lpUserItem = NULL;

	CString strFirstName, strLastName, strTelephoneNumber, strEmailAddress;
	m_ecName.GetWindowTextW(strFirstName);
	m_ecSurname.GetWindowTextW(strLastName);
	m_ecPhoneNum.GetWindowTextW(strTelephoneNumber);
	m_ecEmailAddress.GetWindowTextW(strEmailAddress);

	if (m_oaUserContainer.IsEmpty())
	{
		CUserItem* lpUserItem = NULL;
		lpUserItem = new CUserItem();

		lpUserItem->m_strFirstName = strFirstName;
		lpUserItem->m_strLastName = strLastName;
		lpUserItem->m_strTelephoneNumber = strTelephoneNumber;
		lpUserItem->m_strEmailAddress = strEmailAddress;

		lpUserItem->OnSave();
	}

	for (int i = 0; i < m_Grid.GetItemCount(); i++)
	{
		for (int j = 0; j < m_oaUserContainer.GetSize(); j++)
		{
			lpUserItem = (CUserItem*)m_oaUserContainer.GetAt(j);

			if (lpUserItem == NULL)
			{
				continue;
			}

			if (lpUserItem->m_strTelephoneNumber.Compare(m_Grid.GetItemText(i, 3)) == 0)
			{
				CString strError;
				strError.Format(L"Вече има създаден запис с този телефонен номер (%s)!", m_Grid.GetItemText(i, 3));
				AfxMessageBox(strError);
				return;
			}
		}
	}
}

///////////////////////////////////////////////////////////
//////////////// UPDATING DATA FROM DATABASE //////////////
///////////////////////////////////////////////////////////
void CCDatabaseDlg::OnBnClickedUpdateButton()
{
	int nSel = m_Grid.GetSelectionMark();
	if (nSel < 0)
	{
		return;
	}

	CString strFirstName, strLastName, strTelephoneNumber, strEmailAddress;
	m_ecName.GetWindowTextW(strFirstName);
	m_ecSurname.GetWindowTextW(strLastName);
	m_ecPhoneNum.GetWindowTextW(strTelephoneNumber);
	m_ecEmailAddress.GetWindowTextW(strEmailAddress);

	CUserItem* lpUserItem = NULL;
	lpUserItem = (CUserItem*)m_oaUserContainer.GetAt(nSel);

	lpUserItem->m_strFirstName = strFirstName;
	lpUserItem->m_strLastName = strLastName;
	lpUserItem->m_strTelephoneNumber = strTelephoneNumber;
	lpUserItem->m_strEmailAddress = strEmailAddress;

	lpUserItem->OnSave();

	UpdateGrid(&m_oaUserContainer);
}

///////////////////////////////////////////////////////////
//////////////// DELETING DATA FROM DATABASE //////////////
///////////////////////////////////////////////////////////
void CCDatabaseDlg::OnBnClickedDeleteButton()
{
	int nSel = m_Grid.GetSelectionMark();
	if (nSel < 0)
	{
		return;
	}

	CUserItem* lpUserItem = NULL;
	lpUserItem = (CUserItem*)m_oaUserContainer.GetAt(nSel);
	lpUserItem->OnDelete();

	UpdateGrid(&m_oaUserContainer);
}

///////////////////////////////////////////////////////////////
//////////////// DELETING ALL DATA FROM DATABASE //////////////
///////////////////////////////////////////////////////////////
void CCDatabaseDlg::OnBnClickedButtonDeleteAllData()
{
	m_oaUserContainer.OnDeleteAll();

	UpdateGrid(&m_oaUserContainer);
}

//////////////////////////////////////////
////////////// LIST CONTROL //////////////
//////////////////////////////////////////
void CCDatabaseDlg::OnLvnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	*pResult = 0;
}

//////////////////////////////////////////
////////////// LIST CONTROL //////////////
//////////////////////////////////////////
void CCDatabaseDlg::OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int row = m_Grid.GetSelectionMark();

	m_ecId.SetWindowText(m_Grid.GetItemText(row, 0));
	m_ecName.SetWindowText(m_Grid.GetItemText(row, 1));
	m_ecSurname.SetWindowText(m_Grid.GetItemText(row, 2));
	m_ecPhoneNum.SetWindowText(m_Grid.GetItemText(row, 3));
	m_ecEmailAddress.SetWindowText(m_Grid.GetItemText(row, 4));

	*pResult = 0;
}

////////////////////////////////////////////////
////////////// RESET LIST CONTROL //////////////
////////////////////////////////////////////////
void CCDatabaseDlg::ResetListControl()
{
	m_Grid.DeleteAllItems();

	int iNbrOfColumns = 0;
	CHeaderCtrl* pHeader = (CHeaderCtrl*)m_Grid.GetDlgItem(0);

	if (pHeader)
	{
		iNbrOfColumns = pHeader->GetItemCount();
	}

	for (int i = iNbrOfColumns; i >= 0; i--)
	{
		m_Grid.DeleteColumn(i);
	}
}

/// Clear data ///
void CCDatabaseDlg::Clear()
{
	m_ecId.SetWindowTextW(L"");
	m_ecName.SetWindowTextW(L"");
	m_ecSurname.SetWindowTextW(L"");
	m_ecPhoneNum.SetWindowTextW(L"");
	m_ecEmailAddress.SetWindowTextW(L"");
}

void CCDatabaseDlg::UpdateGrid(CUserContainer* oaUserContainer)
{
	ResetListControl();

	m_Grid.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_Grid.InsertColumn(0, L"ID", LVCFMT_LEFT, 111);
	m_Grid.InsertColumn(1, L"Name", LVCFMT_CENTER, 200);
	m_Grid.InsertColumn(2, L"Surname", LVCFMT_CENTER, 200);
	m_Grid.InsertColumn(3, L"Phone number", LVCFMT_CENTER, 200);
	m_Grid.InsertColumn(4, L"E-mail address", LVCFMT_CENTER, 200);

	if (oaUserContainer == NULL)
	{
		return;
	}

	CUserItem* lpUserItem = NULL;
	for (int j = 0; j < oaUserContainer->GetSize(); j++)
	{
		lpUserItem = (CUserItem*)oaUserContainer->GetAt(j);

		if (lpUserItem != NULL)
		{
			CString strBuff;
			strBuff.Format(_T("%d"), lpUserItem->m_nID);
			m_Grid.InsertItem(0, strBuff);
			m_Grid.SetItemText(0, 1, lpUserItem->m_strFirstName);
			m_Grid.SetItemText(0, 2, lpUserItem->m_strLastName);
			m_Grid.SetItemText(0, 3, lpUserItem->m_strTelephoneNumber);
			m_Grid.SetItemText(0, 4, lpUserItem->m_strEmailAddress);
		}
	}
};