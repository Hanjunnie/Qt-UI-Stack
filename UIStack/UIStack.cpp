#include "UIStack.h"
#include <DockWidget.h>
#include <DockComponentsFactory.h>
#include <QToolButton>
#include <DockContainerWidget.h>
#include <DockAreaWidget.h>
#include <QdockWidget>

#include <QFile>

UIStack::UIStack(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::UIStack)
{
     ui->setupUi(this);
 	CDockManager::setConfigFlags(CDockManager::DefaultNonOpaqueConfig);
 	ads::CDockManager::setConfigFlag(ads::CDockManager::XmlCompressionEnabled, false);
 	ads::CDockManager::setConfigFlag(ads::CDockManager::FocusHighlighting, false);
 	ads::CDockManager::setConfigFlag(ads::CDockManager::ActiveTabHasCloseButton, false);
 	ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaHasCloseButton, false);
 
 	ads::CDockManager::setAutoHideConfigFlags(ads::CDockManager::DefaultAutoHideConfig);

 	m_pDockerManager = new CDockManager(this);
 	m_pDockerManager->sideTabBar(SideBarRight);

	setCentralWidget(m_pDockerManager);
 	// CDockWidget 생성
 	auto label = new QLabel("test2");
 	auto dockWidget1 = new CDockWidget("DockWidget", label);
 	m_pDockerManager->addDockWidget(RightDockWidgetArea, dockWidget1); 

	makeGUI();
}

UIStack::~UIStack()
{
    safe_delete(ui);
    safe_delete(m_pDockerManager);
	safe_delete(m_actChart);
}

void UIStack::makeGUI()
{
	setUPGUI();
	makeButtonToChangeMainSheet();
}

void UIStack::changeQssFile(const bool& bOn)
{
	QFile file(getQssFileName(bOn));
	if (file.exists())
	{
		file.open(QFile::ReadOnly | QFile::Text);
		QTextStream ts(&file);
		QString strContents = ts.readAll();
		qApp->setStyleSheet(strContents);
		m_pDockerManager->setStyleSheet(strContents);
	}

}

QString UIStack::getQssFileName(const bool& bOn)
{
	if (bOn)
		return QString(":/qss/light.qss");

	return QString(":/qss/dark.qss");
}

void UIStack::makeAddAction(QAction* pAction, const QString& strName, const QString& strIcon)
{
	pAction = new QAction(strName, this);
	pAction->setIcon(QIcon(strIcon));
	m_pSideBarWidget->addAction(pAction);
}

void UIStack::makeSideWidget()
{
	ui->menuBar->addMenu("Gggg");

	m_pSideBarWidget = new Sidebar(this);
	m_pSideBarWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_pSideBarWidget->setTitleBarWidget(new QWidget());// titlebbar 제거 [4/21/2023 jhHan]
	m_pSideBarWidget->setFixedWidth(100);
	m_pSideBarWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);


	addDockWidget(Qt::LeftDockWidgetArea, m_pSideBarWidget);
	setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);

}

void UIStack::paintEvent(QPaintEvent* event)
{
}

void UIStack::setUPGUI()
{
	makeSideWidget();
	makeAddAction(m_actChart, "chart", ":/svg/chart-area.svg");
	makeAddAction(m_actImageViewer, "Image Viewer", ":/svg/photo.svg");
	makeAddAction(m_act3DViewer, "chart", ":/svg/chart-area.svg");

}

void UIStack::makeButtonToChangeMainSheet()
{
	m_pToggleButton = new QToolButton(this);
	m_pToggleButton->setCheckable(true);
	m_pToggleButton->setIcon(QIcon(":/svg/toggle-off.svg"));
	connect(m_pToggleButton, &QToolButton::toggled, [&](const bool& bOn)
		{
			changeQssFile(bOn);

			if (bOn)
				m_pToggleButton->setIcon(QIcon(":/svg/toggle-off.svg"));
			else
				m_pToggleButton->setIcon(QIcon(":/svg/toggle-on.svg"));
		});

	ui->statusBar->addWidget(m_pToggleButton);
}
