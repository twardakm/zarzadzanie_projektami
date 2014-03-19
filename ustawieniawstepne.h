#ifndef USTAWIENIAWSTEPNE_H
#define USTAWIENIAWSTEPNE_H

#include <QWizard>
#include <QFileDialog>
#include <QDir>

namespace Ui {
class UstawieniaWstepne;
}

class UstawieniaWstepne : public QWizard
{
    Q_OBJECT

public:
    explicit UstawieniaWstepne(QWidget *parent = 0);
    ~UstawieniaWstepne();

    void sprawdz_poprawnosc_sqlite();

private slots:
    void przegladaj_wcisniety();

private:
    Ui::UstawieniaWstepne *ui;
};

#endif // USTAWIENIAWSTEPNE_H
