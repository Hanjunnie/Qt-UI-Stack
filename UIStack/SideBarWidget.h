#pragma once

#include <QWidget>
#include "ui_SideBarWidget.h"
#include "Sidebar.h"

class SideBarWidget : public QWidget
{
	Q_OBJECT

public:
	SideBarWidget(QWidget *parent = nullptr);
	~SideBarWidget();

	void addAction(QAction* act);

private:
	Ui::SideBarWidget ui;

	Sidebar* m_pSideBar{ nullptr };
};
