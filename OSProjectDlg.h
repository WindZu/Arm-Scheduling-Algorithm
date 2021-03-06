
// OSProjectDlg.h: 头文件
//

#pragma once
#include "afxwin.h"
#include "DataList.h"


// COSProjectDlg 对话框
class COSProjectDlg : public CDialog
{
// 构造
public:
	COSProjectDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OSPROJECT_DIALOG };
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
	afx_msg void OnBnClickedExecute();

	void FifoVisit();//先来先服务
	void SsfoVisit();//最短寻找时间优先
	void DtVisit();//电梯调度
	void DxVisit();//单向调度
	void initList(DataList &dataList, int currentNum, int list[]);//初始化链表
	void pushList(DataList &dataList);//按照链表节点顺序输出
	void lookNearest(DataList &dataList);//寻找距离最近点
	void sort(bool dir, int list[]);//根据“方向”参数，对数组进行排序
	void StringToIntArr(CString str, int data[]);//CString 分割“，”,存入int数组

	CString inputStr;
	CString outputStr;
	CString outputDis;

	int len;
	int list[15];
	int lastNum;
	int currentNum;
	int cylinderNum;
	CComboBox m_combo;
};
