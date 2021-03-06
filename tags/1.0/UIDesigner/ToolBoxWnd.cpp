// ToolBoxWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "UIDesigner.h"
#include "ToolBoxWnd.h"

//////////////////////////////////////////////////////////////////////////
// CToolBoxWnd

IMPLEMENT_DYNAMIC(CToolBoxWnd, CDockablePane)

CToolBoxWnd::CToolBoxWnd()
{
	g_pToolBoxWnd=this;
}

CToolBoxWnd::~CToolBoxWnd()
{
}


BEGIN_MESSAGE_MAP(CToolBoxWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CToolBoxWnd 消息处理程序

int CToolBoxWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CRect rectDummy;
	rectDummy.SetRectEmpty();
	if (!m_ctlToolList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 12))
	{
		TRACE0("Failed to create ToolBox\n");
		return -1;      // fail to create
	}
	InitToolList();

	return 0;
}

void CToolBoxWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	AdjustLayout();
}

void CToolBoxWnd::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	m_ctlToolList.SetWindowPos(NULL, rectClient.left,rectClient.top,rectClient.Width(),rectClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
}

void CToolBoxWnd::InitToolList()
{
	CToolElement* pControlTab=new CToolElement(_T("控件"));
	pControlTab->AddSubTool(new CToolElement(_T("指针"),classPointer,IDI_PROPERTIES_WND_HC));
	pControlTab->AddSubTool(new CToolElement(_T("按钮"),classButton,IDI_PROPERTIES_WND_HC));
	pControlTab->AddSubTool(new CToolElement(_T("基础控件"),classControl,IDI_PROPERTIES_WND_HC));
	pControlTab->AddSubTool(new CToolElement(_T("标签"),classLabel,IDI_PROPERTIES_WND_HC));
	pControlTab->AddSubTool(new CToolElement(_T("文本框"),classText,IDI_PROPERTIES_WND_HC));
	pControlTab->AddSubTool(new CToolElement(_T("编辑框"),classEdit,IDI_PROPERTIES_WND_HC));
	pControlTab->AddSubTool(new CToolElement(_T("复选框"),classOption,IDI_PROPERTIES_WND_HC));
	pControlTab->AddSubTool(new CToolElement(_T("组合框"),classCombo,IDI_PROPERTIES_WND_HC));
	pControlTab->AddSubTool(new CToolElement(_T("进度条"),classProgress,IDI_PROPERTIES_WND_HC));
	pControlTab->AddSubTool(new CToolElement(_T("滑块"),classSlider,IDI_PROPERTIES_WND_HC));
	pControlTab->AddSubTool(new CToolElement(_T("ActiveX控件"),classActiveX,IDI_PROPERTIES_WND_HC));
	m_ctlToolList.AddToolTab(pControlTab);

	CToolElement* pLayoutTab=new CToolElement(_T("布局"));
	pLayoutTab->AddSubTool(new CToolElement(_T("垂直布局"),classVerticalLayout,IDI_PROPERTIES_WND_HC));
	pLayoutTab->AddSubTool(new CToolElement(_T("水平布局"),classHorizontalLayout,IDI_PROPERTIES_WND_HC));
	pLayoutTab->AddSubTool(new CToolElement(_T("容器"),classContainer,IDI_PROPERTIES_WND_HC));
	pLayoutTab->AddSubTool(new CToolElement(_T("对话框布局"),classDialogLayout,IDI_PROPERTIES_WND_HC));
	pLayoutTab->AddSubTool(new CToolElement(_T("并列布局"),classTileLayout,IDI_PROPERTIES_WND_HC));
	pLayoutTab->AddSubTool(new CToolElement(_T("选项页布局"),classTabLayout,IDI_PROPERTIES_WND_HC));
	m_ctlToolList.AddToolTab(pLayoutTab);

	m_ctlToolList.SetCurSel(classPointer);
}