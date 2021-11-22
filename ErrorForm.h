#pragma once

#include <QtWidgets/QWidget>
#include <QString>
#include <QDialog>

#include "ui_ErrorForm.h"

class ErrorForm : public QDialog
{
    Q_OBJECT

public:
    ErrorForm(QString errorMessage, QWidget* parent = Q_NULLPTR);

private slots:
    void closeWindow();

private:
    Ui::ErrorFormClass ui;
};
