#include <QtGui/QApplication>
#include "widget.h"
#include "busyindicator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // Widget w;
   // w.show();

	BusyIndicator b;
	QPalette pal = b.palette();
	pal.setColor(QPalette::Background, Qt::darkYellow);
	b.setPalette(pal);
	b.show();

    return a.exec();
}
