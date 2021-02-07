#ifndef CTCPSERVEUR_H
#define CTCPSERVEUR_H

#include <QObject>
//#include <QTcpServer>
#include <QList>
#include <QThread>
#include "cgererclient.h"
#include "cmontcpserver.h"

class CGererServeur : public QObject
{
    Q_OBJECT
public:
    explicit CGererServeur(quint16 port=5555, QObject *parent = nullptr);
    ~CGererServeur();

private:
    CMonTcpServer *_serv;
    QList<CGererClient *> liste_gcl;
    QList<QThread *> liste_th;

signals:
    void sig_aff(QString s);
    void sig_goGestionClient();

public slots:
    void on_newConnection(qintptr sd);
    void on_disconnected();
    void on_aff(QString s);
};

#endif // CTCPSERVEUR_H
