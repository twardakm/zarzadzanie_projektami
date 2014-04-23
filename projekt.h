#ifndef PROJEKT_H
#define PROJEKT_H

#include <QString>
#include <vector>
#include <iterator>
#include "uzytkownik.h"
#include "uczestnik.h"

class Projekt
{
private:
    QString nazwa;
    QString adres_bazy;
    vector<Uczestnik> uczestnik;

public:
    Projekt(QString adres);
};

#endif // PROJEKT_H
