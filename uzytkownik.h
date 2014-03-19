#ifndef UZYTKOWNIK_H
#define UZYTKOWNIK_H

#include <QString>

class Uzytkownik
{
private:
    QString haslo;
    QString e_mail;
protected:
    QString nazwa;
public:
    Uzytkownik(QString nazwa, QString haslo, QString e_mail);
    Uzytkownik();
    ~Uzytkownik();
};

#endif // UZYTKOWNIK_H
