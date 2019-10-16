// SettleFileViewerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SettleFileViewer.h"
#include "SettleFileViewerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


const long SETL_HEADER_SZ = 59;
const long SETL_DETAIL_SZ = 60;
const long SETL_MD_SZ = 133;
const long NETS_SETL_MD_SZ = 160;
const long QB_EXTENSION_SZ = 26;
const long POS_ID_SZ = 10;
const long TERMINAL_ID_SZ = 8;
const long MERCHANT_ID_SZ = 6;
const long SETL_FILENAME_SZ = 41;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CSettleFileViewerDlg dialog




CSettleFileViewerDlg::CSettleFileViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettleFileViewerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSettleFileViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_EDIT3, m_edit3);
	DDX_Control(pDX, IDC_EDIT4, m_edit4);
	DDX_Control(pDX, IDC_EDIT5, m_edit5);
	DDX_Control(pDX, IDC_EDIT6, m_edit6);
	DDX_Control(pDX, IDOK, m_bBrowse);
	DDX_Control(pDX, IDC_BUTTON2, m_bLoad);
	DDX_Control(pDX, IDC_LIST2, m_List2);
}

BEGIN_MESSAGE_MAP(CSettleFileViewerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CSettleFileViewerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &CSettleFileViewerDlg::OnBnClickedButton2)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &CSettleFileViewerDlg::OnNMClickList2)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CSettleFileViewerDlg::OnLvnItemchangedList2)
	ON_NOTIFY(HDN_ITEMDBLCLICK, 0, &CSettleFileViewerDlg::OnHdnItemdblclickList2)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &CSettleFileViewerDlg::OnNMDblclkList2)
END_MESSAGE_MAP()


// CSettleFileViewerDlg message handlers

BOOL CSettleFileViewerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CWnd* pWnd = GetDesktopWindow();
	CenterWindow(pWnd);


	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//ShowWindow(SW_MINIMIZE);

	// TODO: Add extra initialization here
	 m_List2.InsertColumn(0, _TEXT("Txn ID"));
	 m_List2.SetColumnWidth(0, 60);
     m_List2.InsertColumn(1, _TEXT("MD Size"));
	 m_List2.SetColumnWidth(1, 60);

     m_List2.InsertColumn(2, _TEXT("MD"));
	 m_List2.SetColumnWidth(2, 200);

	 m_List2.InsertColumn(3, _TEXT("TermID"));
	 m_List2.SetColumnWidth(3, 70);

	 m_List2.InsertColumn(4, _TEXT("POSID"));
	 m_List2.SetColumnWidth(4, 70);

 	 m_List2.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_TRACKSELECT); // LVS_LIST|LVS_SMALLICON|LVS_ICON
     m_List2.EnableScrollBar(1,0);
	
		return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSettleFileViewerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSettleFileViewerDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSettleFileViewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSettleFileViewerDlg::OnBnClickedOk()
{
	CFileDialog fdTemp(true);
	CString strTemp;

	if (fdTemp.DoModal()==IDOK)
	{
		strTemp=fdTemp.GetPathName();
		m_edit1.SetWindowText(strTemp);
	}
	//OnOK();
}

void CSettleFileViewerDlg::OnBnClickedButton2()
{
	CString strTemp;
	bool ret;

    //Get the filepath from the edit control
	m_edit1.GetWindowText(strTemp);
	m_List2.DeleteAllItems();

    ret=LoadSettleDetail(strTemp);
}

