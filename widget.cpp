#include "widget.h"
#include "busyindicator.h"

#include <QLabel>
#include <QLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
	QGridLayout *layout = new QGridLayout(this);
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			layout->addWidget(new BusyIndicator, i, j );


	QLinearGradient grad(0, 0, width(), height());
	grad.setColorAt(0, Qt::red);
	grad.setColorAt(1, Qt::yellow);
	QPalette pal = palette();
	pal.setBrush(QPalette::Background, QBrush(grad));
	setPalette(pal);

}

Widget::~Widget()
{

}
