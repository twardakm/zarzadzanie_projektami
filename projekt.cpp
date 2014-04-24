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
