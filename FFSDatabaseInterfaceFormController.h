#pragma once

#include "ui_FFSDatabaseInterface.h"

#include <QString>

class FFSDatabaseInterfaceFormController
{

public:
    FFSDatabaseInterfaceFormController();
    static void ManageFileImportRequest(QString fileName);
    static void ManageShowMeasurementTableRequest(Ui::FFSDatabaseInterfaceClass ui);
    static void ManageShowEquipmentTableRequest(Ui::FFSDatabaseInterfaceClass ui);
    static void ManageShowSampleTableRequest(Ui::FFSDatabaseInterfaceClass ui);
    static void ManageShowMeasuringSystemTableRequest(Ui::FFSDatabaseInterfaceClass ui);
    static void ManageLoadDataToSubtableRequest(Ui::FFSDatabaseInterfaceClass ui, QString majorTableName, QString minorTableName, int majorTableId);
};
