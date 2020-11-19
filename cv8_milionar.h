#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_cv8_milionar.h"

class cv8_milionar : public QMainWindow
{
    Q_OBJECT

public:
    cv8_milionar(QWidget *parent = Q_NULLPTR);

private:
    Ui::cv8_milionarClass ui;
};
