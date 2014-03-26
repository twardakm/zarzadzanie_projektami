#include "uzytkownik.h"

Uzytkownik::Uzytkownik() :
nazwa(""), e_mail(""), adres_bazy(""), zalogowany(false)
{
}

Uzytkownik::Uzytkownik(QString n, QString e, QString a) :
nazwa(n),
e_mail(e),
adres_bazy(a),
zalogowany(true)
{
}

Uzytkownik::~Uzytkownik()
{
}

QString Uzytkownik::podaj_nazwe()
{
    return this->nazwa;
}

void Uzytkownik::zaloguj(QString n, QString e, QString a)
{
    this->nazwa = n;
    this->e_mail = e;
    this->adres_bazy = a;
    this->zalogowany = true;
}