bool CSettleFileViewerDlg::LoadSettleDetail(CString strInputPathFile)
{
	CString msg;
    CFile fTemp;
	long datasz=0,lngRecSz,lngRecMDSz,detailsz,detailcnt=0, totdatasz=0, headersz=0, lngTermID=0, lngPOSID=0, lngfilename=0;
    long *ptrlngtmp;
	short txnflg=0;
	char strMDdata[ 267], strterminalid[9], strfilename[42], strPOSID[11], strSource[6], strDest[6], strNETSMDdata[341];

	unsigned char ustrrecsz[2], umsglen[1], newMDdata[133], newNETSMDdata[170];
	
	//Open the Bath file
	 if  (fTemp.Open(strInputPathFile,CFile::modeRead)==0){
		msg.Format("Error reading the file. File is being used.");
   		AfxMessageBox(msg);	
        return false;
	 }

 	unsigned char  *data = new unsigned char[63];
	

	/*attempt to read the header first, 62 bytes*/
	datasz=fTemp.Read(&data[0],62);
	fTemp.Seek(0,CFile::begin);

    //Check the header of settlement file
	if (data[0] != 'H')
	{
		msg.Format("No header indicator");
		AfxMessageBox(msg);	
		return false;
	}
	
    //Check the detail flag of settlement file
	if (data[59] != 'D')
	{
		msg.Format("No Detail indicator");
		AfxMessageBox(msg);	
		return false;
	}



	//Check the the transaction ID of settlement file
    
    switch (data[60])
	{
	case 0x02:
          //AfxMessageBox("It's NETS");	
         msg.Format("2-NETS");
		 txnflg=2;
		break;
    case 0x03:
          //AfxMessageBox("It's 3-TLCM");
		 msg.Format("3-NETS");
		 txnflg=3;
		break;
    case 0x04:
          //AfxMessageBox("It's 4-EZCM");
		 txnflg=4;
		break;
	default:
		msg.Format("No Transaction ID");
		txnflg=4;
      	 //AfxMessageBox(msg);	
		return false;
	}

	/***********************************************
	 * Check the filename inside the header
	 ***********************************************/
	 memcpy(strSource, &data[2], 5);
	 strSource[5]='\0';
	 m_edit3.SetWindowTextA(strSource);


 	/***********************************************
	 * Check the filename inside the header
	 ***********************************************/
	 memcpy(strDest, &data[7], 5);
	 strDest[5]='\0';
	 m_edit4.SetWindowTextA(strDest);

	
	/***********************************************
	 * Check the filename inside the header
	 ***********************************************/
	 memcpy(strfilename, &data[12], SETL_FILENAME_SZ);
	 //hextolong(ufilename,ptrlngtmp, SETL_FILENAME_SZ, false);
	 strfilename[SETL_FILENAME_SZ]='\0';
	 //msg.Format("%s",strfilename);
	 m_edit5.SetWindowTextA(strfilename);

 
	 /*This .setl file has maximum of 1-65535 records (0xFFFF), 2 bytes*/
	 /*Determine the number of record details at the header on 53rd byte */
	 msg="";
	 lngRecSz=0;
	 ptrlngtmp=&lngRecSz;
	 memset(ustrrecsz,0,2);
	 memcpy(ustrrecsz, &data[53], 2);
	 hextolong(ustrrecsz,ptrlngtmp,2,false);
	 msg.Format("%ld", lngRecSz);
	 //AfxMessageBox(msg);	
	 m_edit6.SetWindowTextA(msg);

	 msg="";
	 lngRecMDSz=0;
	 ptrlngtmp=&lngRecMDSz;
	 memset(umsglen,0,1);
	 memcpy(umsglen, &data[61], 1);
	 hextolong(umsglen,ptrlngtmp,1,false);
	 msg.Format("%ld", lngRecMDSz);
	 //AfxMessageBox(msg);
     

	 delete[] data;
	 data=NULL;

	 datasz=0;
	 totdatasz=0;

    /*Calculate the data size, lngRecSz always 1 for NETS*/
    if 	(txnflg==3|| txnflg==4)
	{
        totdatasz = SETL_HEADER_SZ + (SETL_MD_SZ *  lngRecSz) + QB_EXTENSION_SZ;
	} else if (txnflg==2){
	    totdatasz = SETL_HEADER_SZ + (NETS_SETL_MD_SZ  *  lngRecSz) + QB_EXTENSION_SZ;
	}

 	data = new unsigned char[totdatasz + 1];

	/*attempt to read the header first, 62 bytes*/
	datasz=fTemp.Read(&data[0],totdatasz);
	fTemp.Seek(0,CFile::begin);

    
    detailsz= datasz-SETL_HEADER_SZ;
    
	headersz=SETL_HEADER_SZ;
  //  if (txnflg==3|| txnflg==4)
//{
		/***********************************************
		 * Loop and Parse the detail
		 * detail starts with 44 04 85
		 ***********************************************/
		while(detailcnt < detailsz)
		{

			memset(strMDdata, 0, sizeof(strMDdata));
			memset(strterminalid,0,sizeof(strterminalid));		

			msg="";
			if (data[detailcnt + headersz] != 'D')
			{
				msg.Format("No detail indicator");
				AfxMessageBox(msg);	
				return false;
			}


			/**************************************************
		     * Get the Transaction ID
 		     **************************************************/
			switch (data[detailcnt + headersz + 1])
			{
			case 0x02:
				  //AfxMessageBox("It's NETS");	
				 msg.Format("2-NETS");
				 txnflg=2;
				break;
			case 0x03:
				  //AfxMessageBox("It's 3-TLCM");
				 msg.Format("3-TLCM");
				 txnflg=3;
				break;
			case 0x04:
				  //AfxMessageBox("It's 4-EZCM");
				 msg.Format("4-EZCM");
				 txnflg=4;
				break;
			default:
				msg.Format("No Transaction ID");
				txnflg=4;
      			 //AfxMessageBox(msg);	
				return false;
			}

       		m_List2.InsertItem(0,msg);

			/**************************************************
		     * Get the MD Size
 		     **************************************************/
			msg="";
			lngRecMDSz=0;
			ptrlngtmp=&lngRecMDSz;
			memset(umsglen,0,1);
			memcpy(umsglen, &data[headersz + detailcnt + 2], 1);
			hextolong(umsglen,ptrlngtmp,1,false);
			msg.Format("%ld", lngRecMDSz);
			//AfxMessageBox(msg);
	       
			m_List2.SetItemText(0,1,msg);


			/**************************************************
		     * Get the MD Data
 		     **************************************************/
            msg="";

	        /*size=1byte each */
			if (txnflg==3|| txnflg==4)
			{
				memset(newMDdata,0,lngRecMDSz);
				memcpy(newMDdata, &data[headersz + detailcnt + 3], lngRecMDSz);
				hextostrBCD(newMDdata,strMDdata,lngRecMDSz);
				msg.Format("%s", strMDdata);
			} else if (txnflg==2)
			{
				memset(newNETSMDdata,0,lngRecMDSz);
				memcpy(newNETSMDdata, &data[headersz + detailcnt + 3], lngRecMDSz);
				hextostrBCD(newMDdata,strNETSMDdata,lngRecMDSz);
				msg.Format("%s", strNETSMDdata);
			}
			m_List2.SetItemText(0,2,msg);


			/**************************************************
		     * Get the QB POS ID
 		     **************************************************/
            msg="";
			memset(strPOSID,0,sizeof(strPOSID));
			memcpy(strPOSID, &data[headersz + detailcnt +  lngRecMDSz + 3], POS_ID_SZ);
			strPOSID[POS_ID_SZ]='\0';

			m_List2.SetItemText(0,3,strPOSID);


			/**************************************************
		     * Get the QB Terminal ID
 		     **************************************************/
            msg="";
			memset(strterminalid,0,TERMINAL_ID_SZ);
			memcpy(strterminalid, &data[headersz + detailcnt + lngRecMDSz + POS_ID_SZ + 3], TERMINAL_ID_SZ);
            strterminalid[TERMINAL_ID_SZ]='\0';
			m_List2.SetItemText(0,4,strterminalid);

          

			/**************************************************
		     * Accumulate the counter
 		     **************************************************/
			detailcnt = detailcnt + lngRecMDSz + QB_EXTENSION_SZ + 3;
	

		} //end while

//	 }

	 delete[] data;
	 return true;
   
};

