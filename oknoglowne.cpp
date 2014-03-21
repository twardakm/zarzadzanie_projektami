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

    this->uzytkownik = new QString;
    this->wczytaj_dane();
}

OknoGlowne::~OknoGlowne()
{
    if (ui != NULL) delete this->ui;
    if (uzytkownik != NULL) delete this->uzytkownik;
    if (okno != NULL) delete this->okno;
}

void OknoGlowne::wczytaj_dane()
{
    /*Wczytanie danych z bazy
     * -------------------- */
    okno = new UstawieniaWstepne(this);
    okno->exec();
    /* -------------------- */
}

void OknoGlowne::informacje_Qt_wcisniety()
{
    QMessageBox::aboutQt(this, "Informacje o Qt");
}

void OknoGlowne::zmien_uzytkownika_wcisniety()
{
    this->wczytaj_dane();
}
