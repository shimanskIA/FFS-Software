#include "FFSDatabaseInterfaceFormController.h"
#include "FFSDatabaseInterfaceService.h"
#include "TableWriter.h"
#include "WindowManager.h"

#include <QVariant>

void FFSDatabaseInterfaceFormController::ManageFileImportRequest(QString fileName)
{
	FFSDatabaseInterfaceService::ImportRequestReceiver(fileName);
}

void FFSDatabaseInterfaceFormController::ManageShowMeasuringSystemTableRequest(FFSDatabaseInterface* view, bool isFirstLoad)
{
    if (isFirstLoad)
    {
        ShowMeasuringSystemTableRequestReceiver(view->GetUI().majorTableView);
        view->GetUI().tableSelector->addItem("Measurements");
        view->GetUI().tableSelector->addItem("Equipments");
        view->GetUI().tableName->setText((view->GetActualTable() + "s:").toUpper());
        view->GetUI().minorSubtableView->setDisabled(true);
        view->GetUI().minorTableSelector->setDisabled(true);
        DisableButtonActivity(view);
    }
    else
    {
        QString tableName = "measuring system";

        if (view->GetActualTable() != tableName)
        {
            ResetTableModel((FFSTableModel*)view->GetUI().majorTableView->model());
            ResetTableModel((FFSTableModel*)view->GetUI().minorTableView->model());
            ResetTableModel((FFSTableModel*)view->GetUI().minorSubtableView->model());
            view->GetUI().tableSelector->setDisabled(false);
            view->GetUI().minorTableView->setDisabled(false);
            DisableButtonActivity(view);
            view->SetSelectedId(0);
            view->SetMinorSelectedId(0);
            view->SetActualSubtable("measurements");
            view->GetUI().tableName->setText((tableName + "s:").toUpper());
            view->GetUI().minorTableSelector->clear();
            view->GetUI().tableSelector->clear();
            view->GetUI().tableSelector->addItem("Measurements");
            view->GetUI().tableSelector->addItem("Equipments");
            view->SetActualTable(tableName);
            ShowMeasuringSystemTableRequestReceiver(view->GetUI().majorTableView);
            view->SetIsRowSelected(false);
            view->SetIsSubRowSelected(false);
        }
    }
}

void FFSDatabaseInterfaceFormController::ManageShowCharacteristicsTableRequest(FFSDatabaseInterface* view)
{
    QString tableName = "characteristic";

    if (view->GetActualTable() != tableName)
    {
        ResetTableModel((FFSTableModel*)view->GetUI().majorTableView->model());
        ResetTableModel((FFSTableModel*)view->GetUI().minorTableView->model());
        ResetTableModel((FFSTableModel*)view->GetUI().minorSubtableView->model());
        view->SetSelectedId(0);
        view->SetMinorSelectedId(0);
        view->GetUI().tableName->setText((tableName + "s:").toUpper());
        view->GetUI().minorTableSelector->clear();
        view->GetUI().tableSelector->clear();
        view->GetUI().minorSubtableView->setDisabled(true);
        view->GetUI().minorTableSelector->setDisabled(true);
        view->GetUI().tableSelector->setDisabled(true);
        view->GetUI().minorTableView->setDisabled(true);
        DisableButtonActivity(view);
        view->SetActualTable(tableName);
        ShowCharacteristicsTableRequestReceiver(view->GetUI().majorTableView);
        view->SetIsRowSelected(false);
        view->SetIsSubRowSelected(false);
    }
}

