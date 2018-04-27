// OptionsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TrafficMonitor.h"
#include "OptionsDlg.h"
#include "afxdialogex.h"


// COptionsDlg 对话框

IMPLEMENT_DYNAMIC(COptionsDlg, CDialog)

COptionsDlg::COptionsDlg(int tab, CWnd* pParent /*=NULL*/)
	: CDialog(IDD_OPTIONS_DIALOG, pParent), m_tab_selected{ tab }
{

}

COptionsDlg::~COptionsDlg()
{
}

void COptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
}


BEGIN_MESSAGE_MAP(COptionsDlg, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &COptionsDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// COptionsDlg 消息处理程序


BOOL COptionsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(CCommon::LoadText(IDS_TITLE_OPTION));
	//插入标签
	m_tab.InsertItem(0, CCommon::LoadText(IDS_MAIN_WINDOW_SETTINGS));
	m_tab.InsertItem(1, CCommon::LoadText(IDS_TASKBAR_WINDOW_SETTINGS));
	m_tab.InsertItem(2, CCommon::LoadText(IDS_GENERAL_SETTINGS));
	//创建子对话框
	m_tab1_dlg.Create(IDD_MAIN_WND_SETTINGS_DIALOG, &m_tab);
	m_tab2_dlg.Create(IDD_TASKBAR_SETTINGS_DIALOG, &m_tab);
	m_tab3_dlg.Create(IDD_GENERAL_SETTINGS_DIALOG, &m_tab);
	//调整子对话框的大小和位置
	CRect rect;
	m_tab.GetClientRect(rect);
	CRect rcTabItem;
	m_tab.GetItemRect(0, rcTabItem);
	rect.top += rcTabItem.Height() + 4;
	rect.left += 4;
	rect.bottom -= 4;
	rect.right -= 4;
	m_tab1_dlg.MoveWindow(&rect);
	m_tab2_dlg.MoveWindow(&rect);
	m_tab3_dlg.MoveWindow(&rect);
	//设置默认选中的标签
	switch (m_tab_selected)
	{
	case 0:
		m_tab1_dlg.ShowWindow(SW_SHOW);
		break;
	case 1:
		m_tab2_dlg.ShowWindow(SW_SHOW);
		break;
	}
	m_tab.SetCurFocus(m_tab_selected);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void COptionsDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	m_tab_selected = m_tab.GetCurSel();
	switch (m_tab_selected)
	{
	case 0:
		m_tab1_dlg.ShowWindow(SW_SHOW);
		m_tab2_dlg.ShowWindow(SW_HIDE);
		m_tab3_dlg.ShowWindow(SW_HIDE);
		m_tab1_dlg.SetFocus();
		break;
	case 1:
		m_tab2_dlg.ShowWindow(SW_SHOW);
		m_tab1_dlg.ShowWindow(SW_HIDE);
		m_tab3_dlg.ShowWindow(SW_HIDE);
		m_tab2_dlg.SetFocus();
		break;
	case 2:
		m_tab3_dlg.ShowWindow(SW_SHOW);
		m_tab1_dlg.ShowWindow(SW_HIDE);
		m_tab2_dlg.ShowWindow(SW_HIDE);
		m_tab3_dlg.SetFocus();
		break;
	}
	*pResult = 0;
}


void COptionsDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_tab1_dlg.OnOK();
	m_tab2_dlg.OnOK();
	m_tab3_dlg.OnOK();

	CDialog::OnOK();
}
