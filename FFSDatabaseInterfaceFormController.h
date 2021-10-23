#pragma once

#include "ui_FFSDatabaseInterface.h"
#include "FFSDatabaseInterface.h"

#include <QString>

class FFSDatabaseInterfaceFormController
{

public:
    FFSDatabaseInterfaceFormController();
    static void ManageFileImportRequest(QString fileName);
    static void ManageShowMeasurementTableRequest(FFSDatabaseInterface* view);
    static void ManageShowEquipmentTableRequest(FFSDatabaseInterface* view);
    static void ManageShowSampleTableRequest(FFSDatabaseInterface* view);
    static void ManageShowMeasuringSystemTableRequest(FFSDatabaseInterface* view, bool isFirstLoad = false);
    static void ManageShowCharacteristicTypesTableRequest(FFSDatabaseInterface* view);
    static void ManageShowCharacteristicsTableRequest(FFSDatabaseInterface* view);
    static void ManageLoadDataToSubtableRequest(FFSDatabaseInterface* view);
    static void ManageLoadDataToMinorSubtableRequest(FFSDatabaseInterface* view);
    static void ManageSwitchButtonsRequest(FFSDatabaseInterface* view);
    static void ManageRepresentSubtableRequest(FFSDatabaseInterface* view);
    static void ManageRepresentMinorSubtableRequest(FFSDatabaseInterface* view);

private:
    static void DisableButtonActivity(FFSDatabaseInterface* view);
};