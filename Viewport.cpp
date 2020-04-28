#include <QMouseEvent>
#include "Viewport.h"

Viewport::Viewport(QWidget* parent) : QGraphicsView(parent)
{
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
	setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
}

Viewport::~Viewport()
{}

void Viewport::mousePressEvent(QMouseEvent* event)
{
	if (event->button() & Qt::LeftButton)
	{
		old = event->pos();
		delta = { 0, 0 };
		emit mousePositionSignal(delta);
	}
	else
	{
		delta = { 0, 0 };
	}
}

void Viewport::mouseReleaseEvent(QMouseEvent* event)
{
	old = event->pos();
	delta = { 0, 0 };
	emit mousePositionSignal(delta);
}

void Viewport::mouseMoveEvent(QMouseEvent* event)
{
	if ((event->buttons() & Qt::LeftButton))
	{
		delta = event->pos() - old;
		emit mousePositionSignal(delta);
	}
	else
	{
		delta = { 0, 0 };
	}
}