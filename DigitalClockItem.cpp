#include "DigitalClockItem.h"

DigitalClockItem::DigitalClockItem(QObject* parent) : ClockItem(parent)
{}

DigitalClockItem::~DigitalClockItem()
{}

void DigitalClockItem::advance(int phase)
{
	if (phase)
	{
		clockText = QTime::currentTime().toString("hh:mm:ss");
		update();
	}
}
void DigitalClockItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget /*= nullptr*/)
{
	painter->setPen(baseColor);
	painter->setOpacity(1.0);
	auto font = painter->font();
	font.setFamily("04b");
	font.setPixelSize(fontSize);
	painter->setFont(font);
	auto textRect = rect();
	textRect.setSize(rect().size() / 1.5);
	textRect.moveCenter(rect().center());
	painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, clockText);
}