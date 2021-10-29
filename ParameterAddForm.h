#pragma once

#pragma once

#include <QtWidgets/QWidget>

#include "ui_ParameterAddForm.h"
#include "FFSTableModel.h"
#include "BaseDependentAddForm.h"

class ParameterAddForm : public BaseAddForm
{
    Q_OBJECT

public:
    ParameterAddForm(QWidget* parent = Q_NULLPTR, int fk = 0, QString majorTable = "");

    int GetFK();
    QString GetMajorTableName();

    Ui::ParameterAddFormClass GetUI();

    void SetFK(int fk);
    void SetMajorTable(QString majorTable);

private slots:
    void addParameter();

private:
    Ui::ParameterAddFormClass ui;

    int fk = 0;
    QString majorTable = "";
};
