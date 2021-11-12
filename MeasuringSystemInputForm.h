#pragma once

#include <QDialog>
#include <QString>
#include <QList>

#include "ui_MeasuringSystemInputForm.h"

class MeasuringSystemInputForm : public QDialog
{
    Q_OBJECT

public:
    MeasuringSystemInputForm(QWidget* parent = Q_NULLPTR);

    Ui::MeasuringSystemInputFormClass GetUI();

signals:
    void measuringSystemSet(QMap<QString, QString> measuringSystemParameters);

private slots:
    void proceedNext();
    void manageContinueButtonActivity();

private:
    Ui::MeasuringSystemInputFormClass ui;
};
