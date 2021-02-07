#include "cihm.h"
#include "ui_cihm.h"

CIhm::CIhm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CIhm)
{
    ui->setupUi(this);
    _app = new CApp();
    connect(_app, &CApp::sig_aff, this, &CIhm::on_aff);
}

CIhm::~CIhm()
{
    delete _app;
    delete ui;
}

void CIhm::on_aff(QString s)
{
    ui->teTexte->append(s);
}
