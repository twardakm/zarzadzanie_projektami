#include "dodawanieterminu.h"
#include "ui_dodawanieterminu.h"

DodawanieTerminu::DodawanieTerminu(QString b, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DodawanieTerminu),
    adres_bazy(b)
{
    ui->setupUi(this);

    connect(ui->zatwierdz_przycisk, SIGNAL(pressed()),
            this, SLOT(zatwierdz_wcisniety()));
    connect(ui->anuluj_przycisk, SIGNAL(clicked()),
            this, SLOT(anuluj_wcisniety()));
    ui->data_do_edit->setDisplayFormat("dd.MM.yyyy");
    ui->data_od_edit->setDisplayFormat("dd.MM.yyyy");

    ui->data_do_edit->setDate(QDate::currentDate());
    ui->data_od_edit->setDate(QDate::currentDate());

    QPalette kolor;
    kolor.setColor(QPalette::WindowText, Qt::red);
    ui->blad_label->setPalette(kolor);
    ui->blad_label->setText("");
}

DodawanieTerminu::~DodawanieTerminu()
{
    delete ui;
}

void DodawanieTerminu::zatwierdz_wcisniety()
{
    if (ui->opis_edit->toPlainText() == "")
    {
        ui->blad_label->setText("Pusty opis");
        return;
    }
    if (ui->data_do_edit->date() < ui->data_od_edit->date())
    {
        ui->blad_label->setText("Błędna data");
        return;
    }

    QSqlDatabase baza = QSqlDatabase::addDatabase("QSQLITE");
    baza.setDatabaseName(adres_bazy);
    if (!baza.open())
    {
        ui->blad_label->setText("Nie udało się otworzyć bazy danych");
        return;
    }

    QSqlQuery *zapytanie = new QSqlQuery(adres_bazy);
    if(!zapytanie->exec("INSERT INTO 'terminarz' VALUES ('" +
                    ui->data_od_edit->date().toString("yyyy-MM-dd") + "', '" +
                    ui->data_do_edit->date().toString("yyyy-MM-dd") + "', '" +
                    ui->opis_edit->toPlainText() + "')"))
    {
        ui->blad_label->setText("Nie udalo się dodać do bazy danych");
        return;
    }

    delete zapytanie;
    baza.close();
    this->accept();
}

void DodawanieTerminu::anuluj_wcisniety()
{
    this->reject();
}
