
#include "CommonHeaders.h"
#include <QtWidgets>
#include "DigitalClock.h"

DigitalClock::DigitalClock(QWidget *parent)
: QLCDNumber(parent)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
	timer->start(1000);

	showTime();
}

void DigitalClock::showTime()
{
	QDateTime datetime = QDateTime::currentDateTime();
	QString text = datetime.toString("dd.MM.yyyy hh:mm:ss");
	display(text);
}