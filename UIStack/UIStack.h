#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_UIStack.h"
#include <DockManager.h>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include "SideBarWidget.h"

using namespace ads;

template<typename T>
void safe_delete(T * & t)
{
    if (t)
    {
        delete t;
        t = nullptr;
    }
}

namespace Ui
{
    UIStack;
}


class UIStack : public QMainWindow
{
    Q_OBJECT

public:
    UIStack(QWidget *parent = nullptr);
    ~UIStack();

    void makeGUI();
    void makeButtonToChangeMainSheet();
    void changeQssFile(const bool& bOn);
    QString getQssFileName(const bool& bOn);
    void setUPGUI();
    void makeSideWidget();
    void makeAddAction(QAction* pAction, const QString& strName, const QString& strIcon);

private:
    Ui::UIStack* ui;
    CDockManager* m_pDockerManager{ nullptr };
    QToolButton* m_pToggleButton;

    QAction* m_actChart;
    QAction* m_actImageViewer;
    QAction* m_act3DViewer;
    
    Sidebar* m_pSideBarWidget{ nullptr };


protected:
    void paintEvent(QPaintEvent* event) override;

};
