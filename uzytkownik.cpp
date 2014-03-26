#include "uzytkownik.h"

Uzytkownik::Uzytkownik() :
haslo(""), nazwa(""), e_mail("")
{
}

Uzytkownik::Uzytkownik(QString n, QString h, QString e) :
haslo(h), nazwa(n), e_mail(e)
{
}

Uzytkownik::~Uzytkownik()
{

}
