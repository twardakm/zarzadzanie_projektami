#include "projekt.h"

Projekt::Projekt(QString adres, QString n, QString uz) :
    adres_bazy(adres), nazwa(n), uzytkownik(uz)
{
    admin = false;
}

Projekt::~Projekt()
{

}

void Projekt::ustaw_admin(bool a)
{
    this->admin = a;
}

QString Projekt::podaj_nazwe()
{
    return this->nazwa;
}

QString Projekt::podaj_adres()
{
    return this->adres_bazy;
}

bool Projekt::czy_admin()
{
    return admin;
}
