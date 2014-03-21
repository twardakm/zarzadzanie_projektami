#include "ustawieniawstepne.h"
#include "ui_ustawieniawstepne.h"

UstawieniaWstepne::UstawieniaWstepne(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::UstawieniaWstepne)
{
    ui->setupUi(this);
    ui->sciezka->insert("zarzadzanie.sqlite");
    //kolor błędu
    QPalette kolor;
    kolor.setColor(QPalette::WindowText, Qt::red);
    ui->blad->setPalette(kolor);
    //-----------
    ui->blad->setText("");
    connect(ui->przegladaj, SIGNAL(clicked()), this, SLOT(przegladaj_wcisniety()));
}

UstawieniaWstepne::~UstawieniaWstepne()
{
    delete ui;
}

bool UstawieniaWstepne::validateCurrentPage()
{
    if (this->currentId() == 0)
    {
        if(!sprawdz_poprawnosc_sqlite())
            return false;
    }
    return true;
}

bool UstawieniaWstepne::sprawdz_poprawnosc_sqlite()
{

    //1. sprawdzanie czy istnieje plik
    if (!QFileInfo::exists(ui->sciezka->text()))
    {
        ui->blad->setText("Podany plik nie istnieje");
        return false;
    }

    QSqlDatabase baza;
    baza = QSqlDatabase::addDatabase("QSQLITE");
    baza.setDatabaseName(ui->sciezka->text());

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

    baza.close();
    return true;
}

void UstawieniaWstepne::przegladaj_wcisniety()
{
    ui->sciezka->selectAll();
    ui->sciezka->insert(QFileDialog::getOpenFileName(this, tr("Wybierz plik bazy danych"),
                                               QApplication::applicationDirPath(), tr("Bazy danych (*.sqlite)")));
}
