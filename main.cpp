#include <QtGui/QApplication>
#include "widget.h"
#include "busyindicator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	Widget w;
	w.show();

	BusyIndicator b;
	//b.show();

    return a.exec();
}
