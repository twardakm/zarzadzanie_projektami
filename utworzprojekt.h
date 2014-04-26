#ifndef UTWORZPROJEKT_H
#define UTWORZPROJEKT_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QPalette>
#include <QDir>
#include <QDebug>

namespace Ui {
class UtworzProjekt;
}

class UtworzProjekt : public QDialog
{
    Q_OBJECT

public:
    explicit UtworzProjekt(QString adres_b, QString a, QWidget *parent = 0);
    ~UtworzProjekt();

private slots:
    void zatwierdz_przycisk_clicked();
    void anuluj_przycisk_clicked();
    void uzytkownik_przycisk_clicked();
    void administrator_przycisk_clicked();

private:
    Ui::UtworzProjekt *ui;
    QString adres_baza;
    QString admin;
};

#endif // UTWORZPROJEKT_H
