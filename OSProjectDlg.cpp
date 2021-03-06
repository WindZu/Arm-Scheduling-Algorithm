
// OSProjectDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "OSProject.h"
#include "OSProjectDlg.h"
#include "afxdialogex.h"
//#include "DataList.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// COSProjectDlg 对话框



COSProjectDlg::COSProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_OSPROJECT_DIALOG, pParent)
	, inputStr(_T(""))
	, outputStr(_T(""))
	, outputDis(_T(""))
	, lastNum(0)
	, currentNum(0)
	, cylinderNum(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COSProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, inputStr);
	DDX_Text(pDX, IDC_EDIT4, outputStr);
	DDX_Text(pDX, IDC_EDIT5, outputDis);
	DDX_Text(pDX, IDC_EDIT1, lastNum);
	DDX_Text(pDX, IDC_EDIT2, currentNum);
	DDX_Text(pDX, IDC_EDIT6, cylinderNum);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
}

BEGIN_MESSAGE_MAP(COSProjectDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &COSProjectDlg::OnBnClickedExecute)
END_MESSAGE_MAP()


// COSProjectDlg 消息处理程序

BOOL COSProjectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void COSProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void COSProjectDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR COSProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//CString 分割“，”,存入int数组
void COSProjectDlg::StringToIntArr(CString str, int data[])
{
	int i = 0, pos;
	while (str != "")
	{
		pos = str.Find(',', 0);
		if (pos<0)//要对最后一个数据作处理, 要不会死循环  
		{
			data[i] = atoi(str);
			break;
		}
		data[i] = atoi(str.Left(pos));
		str.Delete(0, pos + 1);
		i++;
	}
}


//初始化链表
void COSProjectDlg::initList(DataList &dataList, int currentNum, int list[])
{
	dataList.addNode(currentNum);

	for (int i = 0; i<len; i++)
		dataList.addNode(list[i]);


}
//按照链表节点顺序输出
void COSProjectDlg::pushList(DataList &dataList)
{
	Node *temp = dataList.head;
	while (temp->next != NULL)
	{
		CString a;
		a.Format("%d", temp->data);
		outputStr = outputStr + a + "->";
		//cout << temp->data << "->";
		temp = temp->next;
	}
	CString c;
	//c.Format("%d", len);
	c.Format("%d", temp->data);
	outputStr = outputStr + c ;
	//cout << temp->data;
	//cout << endl;

	int sum = 0;
	Node *temp1 = dataList.head;

	while (temp1->next != NULL)
	{
		int q = 0;
		q = abs((temp1->next->data) - (temp1->data));
		sum += q;
		//cout << q << "+";
		//list[i]
		//CString a;
		//a.Format("%d", q);
		//outputDis = outputDis + a + "+";
		temp1 = temp1->next;
	}
	CString b;
	b.Format("%d", sum);
	//outputDis = outputDis +"="+b;
	outputDis = b;
	//cout << "=" << sum;
	//cout << endl;
}
//寻找距离最近点
void COSProjectDlg::lookNearest(DataList &dataList)
{
	Node *currentNode = dataList.head;
	while (currentNode->next->next != NULL)
	{
		Node *temp = currentNode;
		int min = 9999;
		int tempData = temp->data;
		Node *preNode = NULL;
		while (temp->next != NULL)
		{
			int tempNum = abs((temp->next->data) - tempData);
			if (tempNum<min)
			{
				min = tempNum;
				preNode = temp;//记录当前“减数”的前一个节点，用于找出最近节点后的节点交换
			}
			temp = temp->next;
		}
		if (preNode->data == currentNode->data)
		{
		}
		else if (currentNode->next->data == preNode->data)
		{
			Node *p = currentNode->next;
			Node *q = preNode->next;

			currentNode->next = q;
			p->next = q->next;
			q->next = p;
		}
		else
		{
			Node *aPre = currentNode;
			Node *a = currentNode->next;
			Node *aNext = currentNode->next->next;

			Node *bPre = preNode;
			Node *b = preNode->next;
			Node *bNext = preNode->next->next;

			aPre->next = b;
			b->next = aNext;

			bPre->next = a;
			a->next = bNext;
		}
		currentNode = currentNode->next;
	}
}
//根据“方向”参数，对数组进行排序
void COSProjectDlg::sort(bool dir, int list[])
{
	if (dir)
	{
		int temp = 0;
		for (int i = 0; i<len - 1; i++)
			for (int j = 0; j<len - 1 - i; j++)//冒泡排序，从小到大
				if (list[j]>list[j + 1])
				{
					temp = list[j];
					list[j] = list[j + 1];
					list[j + 1] = temp;
				}
	}
	else
	{
		int temp = 0;
		for (int i = 0; i<len - 1; i++)
			for (int j = 0; j<len - 1 - i; j++)//冒泡排序，从大到小
				if (list[j]<list[j + 1])
				{
					temp = list[j];
					list[j] = list[j + 1];
					list[j + 1] = temp;
				}
	}
}

