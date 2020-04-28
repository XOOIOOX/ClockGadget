#pragma once

#include <QGraphicsView>

class Viewport : public QGraphicsView
{
	Q_OBJECT

public:
	Viewport(QWidget* parent);
	~Viewport();

	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);

private:
	QPoint delta{ 0, 0 };
	QPoint old{ delta };

signals:
	void mousePositionSignal(QPoint pos);
};
