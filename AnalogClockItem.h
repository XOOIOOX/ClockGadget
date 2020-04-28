#pragma once
#include "ClockItem.h"

class AnalogClockItem : public ClockItem
{
public:
	AnalogClockItem(QObject* parent = nullptr);
	~AnalogClockItem();

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
	void advance(int phase) override;

private:
	double hour;
	double min;
	double sec;
	double digitsPenWidth{ 0 };
	double secondsPenWidth{ 2 };
	double minutesPenWidth{ 5 };
	double hoursPenWidth{ 7 };

	double digitsSize{ 63 };
	double secondsSize{ 63 };
	double minutesSize{ 53 };
	double hoursSize{ 35 };

	QPointF angleToXY(const double& angle, const double& len);
};
