#include "UIStack.h"
#include <QtWidgets/QApplication>
#include <QMessageBox>
#include "RunGuard.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	//중복 실행 막아주는 기능 필요
	RunGuard runguard(a.applicationName());
	if (not runguard.tryToRun())
	{
		QMessageBox::warning(nullptr, "Warning", QString("%1 already running!").arg(a.applicationName()));
		return 0;
	}

    UIStack w;
	w.showMaximized();
    w.show();
    return a.exec();
}
