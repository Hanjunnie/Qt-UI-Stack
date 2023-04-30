#include "SideBarWidget.h"

SideBarWidget::SideBarWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_pSideBar = new Sidebar();
	auto layout = new QHBoxLayout();
	layout->addWidget(m_pSideBar);
	setLayout(layout);
}

SideBarWidget::~SideBarWidget()
{
}

void SideBarWidget::addAction(QAction* act)
{
	m_pSideBar->addAction(act);
}