//先来先服务
void COSProjectDlg::FifoVisit()
{
	DataList dataList;
	initList(dataList, currentNum, list);

	pushList(dataList);

}

//最短寻找时间优先
void COSProjectDlg::SsfoVisit()
{
	DataList dataList;
	initList(dataList, currentNum, list);
	lookNearest(dataList);//按照最近距离排序节点
	pushList(dataList);
}

//电梯调度
void COSProjectDlg::DtVisit()
{
	DataList dataList;
	int *arr = new int[len];
	memset(arr, 0, sizeof(arr));

	int *arr1 = new int[len];
	int *arr2 = new int[len];
	for (int i = 0; i<len; i++)
	{
		arr1[i] = list[i];
		arr2[i] = list[i];
	}
	sort(true, arr1);//从小到大
	sort(false, arr2);//从大到小

	int d = currentNum - lastNum;
	//cout<<d;
	if (d>0)
	{//先从小到大，然后从大到小
		int i = 0;
		while (arr1[i]<currentNum)
			i++;
		int j = 0;
		for (int k = i; k<len; k++)
		{
			arr[j] = arr1[k];
			j++;
		}

		i = 0;
		while (arr2[i]>currentNum)
			i++;
		for (int h = i; h<len; h++)
		{
			arr[j] = arr2[h];
			j++;
		}
	}
	else
	{//先从大到小，然后从小到大
		int i = 0;
		while (arr2[i]>currentNum)
			i++;
		int j = 0;
		for (int k = i; k<len; k++)
		{
			arr[j] = arr2[k];
			j++;
		}

		i = 0;
		while (arr1[i]<currentNum)
			i++;
		for (int h = i; h<len; h++)
		{
			arr[j] = arr1[h];
			j++;
		}
	}

	delete arr1, arr2;
	initList(dataList, currentNum, arr);
	pushList(dataList);
	delete arr;
}

//单向调度
void COSProjectDlg::DxVisit()
{
	DataList dataList;
	int *arr = new int[len];
	memset(arr, 0, sizeof(arr));
	int *arr1 = new int[len];
	for (int i = 0; i<len; i++)
	{
		arr1[i] = list[i];
	}
	sort(true, arr1);//从小到大

	int m = 0;
	while (arr1[m]<currentNum)
		m++;

	int k = 0;
	int l = m;
	for (int n = m; n<len; n++)
	{
		arr[k] = arr1[n];
		k++;
	}

	for (int c = 0; c<l; c++)
	{
		arr[k] = arr1[c];
		k++;
	}
	delete arr1;
	int dis = cylinderNum - (currentNum - arr[len-1]);
	CString a;
	a.Format("%d", dis);
	initList(dataList, currentNum, arr);
	pushList(dataList);
	outputDis = a;
	delete arr;

	
}


void COSProjectDlg::OnBnClickedExecute()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取输入数据
	UpdateData();
	outputDis = "";
	outputStr = "";
	
	//输入数据转化存入list数组，并确定数组长度
	memset(list, 0, sizeof(list));
	StringToIntArr(inputStr,list);
	len = 0;
	while (list[len] != 0)
	{
		len++;
	}
	switch (m_combo.GetCurSel())
	{
	case 0:
		FifoVisit();//先来先服务
		break;
	case 1:
		SsfoVisit();//最短寻找时间优先
		break;
	case 2:
		DtVisit();//电梯调度
		break;
	case 3:
		DxVisit();//单向调度
		break;
	default :
		break;
	}

	UpdateData(false);

}
