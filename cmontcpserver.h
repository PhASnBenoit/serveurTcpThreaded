#ifndef CMATCPSOCKET_H
#define CMATCPSOCKET_H

#include <QObject>
#include <QTcpServer>

class CMonTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit CMonTcpServer(QObject *parent = Q_NULLPTR);

protected:
    void incomingConnection(qintptr sd); // réimplémentation

signals:
    void sig_sdClient(qintptr sd);
};

#endif // CMATCPSOCKET_H
