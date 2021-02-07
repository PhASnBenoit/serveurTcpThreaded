#ifndef CIHM_H
#define CIHM_H

#include <QMainWindow>
#include <QDebug>
#include "capp.h"

namespace Ui {
class CIhm;
}

class CIhm : public QMainWindow
{
    Q_OBJECT

public:
    explicit CIhm(QWidget *parent = nullptr);
    ~CIhm();

private:
    Ui::CIhm *ui;
    CApp  *_app;

private slots:
    void on_aff(QString s);
};

#endif // CIHM_H
