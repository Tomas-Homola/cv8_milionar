#include "cv8_milionar.h"
#include <iostream>
#include <string>
#include <fstream>

using std::cout;
using std::endl;

bool cv8_milionar::loadQuestions(std::string fileName)
{
    std::string temp = "";
    std::fstream textFile;
    textFile.open(fileName, std::ios::in);

    if (textFile.is_open() == false)
        return false;

    std::getline(textFile, temp);
    numOfQuestions = std::stoi(temp);

    questions = new QandA[numOfQuestions];

    for (int i = 0; i < numOfQuestions; i++)
    {
        std::getline(textFile, temp); // precitanie otazky
        questions[i].setQestion(temp); // nastavenie otazky
        
        // precitanie a nastavenie odpovedi
        for (int j = 0; j < 4; j++)
        {
            std::getline(textFile, temp);
            questions[i].setAnswer(j, temp);
        }
        
        /*std::getline(textFile, temp);
        questions[i].setCorrectAnswer(temp);
        std::getline(textFile, temp);
        questions[i].setWrongAnswer1(temp);
        std::getline(textFile, temp);
        questions[i].setWrongAnswer2(temp);
        std::getline(textFile, temp);
        questions[i].setWrongAnswer3(temp);*/
    }
    
    return true;
}

void printQuestion(QandA& q)
{
    cout << q.getQuestion() << endl;
    for (int i = 0; i < 4; i++)
        cout << q.getAnswer(i) << endl;
}

cv8_milionar::cv8_milionar(QWidget *parent) : QMainWindow(parent) // co sa stane po spusteni
{
    ui.setupUi(this);

    // nacitanie otazok z "_otazky.txt"
    if (loadQuestions("_otazky.txt") == false)
        cout << "Otazky sa nenacitali" << endl;
    else
        cout << "Otazky uspesne nacitane" << endl;

    // deaktivacia buttonov a groupBoxov, ktore sa nebudu dat stlacit, kym sa nezacne hra
    ui.pushButtonEndGame->setEnabled(false); // Ukoncit hru
    ui.pushButtonAccept->setEnabled(false); // Potvrdit
    ui.pushButtonSkip->setEnabled(false); // Preskocit otazku
    ui.groupBoxZoliky->setEnabled(false); // groupBox so zolikmi
    ui.groupBoxQuestion->setEnabled(false); // groupBox s otazkou
    ui.groupBoxChoices->setEnabled(false); // groupBox s moznostami
    ui.groupBoxBottom->setEnabled(false); // posledny groupBox

    for (int i = 0; i < numOfQuestions; i++)
        printQuestion(questions[i]);
}

void cv8_milionar::on_pushButtonNewGame_clicked() // button Nova hra
{
    if (ui.lineEditName->text() != "") // pokial nie je zadane meno hraca, tak sa hra nepusti
    {
        player.setPlayerScore(0.0); // nastavenie score hraca
        player.setPlayerName(ui.lineEditName->text()); // nastavenie mena hraca
        questionNum = 0;

        if (ui.difficulty->currentIndex() == 0)
        {
            ui.pushButtonZolik2->setVisible(true);
            ui.pushButtonZolik3->setVisible(true);
        }
        else if (ui.difficulty->currentIndex() == 1) // ak je zvolena stredna obtiaznost
        {
            ui.pushButtonZolik3->setVisible(false);
        }
        else if (ui.difficulty->currentIndex() == 2) // ak je zvolena tazka obtiaznost
        {
            ui.pushButtonZolik2->setVisible(false);
            ui.pushButtonZolik3->setVisible(false);
        }

        if (ui.randomQuestions->isChecked())
            cout << "Nahodne poradie otazok" << endl;
        else
            cout << "Normalne poradie otazok" << endl;

        ui.pushButtonEndGame->setEnabled(true); // Ukoncit hru
        ui.pushButtonAccept->setEnabled(true); // Potvrdit
        ui.pushButtonSkip->setEnabled(true); // Preskocit otazku
        ui.groupBoxZoliky->setEnabled(true); // groupBox so zolikmi
        ui.groupBoxQuestion->setEnabled(true); // groupBox s otazkou
        ui.groupBoxChoices->setEnabled(true); // groupBox s moznostami
        ui.groupBoxBottom->setEnabled(true); // posledny groupBox
        ui.pushButtonNewGame->setEnabled(false); // Nova hra
        ui.randomQuestions->setEnabled(false); // checkBox Nahodne
        ui.difficulty->setEnabled(false); // vyber obtiaznosti
        ui.pushButtonZolik1->setEnabled(true); // zolik 1
        ui.pushButtonZolik2->setEnabled(true); // zolik 2
        ui.pushButtonZolik3->setEnabled(true); // zolik 3

        ui.lineEditName->setReadOnly(true); // zakazane menit meno pocas hry

        ui.scoreBox->setValue(player.getPlayerScore());
        
        ui.textEditQuestion->setText(QString::fromStdString(questions[questionNum].getQuestion()));

        /*ui.choiceA->setText(QString::fromStdString("A) " + otazky[otazkaNum].getCorrectAnswer()));
        ui.choiceB->setText(QString::fromStdString("B) " + otazky[otazkaNum].getWrongAnser1()));
        ui.choiceC->setText(QString::fromStdString("C) " + otazky[otazkaNum].getWrongAnser2()));
        ui.choiceD->setText(QString::fromStdString("D) " + otazky[otazkaNum].getWrongAnser3()));*/
        ui.choiceA->setText(QString::fromStdString("A) " + questions[questionNum].getCorrectAnswer()));
        ui.choiceB->setText(QString::fromStdString("B) " + questions[questionNum].getAnswer(1)));
        ui.choiceC->setText(QString::fromStdString("C) " + questions[questionNum].getAnswer(2)));
        ui.choiceD->setText(QString::fromStdString("D) " + questions[questionNum].getAnswer(3)));


    }

}

