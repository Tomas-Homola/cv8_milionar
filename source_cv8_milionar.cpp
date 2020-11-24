#include "cv8_milionar.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <QDebug>

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
            std::getline(textFile, temp); // precita odpoved
            questions[i].setAnswer(j, temp); // zapise odpoved
        }

        questions[i].setCorrectAnswer(questions[i].getAnswer(0)); // zapise spravnu odpoved
    }
    
    textFile.close();
    return true;
}

void cv8_milionar::printQuestion(QandA& q)
{
    cout << q.getQuestion() << endl;
    for (int i = 0; i < 4; i++)
        cout << q.getAnswer(i) << endl;
}

void cv8_milionar::uncheckChoices()
{
    //qDebug() << "kontrola isChecked";
    if (ui.choiceA->isChecked())
    {
        ui.choiceA->setAutoExclusive(false);
        ui.choiceA->setChecked(false);
        ui.choiceA->setAutoExclusive(true);
        qDebug() << "A unchecked";
    }
    
    if (ui.choiceB->isChecked())
    {
        ui.choiceB->setAutoExclusive(false);
        ui.choiceB->setChecked(false);
        ui.choiceB->setAutoExclusive(true);
        qDebug() << "B unchecked";
    }

    if (ui.choiceC->isChecked())
    {
        ui.choiceC->setAutoExclusive(false);
        ui.choiceC->setChecked(false);
        ui.choiceC->setAutoExclusive(true);
        qDebug() << "C unchecked";
    }

    if (ui.choiceD->isChecked())
    {
        ui.choiceD->setAutoExclusive(false);
        ui.choiceD->setChecked(false);
        ui.choiceD->setAutoExclusive(true);
        qDebug() << "D unchecked";
    }
}

cv8_milionar::cv8_milionar(QWidget *parent) : QMainWindow(parent) // co sa stane po spusteni
{
    ui.setupUi(this);

    // nacitanie otazok z "_otazky.txt"
    if (loadQuestions("_otazky.txt") == false)
        qDebug() << "Otazky sa nenacitali";
    else
        qDebug() << "Otazky uspesne nacitane";

    // deaktivacia buttonov a groupBoxov, ktore sa nebudu dat stlacit, kym sa nezacne hra
    ui.pushButtonEndGame->setEnabled(false); // Ukoncit hru
    ui.pushButtonAccept->setEnabled(false); // Potvrdit
    ui.pushButtonSkip->setEnabled(false); // Preskocit otazku
    ui.groupBoxZoliky->setEnabled(false); // groupBox so zolikmi
    ui.groupBoxQuestion->setEnabled(false); // groupBox s otazkou
    ui.groupBoxChoices->setEnabled(false); // groupBox s moznostami
    ui.groupBoxBottom->setEnabled(false); // posledny groupBox
    msgBox.setWindowTitle(" ");
    qDebug() << "hra nacitana";

    /*for (int i = 0; i < numOfQuestions; i++)
        printQuestion(questions[i]);*/
}

void cv8_milionar::on_pushButtonNewGame_clicked() // button Nova hra
{
    if (ui.lineEditName->text() != "") // pokial nie je zadane meno hraca, tak sa hra nepusti
    {
        player.setPlayerScore(0.0); // nastavenie score hraca na zaciatku hry
        player.setPlayerName(ui.lineEditName->text()); // nastavenie mena hraca
        questionNum = 0; // index pre poradie otazok

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

        if (ui.randomQuestions->isChecked()) // ak je vybrane nahodne poradie otazok
            std::random_shuffle(std::begin(randNum), std::end(randNum)); // pomiesaju sa jednotlive indexi otazok
        else
            for (int i = 0; i < 10; i++) // inak pojdu pekne od prvej po poslednu
                randNum[i] = i;

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
        
        ui.textEditQuestion->setText(QString::fromStdString(questions[randNum[questionNum]].getQuestion())); // vypisanie prvej otazky, ked sa zacne hra

        uncheckChoices();

        questions[randNum[questionNum]].shuffleAnswers(); // pomiesanie odpovedi na danu otazku

        ui.choiceA->setText(QString::fromStdString("A) " + questions[randNum[questionNum]].getAnswer(0)));
        ui.choiceB->setText(QString::fromStdString("B) " + questions[randNum[questionNum]].getAnswer(1)));
        ui.choiceC->setText(QString::fromStdString("C) " + questions[randNum[questionNum]].getAnswer(2)));
        ui.choiceD->setText(QString::fromStdString("D) " + questions[randNum[questionNum]].getAnswer(3)));
    }
}

