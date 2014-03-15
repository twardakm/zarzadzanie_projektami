#ifndef OKNOGLOWNE_H
#define OKNOGLOWNE_H

#include <QMainWindow>

namespace Ui {
class OknoGlowne;
}

class OknoGlowne : public QMainWindow
{
    Q_OBJECT

public:
    explicit OknoGlowne(QWidget *parent = 0);
    ~OknoGlowne();

private:
    Ui::OknoGlowne *ui;
};

#endif // OKNOGLOWNE_H
