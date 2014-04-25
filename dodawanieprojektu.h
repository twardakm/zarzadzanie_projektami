#ifndef DODAWANIEPROJEKTU_H
#define DODAWANIEPROJEKTU_H

#include <QWidget>

namespace Ui {
class DodawanieProjektu;
}

class DodawanieProjektu : public QWidget
{
    Q_OBJECT

public:
    explicit DodawanieProjektu(QWidget *parent = 0);
    ~DodawanieProjektu();

private:
    Ui::DodawanieProjektu *ui;
};

#endif // DODAWANIEPROJEKTU_H
