#-------------------------------------------------
#
# Project created by QtCreator 2014-03-15T11:17:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zarzadzanie_projektami
TEMPLATE = app


SOURCES += main.cpp\
        oknoglowne.cpp \
    uzytkownik.cpp \
    ustawieniawstepne.cpp \
    dodawanieuzytkownika.cpp \
    uczestnik.cpp \
    projekt.cpp \
    dodawanieprojektu.cpp

HEADERS  += oknoglowne.h \
    uzytkownik.h \
    ustawieniawstepne.h \
    dodawanieuzytkownika.h \
    uczestnik.h \
    projekt.h \
    dodawanieprojektu.h

FORMS    += oknoglowne.ui \
    ustawieniawstepne.ui \
    dodawanieuzytkownika.ui \
    dodawanieprojektu.ui

RC_FILE = zarzadzanie_projektami.rc
