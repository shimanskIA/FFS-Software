#include "FFSDatabaseInterface.h"
#include "AboutForm.h"

FFSDatabaseInterface::FFSDatabaseInterface(QWidget* parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.actionInfo, SIGNAL(triggered()), this, SLOT(infoButtonClick()));
}

void FFSDatabaseInterface::infoButtonClick()
{
    //this->close();
    AboutForm* a = new AboutForm();
    a->show();
}

FFSDatabaseInterface::~FFSDatabaseInterface()
{
 
}