void FFSDatabaseInterfaceFormController::ManageLoadDataToSubtableRequest(FFSDatabaseInterface* view)
{
    if (!view->GetEndMajorNodes().contains(view->GetActualTable()))
    {
        int selectedRow = view->GetUI().majorTableView->currentIndex().row();
        QModelIndex indexId = view->GetUI().majorTableView->model()->index(selectedRow, 0);
        int selectedId = view->GetUI().majorTableView->model()->data(indexId).toInt();

        if (selectedId != view->GetSelectedId() || view->GetIsSubtableChanged())
        {
            ResetTableModel((FFSTableModel*)view->GetUI().minorTableView->model());
            ResetTableModel((FFSTableModel*)view->GetUI().minorSubtableView->model());
            view->GetUI().majorDeleteButton->setDisabled(false);
            
            if (view->GetActualSubtable() != "measuring_systems")
            {
                view->GetUI().minorAddButton->setDisabled(false);
            }

            view->GetUI().minorDeleteButton->setDisabled(true);
            view->GetUI().minorPreviewButton->setDisabled(true);
            view->GetUI().minorAddSubbutton->setDisabled(true);
            view->GetUI().minorPreviewSubbutton->setDisabled(true);
            view->GetUI().minorDeleteSubbutton->setDisabled(true);
            view->SetSelectedId(selectedId);
            view->SetMinorSelectedId(0);
            view->SetIsSubtableChanged(false);
            QString transformedTable = view->GetActualTable();
            LoadDataToSubtableRequestReceiver(view->GetUI(), view->GetUI().minorTableView, transformedTable.replace(' ', '_'), view->GetActualSubtable(), selectedId);
            view->SetActualMinorSubtable(view->GetUI().minorTableSelector->currentText().replace(' ', '_').toLower());
            view->SetIsRowSelected(true);
            view->SetIsSubRowSelected(false);

            if (view->GetFirstLoad())
            {
                view->SetTableSettings(view->GetUI().minorTableView);
                view->SetFirstLoad(false);
            }
        }
    }
    else
    {
        if (view->GetActualTable() == "characteristic")
        {
            view->GetUI().majorPreviewButton->setDisabled(false);
        }

        view->GetUI().majorDeleteButton->setDisabled(false);
    }
}

void FFSDatabaseInterfaceFormController::ManageLoadDataToMinorSubtableRequest(FFSDatabaseInterface* view)
{
    if (!view->GetEndMinorNodes().contains(view->GetActualSubtable()))
    {
        int selectedRow = view->GetUI().minorTableView->currentIndex().row();
        QModelIndex indexId = view->GetUI().minorTableView->model()->index(selectedRow, 0);
        int selectedId = view->GetUI().minorTableView->model()->data(indexId).toInt();

        if (selectedId != view->GetMinorSelectedId() || view->GetIsMinorSubtableChanged())
        {
            ResetTableModel((FFSTableModel*)view->GetUI().minorSubtableView->model());
            view->GetUI().minorDeleteButton->setDisabled(false);
            view->GetUI().minorAddSubbutton->setDisabled(false);
            view->SetMinorSelectedId(selectedId);
            view->SetIsMinorSubtableChanged(false);
            QString transformedTable = view->GetActualSubtable();
            transformedTable.chop(1);
            LoadDataToSubtableRequestReceiver(view->GetUI(), view->GetUI().minorSubtableView, transformedTable.replace(' ', '_'), view->GetActualMinorSubtable(), selectedId);
            view->SetIsSubRowSelected(true);

            if (view->GetMinorFirstLoad())
            {
                view->SetTableSettings(view->GetUI().minorSubtableView);
                view->SetMinorFirstLoad(false);
            }
        }
    }
    else
    {
        if (view->GetActualSubtable() == "characteristics")
        {
            view->GetUI().minorPreviewButton->setDisabled(false);
        }

        view->GetUI().minorDeleteButton->setDisabled(false);
    }
}

void FFSDatabaseInterfaceFormController::ManageSwitchButtonsRequest(FFSDatabaseInterface* view)
{
    view->GetUI().minorDeleteSubbutton->setDisabled(false);

    if (view->GetActualMinorSubtable() == "characteristics")
    {
        view->GetUI().minorPreviewSubbutton->setDisabled(false);
    }
}

void FFSDatabaseInterfaceFormController::ManageRepresentSubtableRequest(FFSDatabaseInterface* view)
{
    QString newSubtable = view->GetUI().tableSelector->currentText().replace(' ', '_').toLower();
    if (newSubtable != view->GetActualSubtable())
    {
        view->SetIsSubtableChanged(true);
        view->SetIsSubRowSelected(false);
        view->SetActualSubtable(newSubtable);
        view->GetUI().minorDeleteButton->setDisabled(true);
        view->GetUI().minorPreviewButton->setDisabled(true);
        view->GetUI().minorAddSubbutton->setDisabled(true);

        if (newSubtable == "measuring_systems")
        {
            view->GetUI().minorAddButton->setDisabled(true);
        }

        if (view->GetIsRowSelected())
        {
            ManageLoadDataToSubtableRequest(view);
        }
    }
}

