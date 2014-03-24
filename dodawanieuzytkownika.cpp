#include "dodawanieuzytkownika.h"
#include "ui_dodawanieuzytkownika.h"

DodawanieUzytkownika::DodawanieUzytkownika(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DodawanieUzytkownika)
{
    ui->setupUi(this);
    ui->informacje->setText("Nie dodano bazy danych");
}

DodawanieUzytkownika::DodawanieUzytkownika(QWidget *parent, QSqlDatabase *baza) :
    QDialog(parent), ui(new Ui::DodawanieUzytkownika)
{
    ui->setupUi(this);
    connect(ui->przyciski, SIGNAL(accepted()), this, SLOT(przyciski_zaakceptowano()));
}

DodawanieUzytkownika::~DodawanieUzytkownika()
{
    delete ui;
}

void DodawanieUzytkownika::przyciski_zaakceptowano()
{

}
