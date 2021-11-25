#include "ErrorForm.h"

ErrorForm::ErrorForm(QString errorMessage, QWidget* parent) : QDialog(parent)
{
	ui.setupUi(this);
	ui.errorMessage->setAlignment(Qt::AlignCenter);
	ui.okButton->setStyleSheet("border: 3px solid darkblue;");
	this->setStyleSheet("background-color: white;");
	this->setFixedSize(592, 215);
	this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	ui.errorMessage->setText(errorMessage);
	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(closeWindow()));
}

void ErrorForm::closeWindow()
{
	this->close();
}