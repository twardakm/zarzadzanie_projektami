#ifndef DODAWANIEUZYTKOWNIKA_H
#define DODAWANIEUZYTKOWNIKA_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "ustawieniawstepne.h"

namespace Ui {
class DodawanieUzytkownika;
}

class DodawanieUzytkownika : public QDialog
{
    Q_OBJECT

public:
    explicit DodawanieUzytkownika(QWidget *parent = 0);
    DodawanieUzytkownika(QWidget *parent, QSqlDatabase *ba);
    ~DodawanieUzytkownika();

    bool sprawdz_haslo();
    bool sprawdz_mail();
    bool sprawdz_uzytkownika();

private slots:
    void zatwierdz_wcisniety();
    void anuluj_wcisniety();

private:
    Ui::DodawanieUzytkownika *ui;
    QSqlDatabase baza;
};

#endif // DODAWANIEUZYTKOWNIKA_H
