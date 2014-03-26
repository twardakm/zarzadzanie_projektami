#include "dodawanieuzytkownika.h"
#include "ui_dodawanieuzytkownika.h"

DodawanieUzytkownika::DodawanieUzytkownika(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DodawanieUzytkownika)
{
    ui->setupUi(this);
    this->reject();
}

DodawanieUzytkownika::DodawanieUzytkownika(QWidget *parent, QSqlDatabase *ba) :
    QDialog(parent), ui(new Ui::DodawanieUzytkownika), baza(*ba)
{
    ui->setupUi(this);
    //kolor informacji
    QPalette kolor;
    kolor.setColor(QPalette::WindowText, Qt::red);
    ui->informacje->setPalette(kolor);
    ui->informacje->setText("");
    //ustawienie trybu wprowadzania hasła na hasło
    ui->haslo_edycja->setEchoMode(QLineEdit::Password);
    ui->haslo_potwierdz_edycja->setEchoMode(QLineEdit::Password);

    connect(ui->zatwierdz, SIGNAL(clicked()), this, SLOT(zatwierdz_wcisniety()));
    connect(ui->anuluj, SIGNAL(clicked()), this, SLOT(anuluj_wcisniety()));
}

DodawanieUzytkownika::~DodawanieUzytkownika()
{
    delete ui;
}

bool DodawanieUzytkownika::sprawdz_haslo()
{
    if (ui->haslo_edycja->text() != ui->haslo_potwierdz_edycja->text())
        return false;
    if (ui->haslo_edycja->text() == "")
        return false;
    return true;
}

bool DodawanieUzytkownika::sprawdz_mail()
{
    if(ui->mail_edycja->text() == "")
        return false;
    else
        return true;
}

bool DodawanieUzytkownika::sprawdz_uzytkownika()
{
    if(ui->nazwa_uzytkownika_edycja->text() == "")
        return false;
    else
        return true;
}

void DodawanieUzytkownika::zatwierdz_wcisniety()
{
    if (!sprawdz_mail())
    {
        ui->informacje->setText("Podaj adres e-mail");
        return;
    }
    if (!sprawdz_uzytkownika())
    {
        ui->informacje->setText("Podaj nazwę użytkownika");
        return;
    }
    if (!sprawdz_haslo())
    {
        ui->informacje->setText("Podaj hasło");
        return;
    }

    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(ui->haslo_edycja->text().toLatin1());
    //zapisywanie danych do bazy
    QSqlQuery zapytanie(baza);
    if(!zapytanie.exec("INSERT INTO "
                       + (QString)TABELA_UZYTKOWNICY +
                       " VALUES ('"
                       + ui->nazwa_uzytkownika_edycja->text() + "', '"
                       + ui->mail_edycja->text() + "', '"
                       + (QString)hash.result().toHex() + "')"))
    {
        ui->informacje->setText("Nie udało się dodać użytkownika do bazy danych");
        return;
    }

    this->accept();
}

void DodawanieUzytkownika::anuluj_wcisniety()
{
    this->reject();
}
