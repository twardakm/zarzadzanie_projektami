#include "oknoglowne.h"
#include "ui_oknoglowne.h"

OknoGlowne::OknoGlowne(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OknoGlowne)
{
    ui->setupUi(this);
}

OknoGlowne::~OknoGlowne()
{
    delete ui;
}
