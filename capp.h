#ifndef CAPP_H
#define CAPP_H

#include <QObject>
#include "cgererserveur.h"

#define PORT 5555

class CApp : public QObject
{
    Q_OBJECT
public:
    explicit CApp(QObject *parent = nullptr);
    ~CApp();

private:
    CGererServeur *_serv;

signals:
    void sig_aff(QString s);

public slots:
    void on_aff(QString s);
};

#endif // CAPP_H
