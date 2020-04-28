#pragma once

#include "ClockItem.h"

class DigitalClockItem : public ClockItem
{
public:
	DigitalClockItem(QObject* parent = nullptr);
	~DigitalClockItem();

	void advance(int phase) override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

private:
	int fontSize = 32;
	QString clockText;
};
