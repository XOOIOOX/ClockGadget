#pragma once

#include <QObject>
#include <QGraphicsEffect>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QString>
#include <QTime>
#include <QWidget>

class ClockItem : public QObject, public QGraphicsRectItem
{
	Q_OBJECT

public:
	ClockItem(QObject* parent = nullptr);
	virtual ~ClockItem();

	void setSize(QSize size);
	virtual void advance(int phase) = 0;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) = 0;

protected:
	QColor baseColor{ 0xfffd5bff };
	QColor effectColor = { baseColor };
	QGraphicsDropShadowEffect* effect;
	int blurRadius = 40;
	double opacity = 0.9;

public slots:
	void setColorSlot(QColor color);
};
