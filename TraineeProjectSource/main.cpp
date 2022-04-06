#include "stdafx.h"
#include "maincontrollerqclass.h"
#include <QtWidgets/QApplication>
#include "graphicswindow.h"
#include "mainwindowqclass.h"
#include "QProcess"

#pragma comment(lib,"DriverMoiKlp.lib")

int main(int argc, char *argv[])
{
    //QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication a(argc, argv);
	{
		int block;
		int block2;
	}

	GraphicsWindow* GraphicsDisplay = new GraphicsWindow;
	MainWindowQClass* WindowDisplay = new MainWindowQClass(GraphicsDisplay);	
	WindowDisplay->setAttribute(Qt::WA_DeleteOnClose);
	GraphicsDisplay->setAttribute(Qt::WA_DeleteOnClose);


	MainControllerQClass* MainController = new MainControllerQClass(WindowDisplay,GraphicsDisplay);

	QObject::connect(WindowDisplay, &QMainWindow::destroyed, MainController, &QObject::deleteLater);
	QObject::connect(MainController, &QObject::destroyed, GraphicsDisplay, &QWidget::close);
	 


	WindowDisplay->show();
	WindowDisplay->move(10,10);


	//GraphicsDisplay->show();
	//GraphicsDisplay->move(WindowDisplay->x()-GraphicsDisplay->size().width(), WindowDisplay->y());



	return a.exec();
}

