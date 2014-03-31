#ifndef UZYTKOWNIK_H
#define UZYTKOWNIK_H

#include <QString>

class Uzytkownik
{
private:
    QString e_mail;
protected:
    QString nazwa;
    QString adres_bazy;

    bool zalogowany;
public:
    Uzytkownik();
    Uzytkownik(QString n, QString e, QString a);
    ~Uzytkownik();

    QString podaj_nazwe();
    QString podaj_e_mail();
    QString podaj_adres_bazy();

    void zaloguj(QString n, QString e, QString a);
    void wyloguj();

    bool usun_uzytkownika();
    bool usun_uzytkownika(QString haslo);

    bool zmien_haslo();
    bool zmien_haslo(QString stare_haslo, QString haslo);

    bool zmien_nazwe();
    bool zmien_nazwe(QString haslo, QString nowa_nazwa);
};

#endif // UZYTKOWNIK_H
