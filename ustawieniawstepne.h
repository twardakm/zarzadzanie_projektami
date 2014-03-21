#ifndef USTAWIENIAWSTEPNE_H
#define USTAWIENIAWSTEPNE_H

#include <QWizard>
#include <QFileDialog>
#include <QDir>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QtSql>
#include <QSqlQuery>
#include <QtSql/QSqlQuery>
#include <QPalette>
#include <QStringList>
#include <QFileInfo>

#define TABELA_UZYTKOWNICY "uzytkownicy"
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
    explicit UstawieniaWstepne(QWidget *parent = 0);
    ~UstawieniaWstepne();

    bool sprawdz_poprawnosc_sqlite();

private slots:
    void przegladaj_wcisniety();

private:
    Ui::UstawieniaWstepne *ui;
    QSqlDatabase baza;

    bool validateCurrentPage();
    bool sprawdz_dane_logowania();
};

#endif // USTAWIENIAWSTEPNE_H
