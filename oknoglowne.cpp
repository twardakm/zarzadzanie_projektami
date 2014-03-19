#include "oknoglowne.h"
#include "ui_oknoglowne.h"

OknoGlowne::OknoGlowne(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::OknoGlowne)
{
    ui->setupUi(this);
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
    okno->show();
    /* -------------------- */
}
