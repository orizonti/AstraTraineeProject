#ifndef TESTQTWIN_H
#define TESTQTWIN_H

#include <QtWidgets/QMainWindow>
#include "ui_testqtwin.h"
#include <QWidget>
#include "QGraphicsScene"
#include "QLabel"
#include "QPushButton"
#include "pidwindow.h"
#include <QGraphicsProxyWidget>
#include "pidwindow.h"
#include "node.h"
#include "edge.h"
#include "graphicwidgetnode.h"
#include "aimingblockwindow.h"
#include "camerawindow.h"

class TestQtWin : public QMainWindow
{
	Q_OBJECT

public:
	TestQtWin(QWidget *parent = 0);
	~TestQtWin();
	QGraphicsScene* Scene;
private:
	Ui::TestQtWinClass ui;
};

#endif // TESTQTWIN_H
