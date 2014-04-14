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
    //wczytanie adresu projektu
    baza = QSqlDatabase::addDatabase("QSQLITE");
    baza.setDatabaseName(uzytkownik.podaj_adres_bazy());

    if(!baza.open())
    {
        //tu dopisać co się dzieje jak nie idzie otworzyć bazy danych
    }

    QSqlQuery *zapytanie = new QSqlQuery(uzytkownik.podaj_adres_bazy());
    zapytanie->exec("SELECT adres_bazy FROM projekty");
    zapytanie->next();
    qDebug() << "Adres bazy: " << zapytanie->value(0).toString();


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
