#include "capp.h"

CApp::CApp(QObject *parent) : QObject(parent)
{
    _serv = new CGererServeur(PORT);
    connect(_serv, &CGererServeur::sig_aff, this, &CApp::on_aff);
}

CApp::~CApp() {
    delete _serv;
}

void CApp::on_aff(QString s)
{
    emit sig_aff(s);
}
