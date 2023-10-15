#include "stdafx.h"
#include "maincontrollerqclass.h"
#include <QtWidgets/QApplication>
#include "graphicswindow.h"
#include "mainwindowqclass.h"
#include "QProcess"
//test string
QString print_thread_id()
{
  auto id = std::this_thread::get_id();
  stringstream ss;
  ss << id;
  return QString(ss.str().c_str());
}

int main(int argc, char *argv[])
{
    //QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication a(argc, argv);
	{
		int block;
		int block2;
	}
	qDebug() << "current stream - " << print_thread_id();

	GraphicsWindow* GraphicsDisplay = new GraphicsWindow;
	MainWindowQClass* WindowDisplay = new MainWindowQClass(GraphicsDisplay);
	GraphicsDisplay->setAttribute(Qt::WA_DeleteOnClose);

	MainControllerQClass* MainController = new MainControllerQClass(WindowDisplay,GraphicsDisplay);

	QObject::connect(WindowDisplay, &MainWindowQClass::SignalMainWindowClosed, MainController, &MainControllerQClass::SlotFinishWork);



	WindowDisplay->show();
	WindowDisplay->move(10,10);


	//GraphicsDisplay->show();
	//GraphicsDisplay->move(WindowDisplay->x()-GraphicsDisplay->size().width(), WindowDisplay->y());



	return a.exec();
}

