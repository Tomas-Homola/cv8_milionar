#pragma once

#include <QtWidgets/QMainWindow>
#include <ui_cv8_milionar.h>

class cv8_milionar : public QMainWindow
{
    Q_OBJECT

public:
    cv8_milionar(QWidget *parent = Q_NULLPTR);

private:
    Ui::cv8_milionarClass ui;

private slots:
    void on_pushButtonNewGame_clicked(); // nova hra
    void on_pushButtonEndGame_clicked(); // koniec hry
    void on_pushButtonAccept_clicked(); // potvrdenie vyberu
    void on_pushButtonSkip_clicked(); // preskocenie otazky

    void on_pushButtonZolik1(); // zolik 1
    void on_pushButtonZolik2(); // zolik 2
    void on_pushButtonZolik3(); // zolik 3
};
