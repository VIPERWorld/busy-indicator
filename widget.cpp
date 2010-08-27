#include "widget.h"
#include "busyindicator.h"

#include <QLabel>
#include <QLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
	QGridLayout *layout = new QGridLayout(this);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			BusyIndicator *ind = new BusyIndicator(this);
			if (i % 3 == 0)
				ind->setIndicatorStyle(BusyIndicator::StyleRect);
			else if (i % 3 == 1)
				ind->setIndicatorStyle(BusyIndicator::StyleEllipse);
			else
				ind->setIndicatorStyle(BusyIndicator::StyleArc);
			layout->addWidget(ind, i, j );
		}
	}


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
