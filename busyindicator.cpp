#include "busyindicator.h"

#include <QDebug>
#include <QPainter>
#include <QPixmapCache>

BusyIndicator::BusyIndicator(QWidget *parent) :
	QWidget(parent),
	startAngle(0)
{
	setBackgroundRole(QPalette::Base);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	timer.setInterval(200);
	connect(&timer, SIGNAL(timeout()), this, SLOT(rotate()));
	timer.start();
}

void BusyIndicator::rotate()
{
	startAngle += 20;
	startAngle %= 360;
	update();
}

#if 0
void BusyIndicator::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	int side = qMin(width(), height());
	painter.translate(width() / 2, height() / 2);
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
}
#endif

QPixmap BusyIndicator::generatePixmap()
{
	qDebug() << "generating";
	QPixmap pixmap(width(), height());
	QPainter painter(&pixmap);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.fillRect(rect(), palette().color(QPalette::Background));

	int side = qMin(width(), height());
	painter.translate(width() / 2, height() / 2);
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

void BusyIndicator::paintEvent(QPaintEvent *e)
{
	QString key = QString("%1:%2:%3:%4")
						  .arg(metaObject()->className())
						  .arg(width())
						  .arg(height())
						  .arg(startAngle);
qDebug() << key;
	QPixmap pixmap;
	QPainter painter(this);

	if(!QPixmapCache::find(key, &pixmap)) {
		pixmap = generatePixmap();
		QPixmapCache::insert(key, pixmap);
	}
	painter.drawPixmap(0, 0, pixmap);
}

