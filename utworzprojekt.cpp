#include "utworzprojekt.h"
#include "ui_utworzprojekt.h"

UtworzProjekt::UtworzProjekt(QString adres_b, QString a ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UtworzProjekt),
    adres_baza(adres_b),
    admin(a)
{
    ui->setupUi(this);

    connect(ui->zatwierdz_przycisk, SIGNAL(clicked()), this,
            SLOT(zatwierdz_przycisk_clicked()));
    connect(ui->anuluj_przycisk, SIGNAL(clicked()), this,
            SLOT(anuluj_przycisk_clicked()));
    connect(ui->uzytkownik_przycisk, SIGNAL(clicked()), this,
            SLOT(uzytkownik_przycisk_clicked()));
    connect(ui->administrator_przycisk, SIGNAL(clicked()), this,
            SLOT(administrator_przycisk_clicked()));

    QPalette kolor;
    kolor.setColor(QPalette::WindowText, Qt::red);
    ui->blad_label->setPalette(kolor);
    ui->blad_label->setText("");


    //zapełnienie listy użytkowników
    //------------------------------------
    ui->lista_administratorzy->addItem(admin);

    QSqlDatabase *baza = new QSqlDatabase;
    *baza = QSqlDatabase::addDatabase("QSQLITE");
    baza->setDatabaseName(adres_baza);
    if(!baza->open())
    {
        QMessageBox::warning(this,"Dodawanie projektu",
                             "Nie udało się stworzyć bazy danych");
        delete baza;
        return;
    }
    QSqlQuery *zapytanie_baza = new QSqlQuery(adres_baza);
    ui->lista_wszyscy->clear();
    zapytanie_baza->exec("SELECT nazwa FROM uzytkownicy WHERE nazwa<>'" +
                         admin + "'");
    while (zapytanie_baza->next())
        ui->lista_wszyscy->addItem(zapytanie_baza->value(0).toString());

    baza->close();
    delete zapytanie_baza;
    delete baza;
    //--------------------------------------
}

UtworzProjekt::~UtworzProjekt()
{
    delete ui;
}

void UtworzProjekt::uzytkownik_przycisk_clicked()
{
    if (ui->lista_wszyscy->currentRow() >= 0)
        ui->lista_uzytkownicy->addItem(ui->lista_wszyscy->takeItem(ui->lista_wszyscy->currentRow())->text());
}

void UtworzProjekt::administrator_przycisk_clicked()
{
    if (ui->lista_wszyscy->currentRow() >= 0)
        ui->lista_administratorzy->addItem(ui->lista_wszyscy->takeItem(ui->lista_wszyscy->currentRow())->text());
}

void UtworzProjekt::zatwierdz_przycisk_clicked()
{
    if (ui->nazwa_edit->text() == "")
    {
        ui->blad_label->setText("Pusta nazwa projektu");
        return;
    }
    if (ui->adres_edit->text() == "")
    {
        ui->blad_label->setText("Pusta nazwa bazy");
        return;
    }

    qDebug() << QDir::currentPath() + "/" + ui->adres_edit->text();

    QSqlDatabase *baza_projekt = new QSqlDatabase;
    *baza_projekt = QSqlDatabase::addDatabase("QSQLITE");
    baza_projekt->setDatabaseName(ui->adres_edit->text());
    if(!baza_projekt->open())
    {
        QMessageBox::warning(this,"Dodawanie projektu",
                             "Nie udało się stworzyć bazy danych");
        delete baza_projekt;
        return;
    }

    QSqlQuery *zapytanie = new QSqlQuery(ui->adres_edit->text());
    if (!zapytanie->exec("CREATE TABLE 'nazwa' ('projekt' TEXT)") ||
        !zapytanie->exec("CREATE TABLE 'administratorzy' ('admin' TEXT)") ||
        !zapytanie->exec("CREATE TABLE 'uzytkownicy' ('uzytkownik' TEXT)") ||
        !zapytanie->exec("CREATE TABLE 'terminarz' ('data_od' DATETIME, 'data_do' DATETIME, 'opis' TEXT)"))
    {
        QMessageBox::warning(this,"Dodawanie projektu",
                             "Nie udało się stworzyć bazy danych");
        baza_projekt->close();
        delete zapytanie;
        delete baza_projekt;
        return;
    }

    QString uzytkownicy("");
    QString administratorzy("");

    for (int i = 0; i < ui->lista_uzytkownicy->count(); i++)
    {
        uzytkownicy += "('" + ui->lista_uzytkownicy->item(i)->text() + "')";
        if (i+1 < ui->lista_uzytkownicy->count())
            uzytkownicy += ", ";
    }

    for (int i = 0; i < ui->lista_administratorzy->count(); i++)
    {
        administratorzy += "('" + ui->lista_administratorzy->item(i)->text() + "')";
        if (i+1 < ui->lista_administratorzy->count())
            administratorzy += ", ";
    }

    qDebug() << uzytkownicy;
    qDebug() << administratorzy;

    if (!zapytanie->exec("INSERT INTO nazwa VALUES ('" + ui->nazwa_edit->text() + "')") ||
        !zapytanie->exec("INSERT INTO administratorzy VALUES " + administratorzy) ||
        !zapytanie->exec("INSERT INTO uzytkownicy VALUES " + uzytkownicy))
    {
        QMessageBox::warning(this,"Dodawanie projektu",
                             "Nie udało się stworzyć bazy danych");
        baza_projekt->close();
        delete zapytanie;
        delete baza_projekt;
        return;
    }

    delete zapytanie;
    baza_projekt->close();

    //dodanie ścieżki do głównej bazy danych

    QSqlDatabase *baza = new QSqlDatabase;
    *baza = QSqlDatabase::addDatabase("QSQLITE");
    baza->setDatabaseName(adres_baza);
    if(!baza->open())
    {
        QMessageBox::warning(this,"Dodawanie projektu",
                             "Nie udało się dodać adresu");
        delete baza;
        return;
    }

    qDebug() << "Polecenie bazy: " << "INSERT INTO projekty VALUES ('" +
                QDir::currentPath() + "/" + ui->adres_edit->text() + "' ,'" +
                ui->nazwa_edit->text() + "')";

    zapytanie = new QSqlQuery(adres_baza);
    if (!zapytanie->exec("INSERT INTO projekty VALUES ('" +
                        QDir::currentPath() + "/" + ui->adres_edit->text() + "' ,'" +
                        ui->nazwa_edit->text() + "')"))
    {
        QMessageBox::warning(this,"Dodawanie projektu",
                             "Nie udało się dodać adresu");
        baza_projekt->close();
        delete zapytanie;
        delete baza_projekt;
        return;
    }

    baza->close();
    delete baza;
    delete zapytanie;
    delete baza_projekt;
    this->accept();
}

void UtworzProjekt::anuluj_przycisk_clicked()
{
    this->reject();
}
