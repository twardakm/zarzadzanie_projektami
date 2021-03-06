#ifndef PROJEKT_H
#define PROJEKT_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "uzytkownik.h"
#include "uczestnik.h"

class Projekt
{
private:
    QString nazwa;
    QString adres_bazy;
    QString uzytkownik;
    bool admin;

public:
    Projekt(QString adres, QString n, QString uz);
    ~Projekt();

    void ustaw_admin(bool a);

    QString podaj_nazwe();
    QString podaj_adres();
    bool czy_admin();
};

#endif // PROJEKT_H
