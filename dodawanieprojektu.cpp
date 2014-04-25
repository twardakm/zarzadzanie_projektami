#include "dodawanieprojektu.h"
#include "ui_dodawanieprojektu.h"

DodawanieProjektu::DodawanieProjektu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DodawanieProjektu)
{
    ui->setupUi(this);
}

DodawanieProjektu::~DodawanieProjektu()
{
    delete ui;
}