void cv8_milionar::on_pushButtonEndGame_clicked() // button Ukoncit hru
{
    // odcitanie bodov za nezodpovedane otazky
    int temp = numOfQuestions - questionNum;

    player.setPlayerScore(player.getPlayerScore() - temp * 0.5);

    if (player.getPlayerScore() < 0) // aby bol najmensi mozny pocet bodov 0
        player.setPlayerScore(0.0);

    ui.scoreBox->setValue(player.getPlayerScore());

    // znefunkcnenie tlacitok na konci hry
    ui.pushButtonEndGame->setEnabled(false); // Ukoncit hru
    ui.pushButtonAccept->setEnabled(false); // Potvrdit
    ui.pushButtonSkip->setEnabled(false); // Preskocit otazku
    ui.groupBoxZoliky->setEnabled(false); // groupBox so zolikmi
    ui.groupBoxChoices->setEnabled(false); // groupBox s moznostami
    ui.groupBoxBottom->setEnabled(false); // posledny groupBox
    ui.randomQuestions->setEnabled(true); // nahodne poradie otazok
    ui.difficulty->setEnabled(true); // vyber obtiaznosti

    // pri radioButtonoch nebudu uz vypisane posledne mozne odpovede a ani otazka
    ui.choiceA->setText("");
    ui.choiceB->setText("");
    ui.choiceC->setText("");
    ui.choiceD->setText("");
    ui.textEditQuestion->setText("");

    // k tomuto su headers <sstream> a <iomanip> -> aby sa vypisali body iba s max jednym desatinnym cislom
    std::ostringstream tempStream;
    tempStream << std::setprecision(2);
    tempStream << player.getPlayerScore();

    // vyhodnotenie
    msgBox.setWindowTitle("Vyhodnotenie");
    msgBox.setText(QString(u8"Koniec hry\nPočet získaných bodov: " + QString::fromStdString(tempStream.str())));
    msgBox.exec();

    ui.pushButtonNewGame->setEnabled(true);

    ui.lineEditName->setReadOnly(false);
}

void cv8_milionar::on_pushButtonAccept_clicked() // button Potvrdit
{
    if (chosenAnswer == questions[randNum[questionNum]].getCorrectAnswer()) // ak je zadana spravna odpoved
    {
        msgBox.setText(u8"Správna odpoveď, +1 bod"); // vypisanie spravy o spravnosti odpovede
        msgBox.exec();

        player.setPlayerScore(player.getPlayerScore() + 1.0);
        ui.scoreBox->setValue(player.getPlayerScore());
    }
    else // ak nie je zadana spravna odpoved
    {
        msgBox.setText(u8"Nesprávna odpoveď, -1 bod"); // vypisanie spravy o spravnosti odpovede
        msgBox.exec();

        player.setPlayerScore(player.getPlayerScore() - 1.0);
        if (player.getPlayerScore() < 0) // aby bol najmensi mozny pocet bodov 0
            player.setPlayerScore(0.0);
        ui.scoreBox->setValue(player.getPlayerScore());
    }

    questionNum++;

    if (questionNum == numOfQuestions)
        on_pushButtonEndGame_clicked();

    if (questionNum < numOfQuestions)
    {
        ui.choiceA->setEnabled(true);
        ui.choiceB->setEnabled(true);
        ui.choiceC->setEnabled(true);
        ui.choiceD->setEnabled(true);
        
        ui.textEditQuestion->setText(QString::fromStdString(questions[randNum[questionNum]].getQuestion()));

        uncheckChoices();

        questions[randNum[questionNum]].shuffleAnswers(); // pomiesanie odpovedi

        ui.choiceA->setText(QString::fromStdString("A) " + questions[randNum[questionNum]].getAnswer(0)));
        ui.choiceB->setText(QString::fromStdString("B) " + questions[randNum[questionNum]].getAnswer(1)));
        ui.choiceC->setText(QString::fromStdString("C) " + questions[randNum[questionNum]].getAnswer(2)));
        ui.choiceD->setText(QString::fromStdString("D) " + questions[randNum[questionNum]].getAnswer(3)));
    }
}

