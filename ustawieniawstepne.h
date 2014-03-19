#ifndef USTAWIENIAWSTEPNE_H
#define USTAWIENIAWSTEPNE_H

#include <QWizard>
#include <QFileDialog>
#include <QDir>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QtSql>
#include <QPalette>

namespace Ui {
class UstawieniaWstepne;
}

class UstawieniaWstepne : public QWizard
{
    Q_OBJECT

public:
    explicit UstawieniaWstepne(QWidget *parent = 0);
    ~UstawieniaWstepne();

    bool sprawdz_poprawnosc_sqlite();

private slots:
    void przegladaj_wcisniety();

private:
    Ui::UstawieniaWstepne *ui;
    bool validateCurrentPage();
};

#endif // USTAWIENIAWSTEPNE_H
