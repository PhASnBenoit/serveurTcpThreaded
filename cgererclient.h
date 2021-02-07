#ifndef CGERERCLIENT_H
#define CGERERCLIENT_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QHostAddress>

class CGererClient : public QObject
{
    Q_OBJECT

public:
    explicit CGererClient(qintptr sd = 0, QObject *parent = nullptr);
    ~CGererClient();

private:
    QTcpSocket *_sock;
    QHostAddress _hostAddress;
    QHostAddress _localAddress;
    quint16 _peerPort, _localPort;
    qintptr _sd;

signals:
    void sig_aff(QString s);
    void sig_disconnected();

public slots:
    void on_goGestionClient();

private slots:
    void on_readyRead();
    void on_disconnected();
};

#endif // CGERERCLIENT_H
