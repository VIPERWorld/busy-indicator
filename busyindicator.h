#ifndef BUSYINDICATOR_H
#define BUSYINDICATOR_H

#include <QTimer>
#include <QWidget>

class BusyIndicator : public QWidget
{
    Q_OBJECT
public:
	explicit BusyIndicator(QWidget *parent = 0);

	void paintEvent(QPaintEvent *);
	QSize minimumSizeHint() const;
	QSize sizeHint() const;

signals:

private slots:
	void rotate();

private:
	QPixmap generatePixmap(int sideLength);
	QTimer timer;
	int startAngle;
};

#endif // BUSYINDICATOR_H
