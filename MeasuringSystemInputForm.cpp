#include "MeasuringSystemInputForm.h"
#include "MeasuringSystemInputFormController.h"

#include <QCloseEvent>

MeasuringSystemInputForm::MeasuringSystemInputForm(QWidget* parent) : QDialog(parent)
{
	ui.setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    ui.continueButton->setDisabled(true);
    ui.NameInput->setMaxLength(100);
    ui.DescriptionInput->setMaxLength(300);
    ui.MainContributorInput->setMaxLength(100);
    connect(ui.continueButton, SIGNAL(clicked()), this, SLOT(proceedNext()));
    connect(ui.NameInput, SIGNAL(textChanged(QString)), this, SLOT(manageContinueButtonActivity()));
    connect(ui.MainContributorInput, SIGNAL(textChanged(QString)), this, SLOT(manageContinueButtonActivity()));
}

Ui::MeasuringSystemInputFormClass MeasuringSystemInputForm::GetUI()
{
    return this->ui;
}

void MeasuringSystemInputForm::proceedNext()
{
    QMap<QString, QString> credentials;
    credentials.insert("name", ui.NameInput->text());
    credentials.insert("description", ui.DescriptionInput->text());
    credentials.insert("contributor", ui.MainContributorInput->text());
    emit measuringSystemSet(credentials);
    this->close();
}

void MeasuringSystemInputForm::manageContinueButtonActivity()
{
    MeasuringSystemInputFormController::ManageContinueButtonActivity(this);
}