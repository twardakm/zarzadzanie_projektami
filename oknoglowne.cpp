#include "oknoglowne.h"
#include "ui_oknoglowne.h"
#include "projekt.h"

OknoGlowne::OknoGlowne(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::OknoGlowne)
{
    ui->setupUi(this);
    projekt = NULL;

    ui->uczestnik_projektu->setText("");
    ui->nazwa_projektu->setText("");

    connect(ui->informacje_Qt, SIGNAL(triggered()),
            this, SLOT(informacje_Qt_wcisniety()));
    connect(ui->zmien_uzytkownika, SIGNAL(triggered()),
            this, SLOT(zmien_uzytkownika_wcisniety()));
    connect(ui->wyloguj, SIGNAL(triggered()),
            this, SLOT(wyloguj_wcisniety()));
    connect(ui->usun, SIGNAL(triggered()), this,
            SLOT(usun_wcisniety()));
    connect(ui->listaProjektow, SIGNAL(clicked(QModelIndex)), this,
            SLOT(listaProjektow_aktywny(QModelIndex)));
    connect(ui->terminarz, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this,
            SLOT(terminarz_itemClicked(QTreeWidgetItem*,int)));
    connect(ui->dodaj_przycisk, SIGNAL(clicked()), this,
            SLOT(dodaj_przycisk_clicked()));
    connect(ui->usun_przycisk, SIGNAL(clicked()), this,
            SLOT(usun_przycisk_clicked()));
    connect(ui->utworz_projekt_przycisk, SIGNAL(clicked()), this,
            SLOT(utworz_projekt_przycisk_clicked()));
    connect(ui->usun_projekt_przycisk, SIGNAL(clicked()), this,
            SLOT(usun_projekt_przycisk_clicked()));

    ui->terminarz->setExpandsOnDoubleClick(false);
    ui->terminarz->setMaximumHeight(200);
    ui->terminarz->setMaximumWidth(160);
    ui->terminarz->setColumnWidth(0,88);
    ui->terminarz->setColumnWidth(1,68);
    this->wczytaj_dane();
}

OknoGlowne::~OknoGlowne()
{
    if (ui != NULL) delete this->ui;
    if (projekt != NULL) delete this->projekt;
}

void OknoGlowne::wczytaj_dane()
{
    /*Wczytanie danych z bazy
     * -------------------- */
    UstawieniaWstepne okno(this, &uzytkownik);
    okno.exec();
    /* -------------------- */
    odswiez();
}

void OknoGlowne::odswiez()
{
    ui->nazwa_uzytkownika->setText(uzytkownik.podaj_nazwe());
    ui->menuUzytkownik->setTitle(uzytkownik.podaj_nazwe());
    ui->usun_projekt_przycisk->setDisabled(true);

    this->pokaz_projekty();
}

void OknoGlowne::pokaz_projekty()
{
    if (uzytkownik.podaj_nazwe() != "")
        ui->utworz_projekt_przycisk->setEnabled(true);
    else
        ui->utworz_projekt_przycisk->setDisabled(true);

    ui->listaProjektow->clear();
    QSqlDatabase *baza_projekt;
    QSqlQuery *projekt_zapytanie;
    //wczytanie adresu projektu
    baza = QSqlDatabase::addDatabase("QSQLITE");
    baza.setDatabaseName(uzytkownik.podaj_adres_bazy());

    if(!baza.open())
    {
        qDebug() << "Nie otworzono";
    }

    QSqlQuery *zapytanie = new QSqlQuery(uzytkownik.podaj_adres_bazy());
    zapytanie->exec("SELECT sciezka, nazwa FROM projekty");

    while(zapytanie->next())
    {
        baza_projekt = new QSqlDatabase;
        *baza_projekt = QSqlDatabase::addDatabase("QSQLITE");
        baza_projekt->setDatabaseName(zapytanie->value(0).toString());
        if(!baza_projekt->open())
        {
            ui->listaProjektow->addItem("Błąd otwarcia");
        }

        projekt_zapytanie = new QSqlQuery(zapytanie->value(0).toString());
        projekt_zapytanie->exec("SELECT admin FROM administratorzy WHERE admin='" + uzytkownik.podaj_nazwe() +"'");
        if (projekt_zapytanie->next())
            ui->listaProjektow->addItem(zapytanie->value(1).toString());
        else
        {
            projekt_zapytanie->exec("SELECT uzytkownik FROM uzytkownicy WHERE uzytkownik='" + uzytkownik.podaj_nazwe() + "'");
            if (projekt_zapytanie->next())
                ui->listaProjektow->addItem(zapytanie->value(1).toString());
        }

        delete projekt_zapytanie;
        baza_projekt->close();
        delete baza_projekt;
        //zczytanie projektów
    }

    delete zapytanie;
    baza.close();
}

