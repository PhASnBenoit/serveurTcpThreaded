#include "cgererclient.h"

CGererClient::CGererClient(qintptr sd, QObject *parent) : QObject(parent)
{
    _sd = sd;
}

CGererClient::~CGererClient()
{
    qDebug() << "GCererClient::~CGererClient : destruction !";
    emit sig_aff("GCererClient::~CGererClient : destruction !");
    _sock->close();
    delete _sock;
}

void CGererClient::on_goGestionClient()
{
        _sock = new QTcpSocket();  // la socket est maintenant gérée par le thread
        // init des params du client
        if (_sock->setSocketDescriptor(_sd)) {
            _hostAddress = _sock->peerAddress();
            _localAddress = _sock->localAddress();
            _peerPort = _sock->peerPort();
            _localPort = _sock->localPort();
            emit sig_aff("CGererClient::on_goGestionClient : Connexion de IP="+_hostAddress.toString()+
                         " Port="+QString::number(_peerPort));
            // signaux de fonctionnement de la socket
            connect(_sock, &QTcpSocket::readyRead, this, &CGererClient::on_readyRead);
            connect(_sock, &QTcpSocket::disconnected, this, &CGererClient::on_disconnected);
            connect(_sock, static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),
                  [=](QAbstractSocket::SocketError socketError) {
                    switch(socketError) {
                    case QAbstractSocket::RemoteHostClosedError:
                        emit sig_aff("Erreur socket : Remote Host Closed !");
                        break;
                    default:
                        emit sig_aff("Erreur socket : Erreur non précisée : "+QString::number(socketError));
                    } // sw
                  });
        } // if setsocket....
}

void CGererClient::on_readyRead()
{
    QTcpSocket *client = static_cast<QTcpSocket *>(sender());
    qint64 nb = client->bytesAvailable();
    QString all=client->readAll();
    //QString all = _sock->readAll();
    emit sig_aff("IP Local="+_localAddress.toString()+" Port="+QString::number(_localPort));
    emit sig_aff(QString::number(nb)+" car reçus de IP="+_hostAddress.toString()+" Port="+QString::number(_peerPort)+" : "+all);
    client->write("Bien reçu !\x0d\x0a", 13);
}

void CGererClient::on_disconnected()
{
    emit sig_aff("CGererClient::on_disconnected : Déconnexion de IP="+_hostAddress.toString()+" Port="+QString::number(_peerPort));
    emit sig_disconnected();
}
