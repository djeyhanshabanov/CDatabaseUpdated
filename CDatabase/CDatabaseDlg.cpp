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
	m_BaseConnection->Close();
	delete m_BaseConnection;
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

/////////////////////////////////////////////////////////
// CUserItem

CUserItem::CUserItem()
{
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

	return TRUE;
};

BOOL CUserItem::OnDelete()
{
	CString strQuery;
	strQuery.Format(L"DELETE FROM usertable WHERE ID= %s", m_nID);

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
	, m_Name(_T(""))
	, m_Surname(_T(""))
	, m_PhoneNum(_T(""))
	, m_EmailAddress(_T(""))
	, m_Id(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCDatabaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListControl);
	DDX_Text(pDX, IDC_EDIT_ID, m_Id);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Name);
	DDX_Text(pDX, IDC_EDIT_SURNAME, m_Surname);
	DDX_Text(pDX, IDC_EDIT_PHONE_NUM, m_PhoneNum);
	DDX_Text(pDX, IDC_EDIT_EMAIL_ADDRESS, m_EmailAddress);
	DDX_Control(pDX, IDC_EDIT_ID, m_Id1);
	DDX_Control(pDX, IDC_EDIT_NAME, m_Name1);
	DDX_Control(pDX, IDC_EDIT_SURNAME, m_Surname1);
	DDX_Control(pDX, IDC_EDIT_PHONE_NUM, m_PhoneNum1);
	DDX_Control(pDX, IDC_EDIT_EMAIL_ADDRESS, m_EmailAddress1);
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
	CRUD(Action::R);
}

///////////////////////////////////////////////////////
//////////////// ADDING DATA TO DATABASE //////////////
///////////////////////////////////////////////////////
void CCDatabaseDlg::OnBnClickedAddButton()
{
	CRUD(Action::C);
}

///////////////////////////////////////////////////////////
//////////////// UPDATING DATA FROM DATABASE //////////////
///////////////////////////////////////////////////////////
void CCDatabaseDlg::OnBnClickedUpdateButton()
{
	CRUD(Action::U);
}

///////////////////////////////////////////////////////////
//////////////// DELETING DATA FROM DATABASE //////////////
///////////////////////////////////////////////////////////
void CCDatabaseDlg::OnBnClickedDeleteButton()
{
	CRUD(Action::D);
}

///////////////////////////////////////////////////////////////
//////////////// DELETING ALL DATA FROM DATABASE //////////////
///////////////////////////////////////////////////////////////
void CCDatabaseDlg::OnBnClickedButtonDeleteAllData()
{
	CRUD(Action::DA);
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

	int row = m_ListControl.GetSelectionMark();

	m_Id1.SetWindowText(m_ListControl.GetItemText(row, 0));
	m_Name1.SetWindowText(m_ListControl.GetItemText(row, 1));
	m_Surname1.SetWindowText(m_ListControl.GetItemText(row, 2));
	m_PhoneNum1.SetWindowText(m_ListControl.GetItemText(row, 3));
	m_EmailAddress1.SetWindowText(m_ListControl.GetItemText(row, 4));

	*pResult = 0;
}

////////////////////////////////////////////////
////////////// RESET LIST CONTROL //////////////
////////////////////////////////////////////////
void CCDatabaseDlg::ResetListControl()
{
	m_ListControl.DeleteAllItems();
	int iNbrOfColumns;
	CHeaderCtrl* pHeader = (CHeaderCtrl*)m_ListControl.GetDlgItem(0);
	if (pHeader) {
		iNbrOfColumns = pHeader->GetItemCount();
	}
	for (int i = iNbrOfColumns; i >= 0; i--) {
		m_ListControl.DeleteColumn(i);
	}
}