void OknoGlowne::pokaz_uczestnikow()
{
    ui->listaUczestnikow->clear();
    ui->listaUczestnikow->addItem("Uczestnicy:");

    baza = QSqlDatabase::addDatabase("QSQLITE");
    baza.setDatabaseName(uzytkownik.podaj_adres_bazy());

    if(!baza.open())
    {
        qDebug() << "Nie otworzono";
    }
    QSqlQuery *zapytanie = new QSqlQuery(uzytkownik.podaj_adres_bazy());
    qDebug() << "Zaznaczony projekt: " << ui->listaProjektow->currentItem()->text();
    zapytanie->exec("SELECT sciezka FROM projekty WHERE nazwa='" + ui->listaProjektow->currentItem()->text() + "'");
    zapytanie->next();
    //otwarcie bazy danych z projektem
    QSqlDatabase *baza_projekt = new QSqlDatabase;
    *baza_projekt = QSqlDatabase::addDatabase("QSQLITE");
    baza_projekt->setDatabaseName(zapytanie->value(0).toString());
    if(!baza_projekt->open())
    {
        ui->listaUczestnikow->addItem("Błąd otwarcia");
    }
    else
    {
        //utworzenie projektu
        if (projekt != NULL)
            delete projekt;
        projekt = new Projekt(zapytanie->value(0).toString(), ui->listaProjektow->currentItem()->text(), uzytkownik.podaj_nazwe());

        QSqlQuery *projekt_zapytanie;
        projekt_zapytanie = new QSqlQuery(zapytanie->value(0).toString());
        projekt_zapytanie->exec("SELECT uzytkownik FROM uzytkownicy");
        while (projekt_zapytanie->next())
        {
            ui->listaUczestnikow->addItem(projekt_zapytanie->value(0).toString());
            if (projekt_zapytanie->value(0).toString() == uzytkownik.podaj_nazwe())
                projekt->ustaw_admin(false);
        }
        projekt_zapytanie->exec("SELECT admin FROM administratorzy");
        ui->listaUczestnikow->addItem("Administratorzy:");
        while (projekt_zapytanie->next())
        {
            ui->listaUczestnikow->addItem(projekt_zapytanie->value(0).toString());
            if (projekt_zapytanie->value(0).toString() == uzytkownik.podaj_nazwe())
                projekt->ustaw_admin(true);
        }
        delete projekt_zapytanie;
    }

    delete baza_projekt;
    delete zapytanie;
    baza.close();

    if (projekt != NULL)
        pokaz_projekt();
}

void OknoGlowne::pokaz_projekt()
{
    if (ui->listaProjektow->currentRow() >= 0)
        ui->usun_projekt_przycisk->setEnabled(true);
    else
        ui->usun_projekt_przycisk->setDisabled(true);

    ui->nazwa_projektu->setText(projekt->podaj_nazwe());
    if (projekt->czy_admin())
        ui->uczestnik_projektu->setText("Administrator");
    else
        ui->uczestnik_projektu->setText("Uczestnik");

    baza = QSqlDatabase::addDatabase("QSQLITE");
    baza.setDatabaseName(projekt->podaj_adres());

    if(!baza.open())
    {
        //dopisać co jak się baza nie otworzy
    }

    ui->terminarz->clear();
    QList<QTreeWidgetItem *> lista_dane_terminarz;
    QTreeWidgetItem *item_dane_terminarz;

    QSqlQuery *zapytanie = new QSqlQuery(projekt->podaj_adres());
    zapytanie->exec("SELECT * FROM terminarz");

    while(zapytanie->next())
    {
        item_dane_terminarz = new QTreeWidgetItem(ui->terminarz);

        item_dane_terminarz->setTextAlignment(0, Qt::AlignLeft);
        item_dane_terminarz->setTextAlignment(1, Qt::AlignLeft);
        item_dane_terminarz->setText(0,zapytanie->value(0).toDate().toString("dd.MM.yyyy"));
        item_dane_terminarz->setText(1,zapytanie->value(1).toDate().toString("dd.MM.yyyy"));
        item_dane_terminarz->setText(2,zapytanie->value(2).toString());

        lista_dane_terminarz.append(item_dane_terminarz);

    }

    ui->terminarz->addTopLevelItems(lista_dane_terminarz);

    baza.close();

    if (projekt->czy_admin())
    {
        ui->dodaj_przycisk->setEnabled(true);
        ui->usun_przycisk->setEnabled(true);
    }
    else
    {
        ui->dodaj_przycisk->setDisabled(true);
        ui->usun_przycisk->setDisabled(true);
    }

}

void OknoGlowne::informacje_Qt_wcisniety()
{
    QMessageBox::aboutQt(this, "Informacje o Qt");
}

