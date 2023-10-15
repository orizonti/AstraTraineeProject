#ifndef TCPCLIENTENGINE_H
#define TCPCLIENTENGINE_H


class TCPClientEngine : public QObject
{
Q_OBJECT
public:
    TCPClientEngine(QObject *parent = nullptr);
    ~TCPClientEngine();

    QTcpSocket DataSocket;
	int Counter = 0;
public slots:
    void SlotReadDataFromHost();
    void SlotSendData(QVector<double> Data);

    void ConnectToHost(QString Address, int Port);
    void DisconnectFromHost();
signals:
    void OutputSignal(QString OutputString);
};

#endif // TCPCLIENTENGINE_H
