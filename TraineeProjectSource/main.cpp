#include "CommonHeaders.h"
#include "maincontrollerqclass.h"
#include <QtWidgets/QApplication>
#include "graphicswindow.h"
#include "mainwindowqclass.h"
#include "QProcess"
#include <QByteArray>

#define PRINT_WARNING 1
#define PRINT_INFO 0

#define PRINT_CRITICAL 0
#define PRINT_FATAL 0
QRegExp TAGS_EXCLUDE("\\b(KALMAN|MAIN|ROTATE)\\b");

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    if(msg.contains(TAGS_EXCLUDE)) { return; };

    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";

    switch (type) {
    case QtInfoMsg:     if(PRINT_INFO) qDebug() <<  msg; break;
    case QtWarningMsg:  if(PRINT_WARNING) qDebug() << msg; break;
    case QtCriticalMsg: if(PRINT_CRITICAL) qDebug() << msg; break;
    case QtFatalMsg:    if(PRINT_FATAL) qDebug() << msg; break;

    case QtDebugMsg: std::cerr << msg.toStdString().c_str() << std::endl; break;
    }
}

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
    #define TAG "[ MAIN FUNC   ]" 
    qInstallMessageHandler(myMessageOutput);
	QApplication a(argc, argv);
	{
		int block;
		int block2;
	}
	qDebug() << TAG   << "CURRENT STREAM: " << print_thread_id();

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