void OknoGlowne::zmien_uzytkownika_wcisniety()
{
    this->wczytaj_dane();
}

void OknoGlowne::wyloguj_wcisniety()
{
    this->uzytkownik.wyloguj();
    this->odswiez();
}

void OknoGlowne::usun_wcisniety()
{
    if(!this->uzytkownik.usun_uzytkownika())
    {
        QMessageBox::warning(this,"Usunięcie użytkownika",
                             "Nie udało się usunąć użytkownika");
        return;
    }
    else
    {
        QMessageBox::information(this, "Usunięcie użytkownika",
                                 "Poprawnie usunięto użytkownika");
    }
    this->uzytkownik.wyloguj();
    this->odswiez();
}

void OknoGlowne::listaProjektow_aktywny(const QModelIndex &index)
{
    if (index.isValid())
        this->pokaz_uczestnikow();
}

void OknoGlowne::terminarz_itemClicked(QTreeWidgetItem *item, int column)
{
    if (column >= 0)
    {
        ui->terminarz_opis->clear();
        ui->terminarz_opis->setText(item->text(2));
    }
}

void OknoGlowne::dodaj_przycisk_clicked()
{
    DodawanieTerminu okno(projekt->podaj_adres(), this);
    okno.exec();
    this->pokaz_projekt();
}

void OknoGlowne::usun_przycisk_clicked()
{
    qDebug() << ui->terminarz->currentItem()->text(0);
    QSqlDatabase *baza_projekt;
    QSqlQuery *projekt_zapytanie;

    baza_projekt = new QSqlDatabase;
    *baza_projekt = QSqlDatabase::addDatabase("QSQLITE");
    baza_projekt->setDatabaseName(projekt->podaj_adres());

    if(!baza_projekt->open())
    {
        QMessageBox::warning(this, tr("Zarządzanie projektami"),
                             tr("Nie udało się otworzyć bazy danych"),
                             QMessageBox::Ok);
        delete baza_projekt;

        return;
    }

    projekt_zapytanie = new QSqlQuery(projekt->podaj_adres());

    if(!projekt_zapytanie->exec(
                "DELETE FROM terminarz WHERE data_od='"
                + QDate::fromString(ui->terminarz->currentItem()->text(0),
                                    "dd.MM.yyyy").toString("yyyy-MM-dd") +
                "' and data_do='" +
                QDate::fromString(ui->terminarz->currentItem()->text(1),
                                    "dd.MM.yyyy").toString("yyyy-MM-dd") +
                "' and opis='" + ui->terminarz->currentItem()->text(2) + "'"))
    {
        QMessageBox::warning(this, tr("Zarządzanie projektami"),
                             tr("Nie udało się otworzyć bazy danych"),
                             QMessageBox::Ok);

        delete projekt_zapytanie;
        delete baza_projekt;

        return;
    }

    delete projekt_zapytanie;
    delete baza_projekt;

    this->pokaz_projekt();
}

void OknoGlowne::utworz_projekt_przycisk_clicked()
{
   UtworzProjekt okno(uzytkownik.podaj_adres_bazy(), uzytkownik.podaj_nazwe(), this);
   okno.exec();
   pokaz_projekty();
}

void OknoGlowne::usun_projekt_przycisk_clicked()
{
    if(QMessageBox::question(this, "Usuwanie projektu", "Czy na pewno chcesz usunąć bieżący projekt: " +
                             ui->listaProjektow->currentItem()->text() + "?",
                             QMessageBox::Apply|QMessageBox::No) == QMessageBox::Apply)
    {

        baza = QSqlDatabase::addDatabase("QSQLITE");
        baza.setDatabaseName(uzytkownik.podaj_adres_bazy());

        if(!baza.open())
        {
            QMessageBox::warning(this, "Usuwanie projektu", "Nie udało się połączyć z bazą danych");
            return;
        }

        QSqlQuery *zapytanie = new QSqlQuery(uzytkownik.podaj_adres_bazy());

        zapytanie->exec("SELECT sciezka FROM projekty WHERE nazwa='" + ui->listaProjektow->currentItem()->text() + "'");
        zapytanie->next();

        if(!QFile::remove(zapytanie->value(0).toString()))
        {
            QMessageBox::warning(this, "Usuwanie projektu", "Nie udało się połączyć z bazą danych");
            delete zapytanie;
            return;
        }

        if (!zapytanie->exec("DELETE FROM projekty WHERE nazwa='" + ui->listaProjektow->currentItem()->text() + "'"))
        {
            QMessageBox::warning(this, "Usuwanie projektu", "Nie udało się połączyć z bazą danych");
            delete zapytanie;
            return;
        }
        delete zapytanie;

        baza.close();

        this->odswiez();
    }
}