void cv8_milionar::on_pushButtonSkip_clicked() // button Preskocit otazku
{
    // vypisanie
    msgBox.setText(u8"Otázka nezodpovedaná, -0.5 boda");
    msgBox.exec();
    
    player.setPlayerScore(player.getPlayerScore() - 0.5);
    if (player.getPlayerScore() < 0) // aby bol najmensi mozny pocet bodov 0
        player.setPlayerScore(0.0);
    ui.scoreBox->setValue(player.getPlayerScore());

    questionNum++;

    if (questionNum == numOfQuestions)
        on_pushButtonEndGame_clicked();

    if (questionNum < numOfQuestions)
    {
        ui.choiceA->setEnabled(true);
        ui.choiceB->setEnabled(true);
        ui.choiceC->setEnabled(true);
        ui.choiceD->setEnabled(true);
        
        ui.textEditQuestion->setText(QString::fromStdString(questions[randNum[questionNum]].getQuestion()));

        uncheckChoices();

        questions[randNum[questionNum]].shuffleAnswers(); // pomiesanie odpovedi

        ui.choiceA->setText(QString::fromStdString("A) " + questions[randNum[questionNum]].getAnswer(0)));
        ui.choiceB->setText(QString::fromStdString("B) " + questions[randNum[questionNum]].getAnswer(1)));
        ui.choiceC->setText(QString::fromStdString("C) " + questions[randNum[questionNum]].getAnswer(2)));
        ui.choiceD->setText(QString::fromStdString("D) " + questions[randNum[questionNum]].getAnswer(3)));
    }
}

//########## ZOLIKY ##########//

void cv8_milionar::on_pushButtonZolik1_clicked() // zolik 1
{
    int temp = 0;
    int tempWrong[2] = { -1,-1 };

    ui.pushButtonZolik1->setEnabled(false);

    for (int i = (questionNum % 2); i < (3 + questionNum % 2); i++)
    {
        if (questions[randNum[questionNum]].getAnswer(i) != questions[randNum[questionNum]].getCorrectAnswer())
        {
            tempWrong[temp] = i;
            temp++;
        }
        
        if (temp == 2)
            break;
    }

    for (int i = 0; i < 2; i++)
    {
        if (tempWrong[i] == 0)
            ui.choiceA->setEnabled(false);
        else if (tempWrong[i] == 1)
            ui.choiceB->setEnabled(false);
        else if (tempWrong[i] == 2)
            ui.choiceC->setEnabled(false);
        else if (tempWrong[i] == 3)
            ui.choiceD->setEnabled(false);
    }
}

void cv8_milionar::on_pushButtonZolik2_clicked() // zolik 2
{
    int temp = 0;
    int tempWrong[2] = { -1,-1 };

    ui.pushButtonZolik2->setEnabled(false);

    for (int i = (questionNum % 2); i < (3 + questionNum % 2); i++)
    {
        if (questions[randNum[questionNum]].getAnswer(i) != questions[randNum[questionNum]].getCorrectAnswer())
        {
            tempWrong[temp] = i;
            temp++;
        }

        if (temp == 2)
            break;
    }

    for (int i = 0; i < 2; i++)
    {
        if (tempWrong[i] == 0)
            ui.choiceA->setEnabled(false);
        else if (tempWrong[i] == 1)
            ui.choiceB->setEnabled(false);
        else if (tempWrong[i] == 2)
            ui.choiceC->setEnabled(false);
        else if (tempWrong[i] == 3)
            ui.choiceD->setEnabled(false);
    }
}

void cv8_milionar::on_pushButtonZolik3_clicked() // zolik 3
{
    int temp = 0;
    int tempWrong[2] = { -1,-1 };

    ui.pushButtonZolik3->setEnabled(false);

    for (int i = (questionNum % 2); i < (3 + questionNum % 2); i++)
    {
        if (questions[randNum[questionNum]].getAnswer(i) != questions[randNum[questionNum]].getCorrectAnswer())
        {
            tempWrong[temp] = i;
            temp++;
        }

        if (temp == 2)
            break;
    }

    for (int i = 0; i < 2; i++)
    {
        if (tempWrong[i] == 0)
            ui.choiceA->setEnabled(false);
        else if (tempWrong[i] == 1)
            ui.choiceB->setEnabled(false);
        else if (tempWrong[i] == 2)
            ui.choiceC->setEnabled(false);
        else if (tempWrong[i] == 3)
            ui.choiceD->setEnabled(false);
    }
}

//########## JEDNOTLIVE MOZNOSTI ##########//

void cv8_milionar::on_choiceA_clicked()
{
    chosenAnswer = questions[randNum[questionNum]].getAnswer(0);
}

void cv8_milionar::on_choiceB_clicked()
{
    chosenAnswer = questions[randNum[questionNum]].getAnswer(1);
}

void cv8_milionar::on_choiceC_clicked()
{
    chosenAnswer = questions[randNum[questionNum]].getAnswer(2);
}

void cv8_milionar::on_choiceD_clicked()
{
    chosenAnswer = questions[randNum[questionNum]].getAnswer(3);
}