#pragma once

#include <QtWidgets/QWidget>
#include <QSettings>
#include <QTimer>
#include <QMenu>
#include <QColorDialog>
#include "ui_ClockGadget.h"
#include "DigitalClockItem.h"
#include "AnalogClockItem.h"

class ClockGadget : public QWidget
{
	Q_OBJECT

public:
	ClockGadget(QWidget* parent = Q_NULLPTR);
	~ClockGadget();
	bool eventFilter(QObject* obj, QEvent* evt);
	void contextMenuEvent(QContextMenuEvent* evt);

private:
	Ui::ClockGadgetClass ui;
	QSize widgetSize;
	QPoint widgetPos{ pos() };
	QPoint oldPos{ 0, 0 };
	QPoint deltaPos{ 0, 0 };
	QSettings widgetSettings;
	Viewport* view;
	QGraphicsScene* scene;
	DigitalClockItem digitalClock;
	AnalogClockItem analogClock;
	QTimer* animationTimer;
	QMenu* menu;
	QAction* digitalClockAction;
	QAction* analogClockAction;
	QAction* colorAction;
	QAction* exitAction;
	QColorDialog colorDialog;
	QColor baseColor{ 0xfffd5bff };

	void setSceneRect();

public slots:
	void moveWidgetSlot(QPoint point);
	void digitalClockSettingsSlot();
	void analogClockSettingsSlot();
	void colorSettingsSlot();

signals:
	void setColorSignal(QColor color);
};