void FFSDatabaseInterfaceFormController::ManageRepresentMinorSubtableRequest(FFSDatabaseInterface* view)
{
    QString newMinorSubtable = view->GetUI().minorTableSelector->currentText().replace(' ', '_').toLower();
    if (newMinorSubtable != view->GetActualMinorSubtable())
    {
        view->SetIsMinorSubtableChanged(true);
        view->SetActualMinorSubtable(newMinorSubtable);
        view->GetUI().minorDeleteSubbutton->setDisabled(true);
        view->GetUI().minorPreviewSubbutton->setDisabled(true);

        if (view->GetIsSubRowSelected())
        {
            ManageLoadDataToMinorSubtableRequest(view);
        }
    }
}

void FFSDatabaseInterfaceFormController::ManageShowMajorTableRequest(QString tableName, QString subtableName, QStringList selectorItems, FFSDatabaseInterface* view)
{
    if (view->GetActualTable() != tableName)
    {
        ResetTableModel((FFSTableModel*)view->GetUI().majorTableView->model());
        ResetTableModel((FFSTableModel*)view->GetUI().minorTableView->model());
        ResetTableModel((FFSTableModel*)view->GetUI().minorSubtableView->model());
        view->GetUI().tableSelector->setDisabled(false);
        view->GetUI().minorTableView->setDisabled(false);
        DisableButtonActivity(view);
        view->SetSelectedId(0);
        view->SetMinorSelectedId(0);
        view->SetActualSubtable(subtableName);
        view->GetUI().tableName->setText((tableName + "s:").toUpper());
        view->GetUI().minorTableSelector->clear();
        view->GetUI().tableSelector->clear();

        foreach(QString item, selectorItems)
        {
            view->GetUI().tableSelector->addItem(item);
        }

        view->GetUI().minorSubtableView->setDisabled(true);
        view->GetUI().minorTableSelector->setDisabled(true);
        view->SetActualTable(tableName);
        ManageFillIndependentTableRequest(tableName, view->GetUI().majorTableView);
        view->SetIsRowSelected(false);
        view->SetIsSubRowSelected(false);
    }
}

void FFSDatabaseInterfaceFormController::ManageRemoveUnusedIdsRequest()
{
    FFSDatabaseInterfaceService::RemoveUnusedIdsRequestReceiver();
}

void FFSDatabaseInterfaceFormController::ManageSwitchToEditModeRequest(QTableView* tableView, FFSDatabaseInterface* view)
{
    view->SetIsInEditMode(true);
    QVariant cellValue = tableView->currentIndex().data();
    view->SetPreviousCellValue(cellValue);
}

void FFSDatabaseInterfaceFormController::ManageDeleteRowRequest(QTableView* tableView, QString tableName)
{
    tableName = tableName.replace(' ', '_');
    FFSDatabaseInterfaceService::DeleteRowRequestReceiver(tableView, tableName);
}

void FFSDatabaseInterfaceFormController::ManageUpdateTableRequest(QString tableName, QTableView* tableView, FFSDatabaseInterface* view)
{
    if (view->GetIsInEditMode())
    {
        view->SetIsInEditMode(false);
        QVariant cellValue = tableView->currentIndex().data();
        if (cellValue.toString() != view->GetPreviousCellValue().toString())
        {
            tableName = tableName.replace(' ', '_');
            FFSDatabaseInterfaceService::UpdateTableRequestReceiver(cellValue, tableName, tableView);
        }
    }
}

void FFSDatabaseInterfaceFormController::ManageRefreshMajorTableRequest(FFSDatabaseInterface* view)
{
    ResetTableModel((FFSTableModel*)view->GetUI().majorTableView->model());
    ResetTableModel((FFSTableModel*)view->GetUI().minorTableView->model());
    ResetTableModel((FFSTableModel*)view->GetUI().minorSubtableView->model());
    view->SetSelectedId(0);
    view->SetMinorSelectedId(0);
    view->GetUI().minorTableSelector->clear();
    view->GetUI().minorSubtableView->setDisabled(true);
    view->GetUI().minorTableSelector->setDisabled(true);
    DisableButtonActivity(view);
    ManageFillIndependentTableRequest(view->GetActualTable(), view->GetUI().majorTableView);
    view->SetIsRowSelected(false);
    view->SetIsSubRowSelected(false);
}

