#ifndef OKNOGLOWNE_H
#define OKNOGLOWNE_H

#include <QMainWindow>
#include <QInputDialog>
#include <QMessageBox>
#include <QIcon>
#include <list>
#include <iterator>

#include "ustawieniawstepne.h"
#include "uzytkownik.h"

namespace Ui {
class OknoGlowne;
}

class OknoGlowne : public QMainWindow
{
    Q_OBJECT

public:
    explicit OknoGlowne(QWidget *parent = 0);
    ~OknoGlowne();

    void wczytaj_dane(); //wczytuje dane z bazy danych

protected:
    Uzytkownik uzytkownik;

private slots:
    void informacje_Qt_wcisniety();
    void zmien_uzytkownika_wcisniety();
    void wyloguj_wcisniety();
    void usun_wcisniety();

private:
    Ui::OknoGlowne *ui;
    void odswiez();
};


#endif // OKNOGLOWNE_H
