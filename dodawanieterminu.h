#ifndef DODAWANIETERMINU_H
#define DODAWANIETERMINU_H

#include <QDialog>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDate>

namespace Ui {
class DodawanieTerminu;
}

class DodawanieTerminu : public QDialog
{
    Q_OBJECT

public:
    explicit DodawanieTerminu(QString b, QWidget *parent = 0);
    ~DodawanieTerminu();

private slots:
    void zatwierdz_wcisniety();

    void anuluj_wcisniety();

private:
    Ui::DodawanieTerminu *ui;
    QString adres_bazy;
};

#endif // DODAWANIETERMINU_H