void CSettleFileViewerDlg::hextolong(unsigned char *txnmsgsz, long *itxnmsgsz, int sz, bool unsign)
{
	int i,negflg;
    long ret=0,y;
	int lsz=sz;
    unsigned char ntmp;
    CString x;

	ntmp=(unsigned char) txnmsgsz[0] & 0xFF;
	/* check first if it's negative */
		if ((((ntmp>> 7) & 0x01) == 1) && unsign)
			 negflg = 1;
		else
		     negflg = 0;

	/* remember MSB is the last */
	for(i=0; i<	sz; i++)
	{
     		
		if (negflg)
			y=((unsigned char) (~txnmsgsz[i]) & 0xFF)<< (8*(--lsz));
		else  
			y=(unsigned char) txnmsgsz[i] << (8*(--lsz));
  	  	
		ret=ret|y;
           
	}

	 if (negflg) 
	 {
		 ret=(ret+1) * -1;
	 }
   *itxnmsgsz= ret;

}
char CSettleFileViewerDlg::dec2hex(int digit) {
 if (digit < 10) return (digit + 48);
 switch(digit) {
  case 10: return 'A';
  case 11: return 'B';
  case 12: return 'C';
  case 13: return 'D';
  case 14: return 'E';
  case 15: return 'F';
 }
 return 0;

}