/////////////////////////////////////////////
////////////// DATABASE ACTION ////////////// 
/////////////////////////////////////////////
void CCDatabaseDlg::CRUD(int action)
{
	// TODO: Add your control notification handler code here
	CString str1 = _T("");
	CString str2 = _T("");
	CString str3 = _T("");
	CString str4 = _T("");
	CString str5 = _T("");

	m_Name1.GetWindowTextW(str1);
	m_Surname1.GetWindowTextW(str2);
	m_PhoneNum1.GetWindowTextW(str3);
	m_EmailAddress1.GetWindowTextW(str4);
	m_Id1.GetWindowTextW(str5);
		
	CDatabase database;

	// You must change above path if it's different
	int iRec = 0;
	int l = 0;
	bool isexists = false;
	bool tarsene = false;

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
	// Build ODBC connection string
	sDsn.Format(L"ODBC;DRIVER={%s};DSN='';DBQ=%s;", sDriver, sFile);

	try
	{
		// Open the database
		database.Open(NULL, false, false, sDsn);

		// Allocate the recordset
		CRecordset recset(&database);
		switch (action)
		{
			// Reading data
		case (R):
			if (!str1.IsEmpty())
			{
				SqlString = "SELECT ID, uname, usurname, uphonenum, uemailaddress FROM usertable WHERE uname LIKE '%";
				SqlString += str1;
				SqlString += "%'";
				tarsene = true;
			}
			else
			{
				SqlString = "SELECT ID, uname, usurname, uphonenum, uemailaddress " "FROM usertable";
			}
			break;

			// Adding data
		case (C):
			for (int i = 0; i < m_ListControl.GetItemCount(); i++)
			{
				CString phnnmbr = m_ListControl.GetItemText(i, 3);
				if (phnnmbr == str3)
				{
					AfxMessageBox(L"Вече има създаден запис с този телефонен номер!");
					isexists = true;
					break;
				}
			}

			if (!isexists)
			{
				SqlString.Format(L"INSERT INTO usertable(uname, usurname, uphonenum, uemailaddress) VALUES('%s', '%s', '%s', '%s')", str1, str2, str3, str4);
			}
			else SqlString = "SELECT ID, uname, usurname, uphonenum, uemailaddress " "FROM usertable";
			break;

			// Updating data
		case (U):
				SqlString.Format(L"UPDATE usertable SET uname= '%s', usurname= '%s', uphonenum= '%s', uemailaddress= '%s' WHERE ID= %s", str1, str2, str3, str4, str5);
			break;	

			// Deleting data
		case (D):
			SqlString.Format(L"DELETE FROM usertable WHERE ID= %s", str5);
			break;	

			// Deleting All data	
		case (DA):
			SqlString.Format(L"DELETE FROM usertable");
			break;
		}
		
		database.ExecuteSQL(SqlString);
		if (!tarsene)
		{
			SqlString = "SELECT ID, uname, usurname, uphonenum, uemailaddress " "FROM usertable";

		// Build the SQL statement
			SqlString = "SELECT ID, uname, usurname, uphonenum, uemailaddress " "FROM usertable";
		}

		// Execute the query
		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);

		// Reset List control if there is any data
		ResetListControl();

		// populate Grids
		m_ListControl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

		// Column width and heading
		m_ListControl.InsertColumn(0, L"ID", LVCFMT_LEFT, 111);
		m_ListControl.InsertColumn(1, L"Name", LVCFMT_CENTER, 200);
		m_ListControl.InsertColumn(2, L"Surname", LVCFMT_CENTER, 200);
		m_ListControl.InsertColumn(3, L"Phone number", LVCFMT_CENTER, 200);
		m_ListControl.InsertColumn(4, L"E-mail address", LVCFMT_CENTER, 200);

		// Loop through each record
		while (!recset.IsEOF()) {
			recset.GetFieldValue(_T("ID"), userid);
			recset.GetFieldValue(_T("uname"), username);
			recset.GetFieldValue(_T("usurname"), usersurname);
			recset.GetFieldValue(_T("uphonenum"), userphonenumber);
			recset.GetFieldValue(_T("uemailaddress"), useremailaddress);

			// Insert values into the list control
			iRec = m_ListControl.InsertItem(0, userid);
			m_ListControl.SetItemText(0, 1, username);
			m_ListControl.SetItemText(0, 2, usersurname);
			m_ListControl.SetItemText(0, 3, userphonenumber);
			m_ListControl.SetItemText(0, 4, useremailaddress);

			// goto next record
			recset.MoveNext();
		}
		// Close the database
		database.Close();
		Clear();
	}
	catch (CDBException* e)
	{
		// If a database exception occured, show error msg
		AfxMessageBox(e->m_strError);
	}
}


/// Clear data ///
void CCDatabaseDlg::Clear()
{
	m_Id1.SetWindowTextW(L"");
	m_Name1.SetWindowTextW(L"");
	m_Surname1.SetWindowTextW(L"");
	m_PhoneNum1.SetWindowTextW(L"");
	m_EmailAddress1.SetWindowTextW(L"");
}

void CCDatabaseDlg::UpdateGrid(CUserContainer* oaUserContainer)
{
	if (oaUserContainer == NULL)
	{
		return;
	}

	CUserItem* lpUserItem = NULL;
	for (int j = 0; j < oaUserContainer->GetSize(); j++)
	{
		lpUserItem = (CUserItem*)oaUserContainer->GetAt(j);

		if (lpUserItem == NULL)
		{
			break;
		}

		CString strBuff;
		strBuff.Format(_T("%d"), lpUserItem->m_nID);
		m_ListControl.InsertItem(0, strBuff);
		m_ListControl.SetItemText(0, 1, lpUserItem->m_strFirstName);
		m_ListControl.SetItemText(0, 2, lpUserItem->m_strLastName);
		m_ListControl.SetItemText(0, 3, lpUserItem->m_strTelephoneNumber);
		m_ListControl.SetItemText(0, 4, lpUserItem->m_strEmailAddress);
	}
};