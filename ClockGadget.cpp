#include "ClockGadget.h"
#include <QDesktopWidget>
#include <QFontDatabase>
#include "qevent.h"

constexpr auto AinmationFps = 60;

ClockGadget::ClockGadget(QWidget* parent) : QWidget(parent)
{
	this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	this->setAttribute(Qt::WA_TranslucentBackground);

	QFontDatabase::addApplicationFont(":/Resources/04B_30__.TTF");

	ui.setupUi(this);
	view = ui.graphicsView;
	scene = new QGraphicsScene(view->rect(), this);
	view->setScene(scene);
	setSceneRect();

	if (!widgetSettings.contains("WindowPos/x") || !widgetSettings.contains("WindowPos/y"))
	{
		move({ QApplication::desktop()->size().width() - width(), 0 });
		widgetSettings.setValue("WindowPos/x", pos().x());
		widgetSettings.setValue("WindowPos/y", pos().y());
		widgetSettings.sync();
	}
	else
	{
		move({ widgetSettings.value("WindowPos/x").toInt(), widgetSettings.value("WindowPos/y").toInt() });
	}

	installEventFilter(this);

	animationTimer = new QTimer(this);
	animationTimer->start(1000 / AinmationFps);

	connect(view, SIGNAL(mousePositionSignal(QPoint)), this, SLOT(moveWidgetSlot(QPoint)));
	connect(animationTimer, SIGNAL(timeout()), scene, SLOT(advance()));

	digitalClock.setSize(this->size());
	analogClock.setSize(this->size());

	if (!widgetSettings.contains("Mode"))
	{
		widgetSettings.setValue("Mode", "Digital");
		widgetSettings.sync();
		scene->addItem(&digitalClock);
	}
	else
	{
		if (widgetSettings.value("Mode").toString() == "Digital")
		{
			scene->addItem(&digitalClock);
		}
		else
		{
			scene->addItem(&analogClock);
		}
	}

	menu = new QMenu();

	digitalClockAction = menu->addAction("Digital");
	analogClockAction = menu->addAction("Analog");
	colorAction = menu->addAction("Color");
	exitAction = menu->addAction("Exit");
	connect(digitalClockAction, SIGNAL(triggered()), this, SLOT(digitalClockSettingsSlot()));
	connect(analogClockAction, SIGNAL(triggered()), this, SLOT(analogClockSettingsSlot()));
	connect(colorAction, SIGNAL(triggered()), this, SLOT(colorSettingsSlot()));
	connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
	connect(this, SIGNAL(setColorSignal(QColor)), &digitalClock, SLOT(setColorSlot(QColor)));
	connect(this, SIGNAL(setColorSignal(QColor)), &analogClock, SLOT(setColorSlot(QColor)));

	if (!widgetSettings.contains("Color"))
	{
		widgetSettings.setValue("Color", baseColor.rgba());
		widgetSettings.sync();
	}
	else
	{
		baseColor.setRgba(widgetSettings.value("Color").toInt());
	}

	emit setColorSignal(baseColor);
}

ClockGadget::~ClockGadget()
{
	widgetSettings.setValue("WindowPos/x", pos().x());
	widgetSettings.setValue("WindowPos/y", pos().y());
	widgetSettings.sync();
}

bool ClockGadget::eventFilter(QObject* obj, QEvent* evt)
{
	if (obj == this && (evt->type() == QEvent::Close))
	{
		qApp->exit();
		return true;
	}

	return false;
}

void ClockGadget::contextMenuEvent(QContextMenuEvent* evt)
{
	if (menu)
	{
		menu->exec(evt->globalPos());
	}
}

void ClockGadget::moveWidgetSlot(QPoint point)
{
	move(pos() + point);
}

void ClockGadget::digitalClockSettingsSlot()
{
	widgetSettings.setValue("Mode", "Digital");
	widgetSettings.sync();
	auto itemsList = scene->items();

	for (auto it : itemsList)
	{
		if (it == &analogClock)
		{
			scene->removeItem(it);
			scene->addItem(&digitalClock);
			return;
		}
	}
}

void ClockGadget::analogClockSettingsSlot()
{
	widgetSettings.setValue("Mode", "Analog");
	widgetSettings.sync();
	auto itemsList = scene->items();

	for (auto it : itemsList)
	{
		if (it == &digitalClock)
		{
			scene->removeItem(it);
			scene->addItem(&analogClock);
			return;
		}
	}
}

void ClockGadget::colorSettingsSlot()
{
	baseColor = colorDialog.getColor(baseColor, nullptr, QString(), QColorDialog::ShowAlphaChannel);
	widgetSettings.setValue("Color", baseColor.rgba());
	widgetSettings.sync();
	emit setColorSignal(baseColor);
}

void ClockGadget::setSceneRect()
{
	auto rect = view->rect();
	rect.setWidth(rect.width() - 2);
	rect.setHeight(rect.height() - 2);
	scene->setSceneRect(rect);
}