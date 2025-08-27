#include "reqmon.h"
#include "ui_reqmon.h"

ReqMon::ReqMon(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ReqMon)
{
    ui->setupUi(this);
}

ReqMon::~ReqMon()
{
    delete ui;
}
