#include "ustawieniawstepne.h"
#include "ui_ustawieniawstepne.h"

UstawieniaWstepne::UstawieniaWstepne(QWidget *parent, Uzytkownik *u) :
    QWizard(parent),
    ui(new Ui::UstawieniaWstepne),
    uzytkownik(u)
{
    this->activateWindow();
    ui->setupUi(this);
    //kolor błędu
    QPalette kolor;
    kolor.setColor(QPalette::WindowText, Qt::red);
    ui->blad->setPalette(kolor);
    ui->blad_logowania->setPalette(kolor);
    //-----------
    ui->blad->setText("");
    connect(ui->przegladaj, SIGNAL(clicked()), this, SLOT(przegladaj_wcisniety()));
    connect(ui->lista_uzytkownikow, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(wyczysc_dane_formularza()));
    connect(ui->utworz, SIGNAL(released()), this, SLOT(utworz_wcisniety()));
    connect(ui->dodaj_uzytkownika, SIGNAL(clicked()), this, SLOT(dodaj_uzytkownika_wcisniety()));
    odczytaj_plik_konfiguracyjny();
}

UstawieniaWstepne::~UstawieniaWstepne()
{
    if(baza.isOpen()) baza.close();
    if(ui != NULL) delete ui;
}

void UstawieniaWstepne::odczytaj_plik_konfiguracyjny()
{
    if(!QFile::exists("config.txt"))
    {
        ui->blad->setText("Tworzenie domyślnego pliku konfiguracyjnego");
        QFile plik("config.txt");
        if(!plik.open(QIODevice::ReadWrite))
        {
            ui->blad->setText("Nie udało się otworzyć pliku");
            return;
        }
        plik.write("zarzadzanie.sqlite");
        plik.close();
        ui->sciezka->addItem("zarzadzanie.sqlite");
        return;
    }

    QFile plik("config.txt");
    if (!plik.open(QIODevice::ReadOnly))
    {
        ui->blad->setText("Nie udało się otworzyć pliku konfiguracyjnego");
        return;
    }
    QString napis = plik.readAll();
    napis.remove(QChar('\n'));
    QStringList lista = napis.split(";", QString::SkipEmptyParts);
    plik.close();

    ui->sciezka->addItems(lista);
}

bool UstawieniaWstepne::validateCurrentPage()
{
    if (this->currentId() == 0)
    {
        if(!sprawdz_poprawnosc_sqlite())
            return false;
    }
    if (this->currentId() == 1)
    {
        if(!sprawdz_dane_logowania())
            return false;
        zaloguj_uzytkownika();
    }
    return true;
}

bool UstawieniaWstepne::sprawdz_dane_logowania()
{
    if (ui->lista_uzytkownikow->count() == 0)
    {
        ui->blad_logowania->setText("Brak użytkowników");
        return false;
    }
    QSqlQuery *zapytanie = new QSqlQuery(baza);
    zapytanie->exec("SELECT " + (QString)TABELA_HASLO +
                    " FROM " + (QString)TABELA_UZYTKOWNICY + " WHERE " +
                    (QString)TABELA_NAZWA + "='" +
                    ui->lista_uzytkownikow->currentItem()->text() +
                    "'");
    zapytanie->next();

    /*sprawdzenie hasła
     * ------------------------ */
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(ui->edycja_haslo->text().toLatin1());
    if(zapytanie->value(0).toString() != hash.result().toHex())
    {
        ui->blad_logowania->setText("Błędne hasło");
        ui->edycja_haslo->setText("");
        delete zapytanie;
        return false;
    }
    /* ------------------------ */

    delete zapytanie;
    baza.close();
    return true;
}

