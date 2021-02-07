#ifndef CSERVEURTCP_H
#define CSERVEURTCP_H

#include <QObject>
#include <QTcpServer>
#include <QHostAddress>
#include <QThread>
#include <QList>

#include "cgererclient.h"

class CServeurTcp : public QObject
{
    Q_OBJECT

public:
    explicit CServeurTcp(QObject *parent = nullptr);
    ~CServeurTcp();
/*
private:
    QTcpServer serv;
    QTcpSocket *_sock;
    CGererClient *_gcl;
    QThread *_th;
    QList<QTcpSocket *> liste_sock;
    QList<CGererClient *> liste_gcl;
    QList<QThread *> liste_th;
*/
signals:
//    void sig_aff(QString s);

private slots:
//    void on_newConnection();
//    void on_disconnected();

};

#endif // CSERVEURTCP_H
