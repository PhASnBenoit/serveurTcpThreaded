#include "cmontcpserver.h"

CMonTcpServer::CMonTcpServer(QObject *parent) : QTcpServer(parent)
{

}

void CMonTcpServer::incomingConnection(qintptr sd)
{
    emit sig_sdClient(sd);
}
