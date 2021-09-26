#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FFSDatabaseInterface.h"

class FFSDatabaseInterface : public QMainWindow
{
    Q_OBJECT

public:
    FFSDatabaseInterface(QWidget *parent = Q_NULLPTR);

private:
    Ui::FFSDatabaseInterfaceClass ui;
};
