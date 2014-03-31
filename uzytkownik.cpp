#include "uzytkownik.h"

Uzytkownik::Uzytkownik() :
e_mail(""),
nazwa(""),
adres_bazy(""),
zalogowany(false)
{
}

Uzytkownik::Uzytkownik(QString n, QString e, QString a) :
e_mail(e),
nazwa(n),
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

QString Uzytkownik::podaj_e_mail()
{
    return this->e_mail;
}

QString Uzytkownik::podaj_adres_bazy()
{
    return this->adres_bazy;
}

void Uzytkownik::zaloguj(QString n, QString e, QString a)
{
    this->nazwa = n;
    this->e_mail = e;
    this->adres_bazy = a;
    this->zalogowany = true;
}

void Uzytkownik::wyloguj()
{
    this->e_mail = "";
    this->nazwa = "";
    this->adres_bazy = "";
    zalogowany = false;
}

bool usun_uzytkownika()
{
    return true;
}

bool usun_uzytkownika(QString haslo)
{
    haslo = "";
    return true;
}
