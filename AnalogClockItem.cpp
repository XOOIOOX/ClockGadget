#include "AnalogClockItem.h"
#include <corecrt_math_defines.h>

AnalogClockItem::AnalogClockItem(QObject* parent) : ClockItem(parent)
{}

AnalogClockItem::~AnalogClockItem()
{}

void AnalogClockItem::advance(int phase)
{
	if (phase)
	{
		auto time = QDateTime::currentDateTime().time();

		sec = time.second() * 6.0 + time.msec() / 166.6 - 90.0;
		min = time.minute() * 6.0 + time.second() / 10.0 - 90.0;
		hour = time.hour() * 30.0 + time.minute() / 2.0 - 90.0;

		update();
	}
}
void AnalogClockItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget /*= nullptr*/)
{
	QBrush brush{ baseColor, Qt::SolidPattern };
	painter->setBrush(brush);
	painter->setOpacity(1.0);

	painter->setPen({ brush, digitsPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin });

	for (int i = 0, angle = 90; i < 12; ++i)
	{
		angle += 30;
		auto point = angleToXY(angle, digitsSize);
		painter->drawEllipse(rect().center() + point, 1.5, 1.5);
	}

	painter->setPen({ brush, secondsPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin });
	double angle = static_cast<double>(sec);
	auto secondsPoint = angleToXY(angle, secondsSize);
	painter->drawLine(rect().center(), rect().center() + secondsPoint);

	painter->setPen({ brush, minutesPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin });
	angle = static_cast<double>(min);
	auto minutesPoint = angleToXY(angle, minutesSize);
	painter->drawLine(rect().center(), rect().center() + minutesPoint);

	painter->setPen({ brush, hoursPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin });
	angle = static_cast<double>(hour);
	auto hoursPoint = angleToXY(angle, hoursSize);
	painter->drawLine(rect().center(), rect().center() + hoursPoint);
}

QPointF AnalogClockItem::angleToXY(const double& angle, const double& len)
{
	return { len * cos(angle * M_PI / 180.0), len * sin(angle * M_PI / 180.0) };
}