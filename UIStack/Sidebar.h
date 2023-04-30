#pragma once
#include <QWidget>
#include <QPaintEvent>
#include <QdockWidget>

class Sidebar  : public QDockWidget
{
	Q_OBJECT

public:
	explicit Sidebar(QWidget *parent =nullptr);
	~Sidebar();

	void addAction(QAction* action);
	void makeGUI();

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	std::list<QAction*> m_listAction;
};
