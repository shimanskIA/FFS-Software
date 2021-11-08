#pragma once

#include <QtWidgets/QWidget>
#include <QString>

#include "ui_ErrorForm.h"

class ErrorForm : public QWidget
{
    Q_OBJECT

public:
    ErrorForm(QString errorMessage, QWidget* parent = Q_NULLPTR);

private slots:
    void closeWindow();

private:
    Ui::ErrorFormClass ui;
};
