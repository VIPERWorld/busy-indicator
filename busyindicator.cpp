#include "busyindicator.h"

#include <QDebug>
#include <QPainter>
#include <QPixmapCache>

BusyIndicator::BusyIndicator(QWidget *parent) :
	QWidget(parent),
	startAngle(0)
{
	QSizePolicy policy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	policy.setHeightForWidth(true);
	setSizePolicy(policy);

	timer.setInterval(50);
	connect(&timer, SIGNAL(timeout()), this, SLOT(rotate()));
	timer.start();
}

void BusyIndicator::rotate()
{
	startAngle += 20;
	startAngle %= 360;
	update();
}

QPixmap BusyIndicator::generatePixmap(int side)
{
	qDebug() << "generate";
	QPixmap pixmap(QSize(side, side));
	pixmap.fill(QColor(255, 255, 255, 0));

	QPainter painter(&pixmap);
	painter.setRenderHint(QPainter::Antialiasing);

	painter.translate(side / 2, side / 2);
	painter.scale(side / 200.0, side / 200.0);

	QColor color = palette().color(QPalette::Foreground);
	QBrush brush(color);
	painter.setPen(Qt::NoPen);

	painter.rotate(startAngle);

	float angle = 0;
	while (angle < 360) {
		painter.setBrush(brush);
		painter.drawRect(-5, -100, 10, 30);
		painter.rotate(20);
		angle += 20;

		color.setAlphaF(angle / 360);
		brush.setColor(color);
	}

	return pixmap;
}

void BusyIndicator::paintEvent(QPaintEvent *)
{
	QString key = QString("%1:%2:%3:%4")
						  .arg(metaObject()->className())
						  .arg(width())
						  .arg(height())
						  .arg(startAngle);

	QPixmap pixmap;
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	int side = qMin(width(), height());

	if(!QPixmapCache::find(key, &pixmap)) {
		pixmap = generatePixmap(side);
		QPixmapCache::insert(key, pixmap);
	}

	painter.translate(width() / 2 - side / 2, height() / 2 - side / 2);

	painter.drawPixmap(0, 0, side, side, pixmap);
}

QSize BusyIndicator::minimumSizeHint() const
{
	return QSize(20, 20);
}

QSize BusyIndicator::sizeHint() const
{
	return QSize(30, 30);
}
