#include "cv8_milionar.h"
#include <iostream>
#include <string>
#include <fstream>

using std::cout;
using std::endl;

bool cv8_milionar::loadQuestions(std::string fileName)
{
    std::string temp;
    std::fstream textFile;
    textFile.open(fileName, std::ios::in);

    if (textFile.is_open() == false)
        return false;

    textFile >> pocetOtazok;

    for (int i = 0; i < pocetOtazok; i++)
    {
        std::getline(textFile, temp); // precitanie otazky
        otazky[i].setQestion(temp); // nastavenie otazky
        
        // precitanie a nastavenie odpovedi
        textFile >> temp; 
        otazky[i].setCorrectAnswer(temp);
        textFile >> temp;
        otazky[i].setWrongAnswer1(temp);
        textFile >> temp;
        otazky[i].setWrongAnswer2(temp);
        textFile >> temp;
        otazky[i].setWrongAnswer3(temp);
    }
    
    return true;
}

cv8_milionar::cv8_milionar(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);

    // deaktivacia buttonov a groupBoxov, ktore sa nebudu dat stlacit, kym sa nezacne hra
    ui.pushButtonEndGame->setEnabled(false); // Ukoncit hru
    ui.pushButtonAccept->setEnabled(false); // Potvrdit
    ui.pushButtonSkip->setEnabled(false); // Preskocit otazku
    ui.groupBoxZoliky->setEnabled(false); // groupBox so zolikmi
    ui.groupBoxQuestion->setEnabled(false); // groupBox s otazkou
    ui.groupBoxChoices->setEnabled(false); // groupBox s moznostami
    ui.groupBoxBottom->setEnabled(false); // posledny groupBox
}

void cv8_milionar::on_pushButtonNewGame_clicked() // button Nova hra
{
    if (ui.lineEditName->text() != "")
    {
        game_on = true;
        body = 0.0;
        otazkaNum = 1;

        ui.pushButtonEndGame->setEnabled(true); // Ukoncit hru
        ui.pushButtonAccept->setEnabled(true); // Potvrdit
        ui.pushButtonSkip->setEnabled(true); // Preskocit otazku
        ui.groupBoxZoliky->setEnabled(true); // groupBox so zolikmi
        ui.groupBoxQuestion->setEnabled(true); // groupBox s otazkou
        ui.groupBoxChoices->setEnabled(true); // groupBox s moznostami
        ui.groupBoxBottom->setEnabled(true); // posledny groupBox
        ui.pushButtonNewGame->setEnabled(false); // Nova hra
        ui.checkBoxRandomQuestion->setEnabled(false); // checkBox Nahodne
        ui.comboBoxDifficulty->setEnabled(false); // vyber obtiaznosti

        ui.lineEditName->setReadOnly(true);

        ui.doubleSpinBoxScore->setValue(body);
        
        ui.textEditQuestion->setText(QString("Otazka 1) bla bla bla?"));
    }

}

void cv8_milionar::on_pushButtonEndGame_clicked() // button Ukoncit hru
{
    cout << "Koniec hry" << endl;

    ui.pushButtonEndGame->setEnabled(false); // Ukoncit hru
    ui.pushButtonAccept->setEnabled(false); // Potvrdit
    ui.pushButtonSkip->setEnabled(false); // Preskocit otazku
    ui.groupBoxZoliky->setEnabled(false); // groupBox so zolikmi
    ui.groupBoxQuestion->setEnabled(false); // groupBox s otazkou
    ui.groupBoxChoices->setEnabled(false); // groupBox s moznostami
    ui.groupBoxBottom->setEnabled(false); // posledny groupBox
    ui.checkBoxRandomQuestion->setEnabled(true);
    ui.comboBoxDifficulty->setEnabled(true);

    ui.pushButtonNewGame->setEnabled(true);

    ui.lineEditName->setReadOnly(false);
}

void cv8_milionar::on_pushButtonAccept_clicked() // button Potvrdit
{
    otazkaNum++;
    cout << "Otazka " << otazkaNum << ") bla bla bla?" << endl;
    body += 1.0;

    ui.doubleSpinBoxScore->setValue(body);
}

void cv8_milionar::on_pushButtonSkip_clicked() // button Preskocit otazku
{
    otazkaNum++;
    cout << "Otazka " << otazkaNum << ") bla bla bla?" << endl;
    body -= 0.5;

    ui.doubleSpinBoxScore->setValue(body);
}

void cv8_milionar::on_pushButtonZolik1_clicked() // zolik 1
{
    cout << "Zolik 1" << endl;
}

void cv8_milionar::on_pushButtonZolik2_clicked() // zolik 2
{
    cout << "Zolik 2" << endl;
}

void cv8_milionar::on_pushButtonZolik3_clicked() // zolik 3
{
    cout << "Zolik 3" << endl;
}