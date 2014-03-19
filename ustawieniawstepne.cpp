#include "ustawieniawstepne.h"
#include "ui_ustawieniawstepne.h"

UstawieniaWstepne::UstawieniaWstepne(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::UstawieniaWstepne)
{
    ui->setupUi(this);
    ui->sciezka->insert("zarzadzanie.sqlite");
    connect(ui->przegladaj, SIGNAL(clicked()), this, SLOT(przegladaj_wcisniety()));
}

UstawieniaWstepne::~UstawieniaWstepne()
{
    delete ui;
}

void UstawieniaWstepne::przegladaj_wcisniety()
{
    ui->sciezka->insert(QFileDialog::getOpenFileName(this, tr("Wybierz plik bazy danych"),
                                               QApplication::applicationDirPath(), tr("Bazy danych (*.sqlite)")));
}
