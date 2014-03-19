#ifndef OKNOGLOWNE_H
#define OKNOGLOWNE_H

#include <QMainWindow>
#include <QInputDialog>
#include <list>
#include <iterator>

#include "ustawieniawstepne.h"

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


private:
    Ui::OknoGlowne *ui;

    UstawieniaWstepne *okno;
    QString *uzytkownik;
    std::list <QString> projekty; //lista projektów do których jest przypisany użytkownik
};


#endif // OKNOGLOWNE_H
