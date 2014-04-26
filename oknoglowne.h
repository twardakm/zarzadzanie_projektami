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
#include "dodawanieterminu.h"
#include "utworzprojekt.h"

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
    Projekt *projekt;

private slots:
    void informacje_Qt_wcisniety();
    void zmien_uzytkownika_wcisniety();
    void wyloguj_wcisniety();
    void usun_wcisniety();

    void listaProjektow_aktywny(const QModelIndex &index);

    void terminarz_itemClicked(QTreeWidgetItem *item, int column);

    void dodaj_przycisk_clicked();
    void usun_przycisk_clicked();

    void utworz_projekt_przycisk_clicked();

private:
    Ui::OknoGlowne *ui;
};


#endif // OKNOGLOWNE_H
