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
    void zaloguj(QString n, QString e, QString a);
};

#endif // UZYTKOWNIK_H
