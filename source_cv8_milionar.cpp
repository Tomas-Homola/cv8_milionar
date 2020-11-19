#include "cv8_milionar.h"

cv8_milionar::cv8_milionar(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);

    // deaktivacia buttonov, ktore sa nebudu dat stlacit, kym sa nezacne hra
    ui.pushButtonEndGame->setEnabled(false);
    ui.pushButtonAccept->setEnabled(false);
    ui.pushButtonSkip->setEnabled(false);
    ui.pushButtonZolik1->setEnabled(false);
    ui.pushButtonZolik2->setEnabled(false);
    ui.pushButtonZolik3->setEnabled(false);
}

void cv8_milionar::on_pushButtonNewGame_clicked() // button Nova hra
{

}

void cv8_milionar::on_pushButtonEndGame_clicked() // button Ukoncit hru
{

}

void cv8_milionar::on_pushButtonAccept_clicked() // button Potvrdit
{

}

void cv8_milionar::on_pushButtonSkip_clicked() // button Preskocit otazku
{

}

void cv8_milionar::on_pushButtonZolik1() // zolik 1
{

}

void cv8_milionar::on_pushButtonZolik2() // zolik 2
{

}

void cv8_milionar::on_pushButtonZolik3() // zolik 3
{

}