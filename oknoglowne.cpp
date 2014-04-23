#include "oknoglowne.h"
#include "ui_oknoglowne.h"

OknoGlowne::OknoGlowne(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::OknoGlowne)
{
    ui->setupUi(this);

    connect(ui->informacje_Qt, SIGNAL(triggered()),
            this, SLOT(informacje_Qt_wcisniety()));
    connect(ui->zmien_uzytkownika, SIGNAL(triggered()),
            this, SLOT(zmien_uzytkownika_wcisniety()));
    connect(ui->wyloguj, SIGNAL(triggered()),
            this, SLOT(wyloguj_wcisniety()));
    connect(ui->usun, SIGNAL(triggered()), this,
            SLOT(usun_wcisniety()));
    this->wczytaj_dane();
}

OknoGlowne::~OknoGlowne()
{
    if (ui != NULL) delete this->ui;
}

void OknoGlowne::wczytaj_dane()
{
    /*Wczytanie danych z bazy
     * -------------------- */
    UstawieniaWstepne okno(this, &uzytkownik);
    okno.exec();
    /* -------------------- */
    odswiez();
}

void OknoGlowne::odswiez()
{
    ui->nazwa_uzytkownika->setText(uzytkownik.podaj_nazwe());
    ui->menuUzytkownik->setTitle(uzytkownik.podaj_nazwe());

    this->pokaz_projekty();
}

void OknoGlowne::pokaz_projekty()
{
    QSqlDatabase *baza_projekt;
    QSqlQuery *projekt_zapytanie;
    //wczytanie adresu projektu
    baza = QSqlDatabase::addDatabase("QSQLITE");
    baza.setDatabaseName(uzytkownik.podaj_adres_bazy());

    if(!baza.open())
    {
        qDebug() << "Nie otworzono";
    }

    QSqlQuery *zapytanie = new QSqlQuery(uzytkownik.podaj_adres_bazy());
    zapytanie->exec("SELECT sciezka, nazwa FROM projekty");

    while(zapytanie->next())
    {
        baza_projekt = new QSqlDatabase;
        *baza_projekt = QSqlDatabase::addDatabase("QSQLITE");
        baza_projekt->setDatabaseName(zapytanie->value(0).toString());
        if(!baza_projekt->open())
        {
            ui->listaProjektow->addItem("Błąd otwarcia");
        }

        projekt_zapytanie = new QSqlQuery(zapytanie->value(0).toString());
        projekt_zapytanie->exec("SELECT admin FROM administratorzy WHERE admin='" + uzytkownik.podaj_nazwe() +"'");
        if (projekt_zapytanie->next())
            ui->listaProjektow->addItem(zapytanie->value(1).toString());

        delete projekt_zapytanie;
        baza_projekt->close();
        delete baza_projekt;
        //zczytanie projektów
    }

    baza.close();
}

void OknoGlowne::informacje_Qt_wcisniety()
{
    QMessageBox::aboutQt(this, "Informacje o Qt");
}

void OknoGlowne::zmien_uzytkownika_wcisniety()
{
    this->wczytaj_dane();
}

void OknoGlowne::wyloguj_wcisniety()
{
    this->uzytkownik.wyloguj();
    this->odswiez();
}

void OknoGlowne::usun_wcisniety()
{
    if(!this->uzytkownik.usun_uzytkownika())
    {
        QMessageBox::warning(this,"Usunięcie użytkownika",
                             "Nie udało się usunąć użytkownika");
        return;
    }
    else
    {
        QMessageBox::information(this, "Usunięcie użytkownika",
                                 "Poprawnie usunięto użytkownika");
    }
    this->uzytkownik.wyloguj();
    this->odswiez();
}
