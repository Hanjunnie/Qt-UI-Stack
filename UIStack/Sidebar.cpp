#include "Sidebar.h"
#include <QStyleOption>
#include <QStyle>
#include <QPainter>

Sidebar::Sidebar(QWidget *parent)
	: QDockWidget(parent)
{
	setMouseTracking(true);
}

Sidebar::~Sidebar()
{}

void Sidebar::addAction(QAction * action)
{
	auto iter = find_if(m_listAction.begin(), m_listAction.end(), [&](const QAction* act)
		{
			return act == action;
		});

	if (iter != m_listAction.end())
		return;

	m_listAction.emplace_back(action);
	action->setChecked(true);
	update();
}

void Sidebar::makeGUI()
{
}

void Sidebar::paintEvent(QPaintEvent* e)
{
	QStyleOptionHeader opt;
	opt.initFrom(this);
	QPainter painter(this);

	style()->drawPrimitive(QStyle::PE_Frame,&opt, &painter, this);

	painter.setPen(QColor("#32414B"));
	QRect rtFrame = rect();
	rtFrame.adjust(0, 0, -1, -1);
	painter.drawRect(rtFrame);

	int action_y = 0;
	const int action_height = 90;

	painter.save();

	for (auto action : m_listAction)
	{
		QRectF actionRect(0, action_y, e->rect().width(), action_height);

		if (action->isChecked())
		{
			painter.fillRect(actionRect.toRect(), QColor("#32414B"));
		}

		// 		if (action == m_listAction) {
		// 			painter.fillRect(actionRect.toRect(), QColor("#148CD2"));
		// 		}

		painter.setPen(QColor("#F0F0F0"));
		QSize size = painter.fontMetrics().size(Qt::TextSingleLine, action->text());
		QRect actionTextRect(QPoint(actionRect.width() / 2 - size.width() / 2, actionRect.bottom() - size.height() - 5), size);
		painter.drawText(actionTextRect, Qt::AlignCenter, action->text());

		QRect actionIconRect(0, action_y + 10, actionRect.width(), actionRect.height() - 2 * actionTextRect.height() - 10);
		QIcon  actionIcon(action->icon());
		actionIcon.paint(&painter, actionIconRect);

		action_y += actionRect.height();
	}
}
