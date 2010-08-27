#include "widget.h"
#include "busyindicator.h"

#include <QLabel>
#include <QLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
	QVBoxLayout *layout = new QVBoxLayout(this);
	BusyIndicator *busyIndicator = new BusyIndicator(this);
	layout->addWidget(busyIndicator);

	//QLabel *label = new QLabel("WTF?", this);
	//layout->addWidget(label);
}

Widget::~Widget()
{

}
