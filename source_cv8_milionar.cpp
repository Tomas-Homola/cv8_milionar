#include "cv8_milionar.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <cstdlib>

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

    /*for (int i = 0; i < numOfQuestions; i++)
        printQuestion(questions[i]);*/
}

void cv8_milionar::on_pushButtonNewGame_clicked() // button Nova hra
{
    if (ui.lineEditName->text() != "") // pokial nie je zadane meno hraca, tak sa hra nepusti
    {
        player.setPlayerScore(0.0); // nastavenie score hraca na zaciatku hry
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
            std::random_shuffle(std::begin(randNum), std::end(randNum)); // pomiesanie poradia otazok
        else
            for (int i = 0; i < 10; i++)
                randNum[i] = i;

        ui.pushButtonEndGame->setEnabled(true); // Ukoncit hru
        ui.pushButtonAccept->setEnabled(true); // Potvrdit
        ui.pushButtonSkip->setEnabled(true); // Preskocit otazku
        ui.groupBoxZoliky->setEnabled(true); // groupBox so zolikmi
        ui.groupBoxQuestion->setEnabled(true); // groupBox s otazkou
        ui.groupBoxQuestion->setTitle("Otazka");
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

        questions[randNum[questionNum]].shuffleAnswers();

        ui.choiceA->setText(QString::fromStdString("A) " + questions[randNum[questionNum]].getAnswer(0)));
        ui.choiceB->setText(QString::fromStdString("B) " + questions[randNum[questionNum]].getAnswer(1)));
        ui.choiceC->setText(QString::fromStdString("C) " + questions[randNum[questionNum]].getAnswer(2)));
        ui.choiceD->setText(QString::fromStdString("D) " + questions[randNum[questionNum]].getAnswer(3)));
    }
}

void cv8_milionar::on_pushButtonEndGame_clicked() // button Ukoncit hru
{
    cout << "Koniec hry" << endl;

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
    ui.randomQuestions->setEnabled(true);
    ui.difficulty->setEnabled(true);

    // k tomuto su headers <sstream> a <iomanip> -> aby sa vypisali body iba s max jednym desatinnym cislom
    std::ostringstream tempStream;
    tempStream << std::setprecision(2);
    tempStream << player.getPlayerScore();

    // vyhodnotenie
    ui.groupBoxQuestion->setTitle("Vyhodnotenie");
    ui.textEditQuestion->setText(QString("Koniec hry\nPocet ziskanych bodov: " + QString::fromStdString(tempStream.str())).toUtf8());

    ui.pushButtonNewGame->setEnabled(true);

    ui.lineEditName->setReadOnly(false);
}

void cv8_milionar::on_pushButtonAccept_clicked() // button Potvrdit
{
    cout << "2 chosen: " << chosenAnswer << endl << "correct answer: " << questions[randNum[questionNum]].getCorrectAnswer() << endl;

    if (chosenAnswer == questions[randNum[questionNum]].getCorrectAnswer())
    {
        cout << "Correct" << endl;
        player.setPlayerScore(player.getPlayerScore() + 1.0);
        ui.scoreBox->setValue(player.getPlayerScore());
    }
    else
    {
        cout << "Incorrect" << endl;
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

        questions[randNum[questionNum]].shuffleAnswers();

        ui.choiceA->setText(QString::fromStdString("A) " + questions[randNum[questionNum]].getAnswer(0)));
        ui.choiceB->setText(QString::fromStdString("B) " + questions[randNum[questionNum]].getAnswer(1)));
        ui.choiceC->setText(QString::fromStdString("C) " + questions[randNum[questionNum]].getAnswer(2)));
        ui.choiceD->setText(QString::fromStdString("D) " + questions[randNum[questionNum]].getAnswer(3)));

        ui.choiceA->setChecked(false);
        ui.choiceB->setChecked(false);
        ui.choiceC->setChecked(false);
        ui.choiceD->setChecked(false);
    }
}

void cv8_milionar::on_pushButtonSkip_clicked() // button Preskocit otazku
{
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

        questions[randNum[questionNum]].shuffleAnswers();

        ui.choiceA->setText(QString::fromStdString("A) " + questions[randNum[questionNum]].getAnswer(0)));
        ui.choiceB->setText(QString::fromStdString("B) " + questions[randNum[questionNum]].getAnswer(1)));
        ui.choiceC->setText(QString::fromStdString("C) " + questions[randNum[questionNum]].getAnswer(2)));
        ui.choiceD->setText(QString::fromStdString("D) " + questions[randNum[questionNum]].getAnswer(3)));

        ui.choiceA->setChecked(false);
        ui.choiceB->setChecked(false);
        ui.choiceC->setChecked(false);
        ui.choiceD->setChecked(false);
    }
}

//########## ZOLIKY ##########//

void cv8_milionar::on_pushButtonZolik1_clicked() // zolik 1
{
    int temp = 0;
    int tempWrong[2] = { -1,-1 };

    cout << "Zolik 1 used" << endl;
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

    cout << "Zolik 2 used" << endl;
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

    cout << "Zolik 3 used" << endl;
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
    
    cout << "chosen: " << chosenAnswer << endl;
}

void cv8_milionar::on_choiceB_clicked()
{
    chosenAnswer = questions[randNum[questionNum]].getAnswer(1);

    cout << "chosen: " << chosenAnswer << endl;
}

void cv8_milionar::on_choiceC_clicked()
{
    chosenAnswer = questions[randNum[questionNum]].getAnswer(2);

    cout << "chosen: " << chosenAnswer << endl;
}

void cv8_milionar::on_choiceD_clicked()
{
    chosenAnswer = questions[randNum[questionNum]].getAnswer(3);

    cout << "chosen: " << chosenAnswer << endl;
}