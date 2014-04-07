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
        QMessageBox blad(this);
        blad.setText("Nie udało się usunąć użytkownika");
        blad.exec();
        return;
    }
    this->uzytkownik.wyloguj();
    this->odswiez();
}
