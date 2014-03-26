#ifndef USTAWIENIAWSTEPNE_H
#define USTAWIENIAWSTEPNE_H

#include <QWizard>
#include <QFileDialog>
#include <QDir>
#include <QtSql/QSqlDatabase>
#include <QtSql/QtSql>
#include <QtSql/QSqlQuery>
#include <QPalette>
#include <QStringList>
#include <QFileInfo>
#include <QCryptographicHash>

#include "dodawanieuzytkownika.h"
#include "oknoglowne.h"
#include "uzytkownik.h"

#define TABELA_UZYTKOWNICY "uzytkownicy"
#define TABELA_HASLO "haslo"
#define TABELA_NAZWA "nazwa"
#define TABELA_MAIL "mail"
#define KOLUMNA_NAZWA_SELECT "SELECT nazwa FROM uzytkownicy"
#define KOLUMNA_MAIL_SELECT "SELECT mail FROM uzytkownicy"
#define KOLUMNA_HASLO_SELECT "SELECT haslo FROM uzytkownicy"

namespace Ui {
class UstawieniaWstepne;
}

class UstawieniaWstepne : public QWizard
{
    Q_OBJECT

public:
    explicit UstawieniaWstepne(QWidget *parent = 0, Uzytkownik *u = 0);
    ~UstawieniaWstepne();

    bool sprawdz_poprawnosc_sqlite();

private slots:
    void przegladaj_wcisniety();
    void dodaj_uzytkownika_wcisniety();
    void utworz_wcisniety();
    void wyczysc_dane_formularza();

protected:
    QSqlDatabase baza;

private:
    Ui::UstawieniaWstepne *ui;
    Uzytkownik *uzytkownik;

    void odswiez_liste_uzytkownikow();
    bool sprawdz_dane_logowania();
    bool validateCurrentPage();
    void zaloguj_uzytkownika();
};

#endif // USTAWIENIAWSTEPNE_H
