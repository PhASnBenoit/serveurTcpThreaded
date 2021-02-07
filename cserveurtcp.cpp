#include "cserveurtcp.h"

/*
CServeurTcp::CServeurTcp(QObject *parent)
{
 //   connect(&serv, &QTcpServer::newConnection, this, &CServeurTcp::on_newConnection);
 //   serv.listen(QHostAddress::AnyIPv4, 5555);
}

void CServeurTcp::on_newConnection()
{
    // création du thread et
    // du gestionnaire de communication
    // avec le client.
    _sock = serv.nextPendingConnection(); // adresse de l'objet
    //emit sig_aff("Nouveau client connecté.");

    _gcl = new CGererClient(nullptr, _sock);
    _th = new QThread();
    _gcl->moveToThread(_th);
    _sock->moveToThread(_th);
    connect(_th, &QThread::finished, _gcl, &QObject::deleteLater);
    //connect(_sock, &QTcpSocket::disconnected, this, &CServeurTcp::on_disconnected);
    _th->start();
}

void CServeurTcp::on_disconnected()
{

}
*/

CServeurTcp::CServeurTcp(QObject *parent)
{

}
