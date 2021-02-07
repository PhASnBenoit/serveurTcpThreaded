#include "cgererserveur.h"

CGererServeur::CGererServeur(quint16 port, QObject *parent) : QObject(parent)
{
    _serv = new CMonTcpServer();
    connect(_serv, &CMonTcpServer::sig_sdClient, this, &CGererServeur::on_newConnection);
    _serv->listen(QHostAddress::AnyIPv4, port);
}

CGererServeur::~CGererServeur()
{
    // effacement des threads
    for (int i=0 ; i<liste_th.size() ; i++) {
        liste_th.at(i)->quit();  // demande au thread de se terminer
        liste_th.at(i)->wait();  // attends la fin de la boucle événements
    } // for
    liste_th.clear();
    liste_gcl.clear();
    delete _serv;
}

void CGererServeur::on_newConnection(qintptr sd)
{
    // Nouvelle connexion d'un client
    // La méthode héritée QTcpServer::incomingConnection() a été redéfinie.
    // création du thread et du gestionnaire de communication avec le client.
    QThread *th = new QThread();
    th->setObjectName("servGcl_"+QString::number(sd));
    CGererClient *gcl = new CGererClient(sd, nullptr);  // il créera la socket de comm grace à sd
    // déplacement vers le thread
    gcl->moveToThread(th);

    connect(gcl, &CGererClient::sig_aff, this, &CGererServeur::on_aff);
    connect(gcl, &CGererClient::sig_disconnected, this, &CGererServeur::on_disconnected); // provoque la destruction du clientet du thread
    connect(this, &CGererServeur::sig_goGestionClient, gcl, &CGererClient::on_goGestionClient); // provoque création socket client
    connect(th, &QThread::finished, gcl, &QObject::deleteLater); // The object will be deleted when control returns to the event loop

    th->start(); // départ boucle des événements du thread.
    emit sig_goGestionClient(); // Départ de la gestion du client

    // Mémorisation des objets créés
    liste_th.append(th);
    liste_gcl.append(gcl);
}

void CGererServeur::on_disconnected()
{
    CGererClient *gcl = static_cast<CGererClient *>(sender());
    // le signal disconnected est parfois envoyé 2 fois !!! la 2ème fois, gcl = 0 !
    // Alors on filtre.
    if (gcl != nullptr) {
        QThread *th = gcl->thread(); // on récupère le thread qui a envoyé le signal
        int pos = liste_th.indexOf(th); // on cherche la position
        if (pos > -1) {  // s'il existe
            liste_th.at(pos)->quit();  // demande au thread de se terminer
            liste_th.at(pos)->wait();  // attends la fin de la boucle événements
            // effacement de la liste des objets dépendant du client
            // _gcl s'effacera automatiquement avec le thread. C'est vérifié,
            //    mettre un point d'arrêt dans ~CGestionClient pour le prouver !
            liste_th.removeAt(pos);
            liste_gcl.removeAt(pos);
        } // if pos
        emit sig_aff("CGererServeur::on_disconnected : Nb client restant : "+QString::number(liste_gcl.size()));
    } // if 0
} //

void CGererServeur::on_aff(QString s)
{
    emit sig_aff(s);
}
