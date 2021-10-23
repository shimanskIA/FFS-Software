#pragma once

#include "ui_FFSDatabaseInterface.h"
#include "FFSDatabaseInterface.h"

#include <QString>

class FFSDatabaseInterfaceFormController
{

public:
    FFSDatabaseInterfaceFormController();
    static void ManageFileImportRequest(QString fileName);
    static void ManageShowMeasuringSystemTableRequest(FFSDatabaseInterface* view, bool isFirstLoad = false);
    static void ManageShowCharacteristicsTableRequest(FFSDatabaseInterface* view);
    static void ManageLoadDataToSubtableRequest(FFSDatabaseInterface* view);
    static void ManageLoadDataToMinorSubtableRequest(FFSDatabaseInterface* view);
    static void ManageSwitchButtonsRequest(FFSDatabaseInterface* view);
    static void ManageRepresentSubtableRequest(FFSDatabaseInterface* view);
    static void ManageRepresentMinorSubtableRequest(FFSDatabaseInterface* view);
    static void ManageDeleteRowRequest(QTableView* view, QString tableName);
    static void ManageRefreshMajorTableRequest(FFSDatabaseInterface* view);
    static void ManageShowMajorTableRequest(QString tableName, QString subtableName, QStringList selectorItems, FFSDatabaseInterface* view);

private:
    static void DisableButtonActivity(FFSDatabaseInterface* view);
};