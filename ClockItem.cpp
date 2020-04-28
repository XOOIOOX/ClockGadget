#include "ClockItem.h"

ClockItem::ClockItem(QObject* parent) : QGraphicsRectItem(nullptr)
{
	effect = new QGraphicsDropShadowEffect();
	effect->setBlurRadius(blurRadius);
	effectColor.setAlphaF(opacity);
	effect->setColor(effectColor);
	effect->setOffset(0);
	this->setGraphicsEffect(effect);
}

ClockItem::~ClockItem()
{}

void ClockItem::setSize(QSize size)
{
	setRect(0, 0, size.width(), size.height());
}

void ClockItem::setColorSlot(QColor color)
{
	baseColor = color;
	effectColor = color;
	effect->setColor(effectColor);
}