bool UstawieniaWstepne::sprawdz_poprawnosc_sqlite()
{
    //1. sprawdzanie czy istnieje plik
    if (!QFile::exists(ui->sciezka->currentText()))
    {
        ui->blad->setText("Podany plik nie istnieje");
        return false;
    }

    baza = QSqlDatabase::addDatabase("QSQLITE");
    baza.setDatabaseName(ui->sciezka->currentText());

    //2. sprawdzanie czy baza danych poprawnie się otworzyła
    if(!baza.open())
    {
        ui->blad->setText("Nie można otworzyć bazy danych");
        return false;
    }

    //3. sprawdzanie czy istnieje tabela użytkowników
    if (!baza.tables().contains(TABELA_UZYTKOWNICY))
    {
        baza.close();
        ui->blad->setText("Brak tabeli użytkowników. Błędna baza danych");
        return false;
    }

    //4. sprawdzanie czy istnieją kolumny
    if (!baza.exec(KOLUMNA_NAZWA_SELECT).exec() ||
        !baza.exec(KOLUMNA_MAIL_SELECT).exec() ||
        !baza.exec(KOLUMNA_HASLO_SELECT).exec())
    {
        baza.close();
        ui->blad->setText("Nieodpowiedni format bazy danych");
        return false;
    }

    //baza danych poprawna, przygotowanie ostatniej strony ustawien
    ui->edycja_haslo->setEchoMode(QLineEdit::Password);

    odswiez_liste_uzytkownikow();

    return true;
}

void UstawieniaWstepne::odswiez_liste_uzytkownikow()
{
    QSqlQuery *zapytanie = new QSqlQuery(baza);
    zapytanie->exec(KOLUMNA_NAZWA_SELECT);

    ui->lista_uzytkownikow->clear();

    while(zapytanie->next())
        ui->lista_uzytkownikow->addItem(zapytanie->value(0).toString());

    delete zapytanie;
}

void UstawieniaWstepne::zaloguj_uzytkownika()
{
    this->uzytkownik->zaloguj(
                ui->lista_uzytkownikow->currentItem()->text(),
                ui->edycja_mail->text(),
                ui->sciezka->currentText());
}

void UstawieniaWstepne::przegladaj_wcisniety()
{
    ui->sciezka->addItem(QFileDialog::getOpenFileName(this, tr("Wybierz plik bazy danych"),
                                               QApplication::applicationDirPath(), tr("Bazy danych (*.sqlite)")));
    ui->sciezka->setCurrentIndex(ui->sciezka->count()-1);
}

void UstawieniaWstepne::utworz_wcisniety()
{
    ui->sciezka->addItem(QFileDialog::getSaveFileName(this, tr("Utwórz bazę danych"),
                                               QApplication::applicationDirPath(), tr("Bazy danych (*.sqlite)")));
    QFile *plik = new QFile(ui->sciezka->currentText());
    plik->open(QIODevice::WriteOnly);
    plik->close();
    delete plik;

    baza = QSqlDatabase::addDatabase("QSQLITE");
    baza.setDatabaseName(ui->sciezka->currentText());

    //sprawdzanie czy baza danych poprawnie się otworzyła
    if(!baza.open())
    {
        ui->blad->setText("Nie można otworzyć bazy danych");
        return;
    }
    //sprawdzenie poprawności wykonania polecenia
    QSqlQuery *zapytanie = new QSqlQuery(baza);
    if (!zapytanie->exec("CREATE TABLE 'uzytkownicy' ('nazwa' TEXT, 'mail' TEXT, 'haslo' TEXT)") ||
        !zapytanie->exec("CREATE TABLE 'projekty' ('sciezka' TEXT, 'nazwa' TEXT)"))
    {
        ui->blad->setText("Błąd tworzenia tablicy");
        delete zapytanie;
        return;
    }
    else
        ui->blad->setText("");
    delete zapytanie;

    baza.close();
}

void UstawieniaWstepne::wyczysc_dane_formularza()
{
    ui->edycja_haslo->setText("");

    //ustawienia wyświetlania maila
    QSqlQuery *zapytanie = new QSqlQuery(baza);
    zapytanie->exec("SELECT " + (QString)TABELA_MAIL + " FROM " +
                    (QString)TABELA_UZYTKOWNICY + " WHERE "+
                    (QString)TABELA_NAZWA + "='" +
                    ui->lista_uzytkownikow->currentItem()->text() +
                    "'");
    zapytanie->next();
    ui->edycja_mail->setText(zapytanie->value(0).toString());

    delete zapytanie;
}

void UstawieniaWstepne::dodaj_uzytkownika_wcisniety()
{
    DodawanieUzytkownika dodawanie(this, &this->baza);
    dodawanie.exec();

    odswiez_liste_uzytkownikow();
}