void FFSDatabaseInterfaceFormController::ManageRefreshViewRequest(FFSDatabaseInterface* view, bool wasAdded)
{
    if (view->GetAddTryMajorTable() && wasAdded)
    {
        view->SetAddTryMajorTable(false);
        ManageRefreshMajorTableRequest(view);
    }
    else if (view->GetAddTryMinorTable() && wasAdded)
    {
        view->SetAddTryMinorTable(false);
        view->SetIsSubtableChanged(true);
        ManageLoadDataToSubtableRequest(view);
    }
    else if (view->GetAddTryMinorSubtable() && wasAdded)
    {
        view->SetAddTryMinorSubtable(false);
        view->SetIsMinorSubtableChanged(true);
        ManageLoadDataToMinorSubtableRequest(view);
    }
}

void FFSDatabaseInterfaceFormController::ManageShowAddViewRequest(QString tableName, FFSDatabaseInterface* view)
{
    tableName = tableName.replace(' ', '_');
    ShowAddViewRequestReceiver(tableName, view);
}

void FFSDatabaseInterfaceFormController::ManageShowMinorAddViewRequest(QString tableName, FFSDatabaseInterface* view)
{
    int selectedRow = view->GetUI().majorTableView->currentIndex().row();
    QModelIndex indexId = view->GetUI().majorTableView->model()->index(selectedRow, 0);
    int selectedId = view->GetUI().majorTableView->model()->data(indexId).toInt();

    QString majorTableName = view->GetActualTable();
    view->GetForeignKeys()[majorTableName] = selectedId;
    ShowAddViewRequestReceiver(tableName, view, view->GetForeignKeys());
    view->GetForeignKeys()[view->GetActualTable()] = 0;
}

void FFSDatabaseInterfaceFormController::ManageShowMinorAddViewSubRequest(QString tableName, FFSDatabaseInterface* view)
{
    int selectedRow = view->GetUI().minorTableView->currentIndex().row();
    QModelIndex indexId = view->GetUI().minorTableView->model()->index(selectedRow, 0);
    int selectedId = view->GetUI().minorTableView->model()->data(indexId).toInt();

    QString majorTableName = view->GetActualSubtable();
    majorTableName.chop(1);
    view->GetForeignKeys()[majorTableName] = selectedId;
    ShowAddViewRequestReceiver(tableName, view, view->GetForeignKeys());
    view->GetForeignKeys()[view->GetActualSubtable()] = 0;
}

void FFSDatabaseInterfaceFormController::DisableButtonActivity(FFSDatabaseInterface* view)
{
    view->GetUI().minorAddSubbutton->setDisabled(true);
    view->GetUI().minorDeleteSubbutton->setDisabled(true);
    view->GetUI().minorPreviewSubbutton->setDisabled(true);
    view->GetUI().minorAddButton->setDisabled(true);
    view->GetUI().minorDeleteButton->setDisabled(true);
    view->GetUI().minorPreviewButton->setDisabled(true);
    view->GetUI().majorDeleteButton->setDisabled(true);
    view->GetUI().majorPreviewButton->setDisabled(true);
}

void FFSDatabaseInterfaceFormController::ResetTableModel(FFSTableModel* tableModel)
{
    tableModel->setRowCount(0);
    tableModel->setColumnCount(0);
}

void FFSDatabaseInterfaceFormController::LoadDataToSubtableRequestReceiver(Ui::FFSDatabaseInterfaceClass ui, QTableView* tableView, QString majorTableName, QString minorTableName, int majorTableId)
{
    TableWriter* tableWriter = new TableWriter();
    tableWriter->RouteRequest(ui, tableView, majorTableName, minorTableName, majorTableId);
}

void FFSDatabaseInterfaceFormController::ShowAddViewRequestReceiver(QString tableName, FFSDatabaseInterface* view, QMap<QString, int> foreignKeys)
{
    WindowManager* windowMananger = new WindowManager();
    windowMananger->ManageWindows(tableName, view, foreignKeys);
}

void FFSDatabaseInterfaceFormController::ShowMeasuringSystemTableRequestReceiver(QTableView* tableView)
{
    TableWriter* tableWriter = new TableWriter();
    tableWriter->FillMeasuringSystemsTable(tableView);
}

void FFSDatabaseInterfaceFormController::ShowCharacteristicsTableRequestReceiver(QTableView* tableView)
{
    TableWriter* tableWriter = new TableWriter();
    QString sqlReadRequest = "SELECT * FROM characteristics";
    tableWriter->FillCharacteristicsTable(tableView, sqlReadRequest);
}