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

bool Uzytkownik::sprawdz_haslo(QString h)
{
    QSqlDatabase baza = QSqlDatabase::addDatabase("QSQLITE");
    baza.setDatabaseName(this->podaj_adres_bazy());

    if(!baza.open())
        return false;

    QSqlQuery zapytanie(baza);

    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(h.toLatin1());

    qDebug() << this->podaj_nazwe();

    zapytanie.exec("SELECT haslo FROM uzytkownicy "
                   "WHERE nazwa='" + this->podaj_nazwe() +"'");
    zapytanie.next();

    qDebug() << hash.result().toHex();
    qDebug() << zapytanie.value(0).toString();

    if(zapytanie.value(0).toString() != hash.result().toHex())
        return false;
    else
        return true;
}

bool Uzytkownik::usun_uzytkownika()
{
    QInputDialog input;
    input.setTextEchoMode(QLineEdit::Password);
    input.setLabelText("Potwierdź hasło użytkownika");
    input.exec();
    if(!this->usun_uzytkownika(input.textValue()))
        return false;
    return true;
}

bool Uzytkownik::usun_uzytkownika(QString haslo)
{
    if (!sprawdz_haslo(haslo))
        return false;
    QSqlDatabase baza = QSqlDatabase::addDatabase("QSQLITE");
    baza.setDatabaseName(this->podaj_adres_bazy());

    qDebug() << this->podaj_adres_bazy();

    if(!baza.open())
        return false;

    QSqlQuery zapytanie(baza);
    zapytanie.exec("SELECT nazwa FROM uzytkownicy "
                    "WHERE nazwa='" + this->podaj_nazwe() +"'");
    zapytanie.next();

    qDebug() << zapytanie.value(0).toString();

    if (zapytanie.value(0).toString() != this->podaj_nazwe())
        return false;

    if(!(zapytanie.exec("DELETE FROM uzytkownicy "
                   "WHERE nazwa='" + this->podaj_nazwe() +"'")))
        return false;

    return true;
}
