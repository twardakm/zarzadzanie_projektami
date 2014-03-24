#ifndef DODAWANIEUZYTKOWNIKA_H
#define DODAWANIEUZYTKOWNIKA_H

#include <QDialog>
#include <QSqlDatabase>
#include "ustawieniawstepne.h"

namespace Ui {
class DodawanieUzytkownika;
}

class DodawanieUzytkownika : public QDialog
{
    Q_OBJECT

public:
    explicit DodawanieUzytkownika(QWidget *parent = 0);
    DodawanieUzytkownika(QWidget *parent, QSqlDatabase *baza);
    ~DodawanieUzytkownika();

private slots:
    void przyciski_zaakceptowano();

private:
    Ui::DodawanieUzytkownika *ui;
};

#endif // DODAWANIEUZYTKOWNIKA_H
