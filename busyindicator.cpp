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
	timer.setInterval(100);
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

	QPainter painter(&pixmap);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.fillRect(0, 0, side, side, palette().color(QPalette::Background));

	painter.translate(side / 2, side / 2);
	painter.scale(side / 200.0, side / 200.0);

	QColor color = palette().color(QPalette::Foreground);
	QBrush brush(color);
	painter.setPen(Qt::NoPen);

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
	QString key = QString("%1:%2:%3")
						  .arg(metaObject()->className())
						  .arg(width())
						  .arg(height());
	qDebug() << key;

	QPixmap pixmap;
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	int side = qMin(width(), height());

	if(!QPixmapCache::find(key, &pixmap)) {
		pixmap = generatePixmap(side);
		QPixmapCache::insert(key, pixmap);
	}

	/* we rotate around the center of the generated pixmap square */
	painter.translate(width() / 2, height() / 2);
	painter.rotate(startAngle);
	painter.translate(-side / 2, -side / 2);

	painter.drawPixmap(0, 0, side, side, pixmap);
}

