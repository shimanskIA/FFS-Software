#pragma once

#include "ui_FFSDatabaseInterface.h"
#include "FFSDatabaseInterface.h"
#include "FFSTableModel.h"
#include "TableFillRequestController.h"

#include <QString>

static class FFSDatabaseInterfaceFormController : TableFillRequestController
{
public:
    static void ManageFileImportRequest(QString fileName);
    static void ManageShowMeasuringSystemTableRequest(FFSDatabaseInterface* view, bool isFirstLoad = false);
    static void ManageShowCharacteristicsTableRequest(FFSDatabaseInterface* view);
    static void ManageLoadDataToSubtableRequest(FFSDatabaseInterface* view);
    static void ManageLoadDataToMinorSubtableRequest(FFSDatabaseInterface* view);
    static void ManageSwitchButtonsRequest(FFSDatabaseInterface* view);
    static void ManageRepresentSubtableRequest(FFSDatabaseInterface* view);
    static void ManageRepresentMinorSubtableRequest(FFSDatabaseInterface* view);
    static void ManageDeleteRowRequest(QTableView* view, QString tableName);
    static void ManageRemoveUnusedIdsRequest();
    static void ManageSwitchToEditModeRequest(QTableView* tableView, FFSDatabaseInterface* view);
    static void ManageRefreshMajorTableRequest(FFSDatabaseInterface* view);
    static void ManageRefreshViewRequest(FFSDatabaseInterface* view, bool wasAdded);
    static void ManageUpdateTableRequest(QString tableName, QTableView* tableView, FFSDatabaseInterface* view);
    static void ManageShowMajorTableRequest(QString tableName, QString subtableName, QStringList selectorItems, FFSDatabaseInterface* view);
    static void ResetTableModel(FFSTableModel* tableModel);
    static void ManageShowAddViewRequest(QString tableName, FFSDatabaseInterface* view);
    static void ManageShowMinorAddViewRequest(QString tableName, FFSDatabaseInterface* view);
    static void ManageShowMinorAddViewSubRequest(QString tableName, FFSDatabaseInterface* view);
    static void ManageShowCharacteristicPreviewRequest(QTableView* tableView, FFSDatabaseInterface* view);

    static void ShowMeasuringSystemTableRequestReceiver(QTableView* tableView);
    static void ShowCharacteristicsTableRequestReceiver(QTableView* tableView);
    static void ShowAddViewRequestReceiver(QString tableName, FFSDatabaseInterface* view, QMap<QString, int> foreignKeys = QMap<QString, int>());
    static void LoadDataToSubtableRequestReceiver(Ui::FFSDatabaseInterfaceClass ui, QTableView* tableView, QString majorTableName, QString minorTableName, int majorTableId);

    static bool IsValueAllowed(QString tableName, QTableView* tableView, int selectedRow);
    static bool ContainsEqualRow(int selectedRow, QTableView* tableView);

private:
    static void DisableButtonActivity(FFSDatabaseInterface* view);
};