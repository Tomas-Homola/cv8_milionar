#pragma once

#include <QtWidgets/QMainWindow>
#include <ui_cv8_milionar.h>
#include "QandA.h"
#include "player.h"

class cv8_milionar : public QMainWindow
{
    Q_OBJECT

public:
    cv8_milionar(QWidget *parent = Q_NULLPTR);

private:
    Ui::cv8_milionarClass ui;

    int questionNum = 0;
    int numOfQuestions = 0;
    int temp[10] = { 0,1,2,3,4,5,6,8,9 };

    //QandA otazky[10];
    QandA* questions;
    Player player;

    bool loadQuestions(std::string fileName); // nacitanie otazok z txt suboru
    void shuffleAnswers(QandA& q);

private slots:
    void on_pushButtonNewGame_clicked(); // nova hra
    void on_pushButtonEndGame_clicked(); // koniec hry
    void on_pushButtonAccept_clicked(); // potvrdenie vyberu
    void on_pushButtonSkip_clicked(); // preskocenie otazky

    void on_pushButtonZolik1_clicked(); // zolik 1
    void on_pushButtonZolik2_clicked(); // zolik 2
    void on_pushButtonZolik3_clicked(); // zolik 3
};
