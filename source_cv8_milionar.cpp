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
    for (int i = 0; i < 4; i++)
    {
        if (!choice[i]->isChecked())
            continue;
        else
        {
            choice[i]->setAutoExclusive(false);
            choice[i]->setChecked(false);
            choice[i]->setAutoExclusive(true);
        }
    }
}

cv8_milionar::cv8_milionar(QWidget *parent) : QMainWindow(parent) // co sa stane po spusteni
{
    ui.setupUi(this);

    srand((unsigned)time(0));

    // nacitanie otazok z "_otazky.txt"
    if (loadQuestions("_otazky.txt") == false)
    {
        qDebug() << "Otazky sa nenacitali";
        exit(-1);
    }
    else
        qDebug() << "Otazky uspesne nacitane";

    // naplnenie vekotra smernikmi na jednotlive radioButtony -> funguje to iba, ak je to spravene takto
    choice.push_back(ui.choiceA);
    choice.push_back(ui.choiceB);
    choice.push_back(ui.choiceC);
    choice.push_back(ui.choiceD);

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

// Nova hra
void cv8_milionar::on_pushButtonNewGame_clicked()
{
    if (ui.lineEditName->text() != "") // pokial nie je zadane meno hraca, tak sa hra nepusti
    {
        player.setPlayerScore(0.0); // nastavenie score hraca na zaciatku hry
        player.setPlayerName(ui.lineEditName->text()); // nastavenie mena hraca
        questionNum = 0; // index pre poradie otazok

        // poskytnutie zolikov podla obtiaznosti
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

        // nahodne poradie otazok
        if (ui.randomQuestions->isChecked()) // ak je vybrane nahodne poradie otazok
            std::random_shuffle(std::begin(randNum), std::end(randNum)); // pomiesaju sa jednotlive indexi otazok
        else
            for (int i = 0; i < 10; i++) // inak pojdu pekne od prvej po poslednu
                randNum[i] = i;

        // nastavenie Enabled pre jednotlive prvky
        ui.pushButtonEndGame->setEnabled(true); // Ukoncit hru
        ui.pushButtonAccept->setEnabled(true); // Potvrdit
        ui.pushButtonSkip->setEnabled(true); // Preskocit otazku
        ui.groupBoxZoliky->setEnabled(true); // groupBox so zolikmi
        ui.groupBoxQuestion->setEnabled(true); // groupBox s otazkou
        ui.groupBoxChoices->setEnabled(true); // groupBox s moznostami
        ui.groupBoxBottom->setEnabled(true); // posledny groupBox
        ui.pushButtonNewGame->setEnabled(false); // Nova hra
        ui.randomQuestions->setEnabled(false); // checkBox Nahodne
        ui.uncheckChoices->setEnabled(false); // checkBox Odznacovat odpovede
        ui.difficulty->setEnabled(false); // vyber obtiaznosti
        ui.pushButtonZolik1->setEnabled(true); // zolik 1
        ui.pushButtonZolik2->setEnabled(true); // zolik 2
        ui.pushButtonZolik3->setEnabled(true); // zolik 3

        // player stuff
        ui.lineEditName->setReadOnly(true); // zakazane menit meno pocas hry
        ui.scoreBox->setValue(player.getPlayerScore());

        for (int i = 0; i < 4; i++)
            choice[i]->setEnabled(true);
        
        ui.textEditQuestion->setText(QString::fromStdString(questions[randNum[questionNum]].getQuestion())); // vypisanie prvej otazky, ked sa zacne hra

        if (ui.uncheckChoices->isChecked())
            uncheckChoices();

        questions[randNum[questionNum]].shuffleAnswers(); // pomiesanie odpovedi na danu otazku

        ui.choiceA->setText(QString::fromStdString("A) " + questions[randNum[questionNum]].getAnswer(0)));
        ui.choiceB->setText(QString::fromStdString("B) " + questions[randNum[questionNum]].getAnswer(1)));
        ui.choiceC->setText(QString::fromStdString("C) " + questions[randNum[questionNum]].getAnswer(2)));
        ui.choiceD->setText(QString::fromStdString("D) " + questions[randNum[questionNum]].getAnswer(3)));

        ui.pushButtonAccept->setEnabled(false);
    }
}

// Ukoncit hru
void cv8_milionar::on_pushButtonEndGame_clicked()
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
    ui.uncheckChoices->setEnabled(true);

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

// button Potvrdit
void cv8_milionar::on_pushButtonAccept_clicked()
{
    // vybranie odpovede
    for (int i = 0; i < 4; i++)
    {
        if (choice[i]->isChecked())
        {
            chosenAnswer = questions[randNum[questionNum]].getAnswer(i);
            qDebug() << "Vybrane: " << QString::fromStdString(chosenAnswer);
            break;
        }
    }
    
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
        for (int i = 0; i < 4; i++)
        {
            if (!choice[i]->isEnabled())
                choice[i]->setEnabled(true);
            else
                continue;
        }
        
        ui.textEditQuestion->setText(QString::fromStdString(questions[randNum[questionNum]].getQuestion()));

        if (ui.uncheckChoices->isChecked())
            uncheckChoices();

        questions[randNum[questionNum]].shuffleAnswers(); // pomiesanie odpovedi

        ui.choiceA->setText(QString::fromStdString("A) " + questions[randNum[questionNum]].getAnswer(0)));
        ui.choiceB->setText(QString::fromStdString("B) " + questions[randNum[questionNum]].getAnswer(1)));
        ui.choiceC->setText(QString::fromStdString("C) " + questions[randNum[questionNum]].getAnswer(2)));
        ui.choiceD->setText(QString::fromStdString("D) " + questions[randNum[questionNum]].getAnswer(3)));

        if (ui.uncheckChoices->isChecked())
            ui.pushButtonAccept->setEnabled(false);
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
        for (int i = 0; i < 4; i++)
        {
            if (!choice[i]->isEnabled())
                choice[i]->setEnabled(true);
            else
                continue;
        }

        ui.textEditQuestion->setText(QString::fromStdString(questions[randNum[questionNum]].getQuestion()));

        if (ui.uncheckChoices->isChecked())
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
    ui.pushButtonZolik1->setEnabled(false);

    int temp = 0;
    int tempWrong[2] = { -1,-1 };
    
    for (int i = 0; i < 4; i++)
    {
        if (choice[i]->isEnabled())
        {
            //qDebug() << i << " is enabled";
            if (questions[randNum[questionNum]].getAnswer(i) != questions[randNum[questionNum]].getCorrectAnswer())
            {
                //qDebug() << "temp pred: " << temp;
                tempWrong[temp] = i;
                temp++;
                //qDebug() << "temp po: " << temp;
            }
        }

        if (temp == 2)
            break;
    }

    for (int i = 0; i < 2; i++)
    {
        if (tempWrong[i] == 0)
            choice[0]->setEnabled(false);
        else if (tempWrong[i] == 1)
            choice[1]->setEnabled(false);
        else if (tempWrong[i] == 2)
            choice[2]->setEnabled(false);
        else if (tempWrong[i] == 3)
            choice[3]->setEnabled(false);
    }

}

void cv8_milionar::on_pushButtonZolik2_clicked() // zolik 2
{
    ui.pushButtonZolik2->setEnabled(false);

    int temp = 0;
    int tempWrong[2] = { -1,-1 };

    for (int i = 0; i < 4; i++)
    {
        if (choice[i]->isEnabled())
        {
            //qDebug() << i << " is enabled";
            if (questions[randNum[questionNum]].getAnswer(i) != questions[randNum[questionNum]].getCorrectAnswer())
            {
                //qDebug() << "temp pred: " << temp;
                tempWrong[temp] = i;
                temp++;
                //qDebug() << "temp po: " << temp;
            }
        }

        if (temp == 2)
            break;
    }

    for (int i = 0; i < 2; i++)
    {
        if (tempWrong[i] == 0)
            choice[0]->setEnabled(false);
        else if (tempWrong[i] == 1)
            choice[1]->setEnabled(false);
        else if (tempWrong[i] == 2)
            choice[2]->setEnabled(false);
        else if (tempWrong[i] == 3)
            choice[3]->setEnabled(false);
    }
}

void cv8_milionar::on_pushButtonZolik3_clicked() // zolik 3
{
    ui.pushButtonZolik3->setEnabled(false);

    int temp = 0;
    int tempWrong[2] = { -1,-1 };

    for (int i = 0; i < 4; i++)
    {
        if (choice[i]->isEnabled())
        {
            //qDebug() << i << " is enabled";
            if (questions[randNum[questionNum]].getAnswer(i) != questions[randNum[questionNum]].getCorrectAnswer())
            {
                //qDebug() << "temp pred: " << temp;
                tempWrong[temp] = i;
                temp++;
                //qDebug() << "temp po: " << temp;
            }
        }

        if (temp == 2)
            break;
    }

    for (int i = 0; i < 2; i++)
    {
        if (tempWrong[i] == 0)
            choice[0]->setEnabled(false);
        else if (tempWrong[i] == 1)
            choice[1]->setEnabled(false);
        else if (tempWrong[i] == 2)
            choice[2]->setEnabled(false);
        else if (tempWrong[i] == 3)
            choice[3]->setEnabled(false);
    }
}

//########## JEDNOTLIVE MOZNOSTI ##########//

void cv8_milionar::on_choiceA_clicked()
{
    if (!ui.pushButtonAccept->isEnabled())
        ui.pushButtonAccept->setEnabled(true);
}

void cv8_milionar::on_choiceB_clicked()
{
    if (!ui.pushButtonAccept->isEnabled())
        ui.pushButtonAccept->setEnabled(true);
}

void cv8_milionar::on_choiceC_clicked()
{
    if (!ui.pushButtonAccept->isEnabled())
        ui.pushButtonAccept->setEnabled(true);
}

void cv8_milionar::on_choiceD_clicked()
{
    if (!ui.pushButtonAccept->isEnabled())
        ui.pushButtonAccept->setEnabled(true);
}