void CSettleFileViewerDlg::hextostrBCD(unsigned char *newstrCAN, char *strPTC, int sz)
{
   int i;
   char *str, *firstptr;
   CString x;


   str=strPTC;
   firstptr=str;
   for (i=0; i<sz; i++)
   {
	   *(str++)=(dec2hex((unsigned char)newstrCAN[i] >> 4));
	   *(str++)=(dec2hex((unsigned char)newstrCAN[i] & 0x0F));

   }
   *(str)='\0';
   str=firstptr;

    //x.Format("new=%s",str);
    //AfxMessageBox(x);

}

void CSettleFileViewerDlg::hextostr(unsigned char *newstrPTC, char *strPTC, int sz)
{
	int i;
	char *str,*pstr;
    CString x;

    str=strPTC;
	pstr=str;
	for(i=0;i<sz;i++)
	{
	   *(str++)=(dec2hex((unsigned char)newstrPTC[i] >> 4));
	   *(str++)=(dec2hex((unsigned char)newstrPTC[i] & 0x0F));
	}
	*str='\0';
    str=pstr;
	x.Format("new=%s",str);
    AfxMessageBox(x);

}

void CSettleFileViewerDlg::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	//m_List2.GetItemPosition(
   // m_List2.SetItemState(m_nSelectItem, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
	//m_List2.EnsureVisible(m_nSelectItem, FALSE);


	*pResult = 0;
}

void CSettleFileViewerDlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CSettleFileViewerDlg::OnHdnItemdblclickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: Add your control notification handler code here

    LVITEM *lvItem;
	int itemctrl;

	m_List2.GetItem(lvItem);
	itemctrl=lvItem->iItem;

	*pResult = 0;
}

void CSettleFileViewerDlg::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
    //Invalidate();
    HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST2);
    LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE) pNMHDR;


	
   // LVITEM *lvItem;
	int itemctrl, nSubItem;

	//m_List2.GetItem(lvItem);
	itemctrl=temp->iItem;

    nSubItem = temp->iSubItem;

   m_List2.SetItemState(itemctrl, LVN_ENDLABELEDIT, LVN_ENDLABELEDIT );
	//m_List2.EnsureVisible(nSubItem, FALSE);



	temp->uNewState= CDIS_FOCUS|CDIS_SELECTED;
	m_List2.SetSelectedColumn(nSubItem);
		m_List2.SetRedraw(1);
	CString s1=m_List2.GetItemText(itemctrl,nSubItem);

//uItemState &= ~CDIS_FOCUS;
        //                *pResult |= CDRF_NOTIFYPOSTPAINT
	if(OpenClipboard())
	{
		HGLOBAL clipbuffer;
		char * buffer;
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, s1.GetLength()+1);
		buffer = (char*)GlobalLock(clipbuffer);
		strcpy(buffer, LPCSTR(s1));
   //    strcpy_s((char*)arr, szData.GetLength(), szData.GetBuffer());
	GlobalUnlock(clipbuffer);
				GlobalUnlock(clipbuffer);

		SetClipboardData(CF_TEXT,clipbuffer);
		CloseClipboard();
   }


	*pResult = 0;
}
