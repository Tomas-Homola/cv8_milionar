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
    pocetOtazok = std::stoi(temp);

    for (int i = 0; i < pocetOtazok; i++)
    {
        std::getline(textFile, temp); // precitanie otazky
        otazky[i].setQestion(temp); // nastavenie otazky
        
        // precitanie a nastavenie odpovedi
        std::getline(textFile, temp);
        otazky[i].setCorrectAnswer(temp);
        std::getline(textFile, temp);
        otazky[i].setWrongAnswer1(temp);
        std::getline(textFile, temp);
        otazky[i].setWrongAnswer2(temp);
        std::getline(textFile, temp);
        otazky[i].setWrongAnswer3(temp);
    }
    
    return true;
}

void printQ(QandA& q)
{
    cout << q.getQuestion() << endl << q.getCorrectAnswer() << endl << q.getWrongAnser1() << endl << q.getWrongAnser2() << endl << q.getWrongAnser3() << endl;
}

cv8_milionar::cv8_milionar(QWidget *parent) : QMainWindow(parent)
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

    /*for (int i = 0; i < pocetOtazok; i++)
        printQ(otazky[i]);*/
}

void cv8_milionar::on_pushButtonNewGame_clicked() // button Nova hra
{
    if (ui.lineEditName->text() != "")
    {
        body = 0.0;
        otazkaNum = 0;

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

        ui.scoreBox->setValue(body);
        
        ui.textEditQuestion->setText(QString::fromStdString(otazky[otazkaNum].getQuestion()));
        ui.choiceA->setText(QString::fromStdString("A) " + otazky[otazkaNum].getCorrectAnswer()));
        ui.choiceB->setText(QString::fromStdString("B) " + otazky[otazkaNum].getWrongAnser1()));
        ui.choiceC->setText(QString::fromStdString("C) " + otazky[otazkaNum].getWrongAnser2()));
        ui.choiceD->setText(QString::fromStdString("D) " + otazky[otazkaNum].getWrongAnser3()));

    }

}

void cv8_milionar::on_pushButtonEndGame_clicked() // button Ukoncit hru
{
    cout << "Koniec hry" << endl;

    // odcitanie bodov za nezodpovedane otazky
    int temp = pocetOtazok - otazkaNum;
    body -= temp * 0.5;
    ui.scoreBox->setValue(body);

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
    otazkaNum++;
    body += 1.0;

    ui.scoreBox->setValue(body);

    if (otazkaNum == pocetOtazok)
        on_pushButtonEndGame_clicked();

    if (otazkaNum < pocetOtazok)
    {
        ui.textEditQuestion->setText(QString::fromStdString(otazky[otazkaNum].getQuestion()));

        ui.choiceA->setText(QString::fromStdString("A) " + otazky[otazkaNum].getCorrectAnswer()));
        ui.choiceB->setText(QString::fromStdString("B) " + otazky[otazkaNum].getWrongAnser1()));
        ui.choiceC->setText(QString::fromStdString("C) " + otazky[otazkaNum].getWrongAnser2()));
        ui.choiceD->setText(QString::fromStdString("D) " + otazky[otazkaNum].getWrongAnser3()));
    }
}

void cv8_milionar::on_pushButtonSkip_clicked() // button Preskocit otazku
{
    otazkaNum++;
    body -= 0.5;

    ui.scoreBox->setValue(body);

    if (otazkaNum == pocetOtazok)
        on_pushButtonEndGame_clicked();

    if (otazkaNum < pocetOtazok)
    {
        ui.textEditQuestion->setText(QString::fromStdString(otazky[otazkaNum].getQuestion()));

        ui.choiceA->setText(QString::fromStdString("A) " + otazky[otazkaNum].getCorrectAnswer()));
        ui.choiceB->setText(QString::fromStdString("B) " + otazky[otazkaNum].getWrongAnser1()));
        ui.choiceC->setText(QString::fromStdString("C) " + otazky[otazkaNum].getWrongAnser2()));
        ui.choiceD->setText(QString::fromStdString("D) " + otazky[otazkaNum].getWrongAnser3()));
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