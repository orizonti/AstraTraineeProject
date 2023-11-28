#include "CommonHeaders.h"
#include "tcpclientengine.h"
#define TAG "[ TCP CLIENT ]" 

TCPClientEngine::TCPClientEngine(QObject *parent): QObject(parent)
{

    QObject::connect(&this->DataSocket,&QTcpSocket::readyRead,this,&TCPClientEngine::SlotReadDataFromHost);
}

TCPClientEngine::~TCPClientEngine()
{
  DataSocket.disconnectFromHost();
}
void TCPClientEngine::SlotReadDataFromHost()
{
    QString inputString(DataSocket.readAll());
    emit OutputSignal("From server: " + inputString);
}
void TCPClientEngine::SlotSendData(QVector<double> Data)
{
	if((Counter++) == 10)
	{
		QString DataInString = "@";
		for(double Value: Data)
		{
		   DataInString = DataInString + "/" + QString::number(Value,'g',4);
		}

		if (DataSocket.isOpen() && DataSocket.isValid())
		{
			DataSocket.write(DataInString.toUtf8());
			//qDebug() << TAG << DataInString << " sent to host";
		}
		else
			qDebug() << TAG << "Socket no valid";

		   //emit OutputSignal("Socket not valid");
		   //emit OutputSignal("From server: " + DataInString + "sent");
		Counter = 0;
	}

}

void TCPClientEngine::ConnectToHost(QString Address, int Port)
{

        this->DataSocket.connectToHost(Address,Port);

		if (DataSocket.isOpen())
		qDebug() << TAG << "Socket connected to " << Address << " Port - " << Port;
        else
		qDebug() << TAG << "Socket not connected";

        //emit OutputSignal("Socket not connected");
        //emit OutputSignal("Socket connected to - " + DataSocket.peerAddress().toString());

}
void TCPClientEngine::DisconnectFromHost()
{

        this->DataSocket.disconnectFromHost();

        if(DataSocket.isOpen())
           emit OutputSignal("Socket disconnected");
}



