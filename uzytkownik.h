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
    Uzytkownik();
    Uzytkownik(QString n, QString h, QString e);
    ~Uzytkownik();
};

#endif // UZYTKOWNIK_H
