#ifndef OKNOGLOWNE_H
#define OKNOGLOWNE_H

#include <QMainWindow>
#include <QInputDialog>
#include <QMessageBox>
#include <QIcon>
#include <QTreeWidgetItem>

#include "projekt.h"
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
    void pokaz_projekty();
    void pokaz_uczestnikow();
    void pokaz_projekt();
    void odswiez();
    QSqlDatabase baza;

private slots:
    void informacje_Qt_wcisniety();
    void zmien_uzytkownika_wcisniety();
    void wyloguj_wcisniety();
    void usun_wcisniety();

    void listaProjektow_aktywny(const QModelIndex &index);

    void terminarz_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::OknoGlowne *ui;
    Projekt * projekt;
};


#endif // OKNOGLOWNE_H