void cv8_milionar::on_pushButtonEndGame_clicked() // button Ukoncit hru
{
    cout << "Koniec hry" << endl;

    // odcitanie bodov za nezodpovedane otazky
    int temp = numOfQuestions - questionNum;
    player.setPlayerScore(player.getPlayerScore() - temp * 0.5);
    ui.scoreBox->setValue(player.getPlayerScore());

    ui.pushButtonEndGame->setEnabled(false); // Ukoncit hru
    ui.pushButtonAccept->setEnabled(false); // Potvrdit
    ui.pushButtonSkip->setEnabled(false); // Preskocit otazku
    ui.groupBoxZoliky->setEnabled(false); // groupBox so zolikmi
    ui.groupBoxQuestion->setEnabled(false); // groupBox s otazkou
    ui.groupBoxChoices->setEnabled(false); // groupBox s moznostami
    ui.groupBoxBottom->setEnabled(false); // posledny groupBox
    ui.randomQuestions->setEnabled(true);
    ui.difficulty->setEnabled(true);

    ui.pushButtonNewGame->setEnabled(true);

    ui.lineEditName->setReadOnly(false);
}

void cv8_milionar::on_pushButtonAccept_clicked() // button Potvrdit
{
    questionNum++;
    player.setPlayerScore(player.getPlayerScore() + 1.0);

    ui.scoreBox->setValue(player.getPlayerScore());

    if (questionNum == numOfQuestions)
        on_pushButtonEndGame_clicked();

    if (questionNum < numOfQuestions)
    {
        ui.textEditQuestion->setText(QString::fromStdString(questions[questionNum].getQuestion()));

        ui.choiceA->setText(QString::fromStdString("A) " + questions[questionNum].getCorrectAnswer()));
        ui.choiceB->setText(QString::fromStdString("B) " + questions[questionNum].getAnswer(1)));
        ui.choiceC->setText(QString::fromStdString("C) " + questions[questionNum].getAnswer(2)));
        ui.choiceD->setText(QString::fromStdString("D) " + questions[questionNum].getAnswer(3)));
    }
}

void cv8_milionar::on_pushButtonSkip_clicked() // button Preskocit otazku
{
    questionNum++;
    player.setPlayerScore(player.getPlayerScore() - 0.5);

    ui.scoreBox->setValue(player.getPlayerScore());

    if (questionNum == numOfQuestions)
        on_pushButtonEndGame_clicked();

    if (questionNum < numOfQuestions)
    {
        ui.textEditQuestion->setText(QString::fromStdString(questions[questionNum].getQuestion()));

        ui.choiceA->setText(QString::fromStdString("A) " + questions[questionNum].getCorrectAnswer()));
        ui.choiceB->setText(QString::fromStdString("B) " + questions[questionNum].getAnswer(1)));
        ui.choiceC->setText(QString::fromStdString("C) " + questions[questionNum].getAnswer(2)));
        ui.choiceD->setText(QString::fromStdString("D) " + questions[questionNum].getAnswer(3)));
    }
}

void cv8_milionar::on_pushButtonZolik1_clicked() // zolik 1
{
    cout << "Zolik 1" << endl;
    ui.pushButtonZolik1->setEnabled(false);
}

void cv8_milionar::on_pushButtonZolik2_clicked() // zolik 2
{
    cout << "Zolik 2" << endl;
    ui.pushButtonZolik2->setEnabled(false);
}

void cv8_milionar::on_pushButtonZolik3_clicked() // zolik 3
{
    cout << "Zolik 3" << endl;
    ui.pushButtonZolik3->setEnabled(false);
}