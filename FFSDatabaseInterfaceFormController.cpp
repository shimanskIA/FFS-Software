#include "FFSDatabaseInterfaceFormController.h"
#include "FFSDatabaseInterfaceService.h"
#include "TableWriter.h"
#include "RowManager.h"
#include "WindowManager.h"
#include "ErrorForm.h"

#include <QVariant>
#include <QGroupBox>

void FFSDatabaseInterfaceFormController::ManageFileImportRequest(QString fileName)
{
	OperationStatusMessage* operationStatusMessage = FFSDatabaseInterfaceService::ImportRequestReceiver(fileName);

    if (!operationStatusMessage->GetIsSuccessfull())
    {
        ErrorForm* errorForm = new ErrorForm(operationStatusMessage->GetOperationMessage());
        errorForm->show();
    }
}

void FFSDatabaseInterfaceFormController::ManageFileExportRequest(QString fileName)
{
    FFSDatabaseInterfaceService::ExportRequestReceiver(fileName);
}

void FFSDatabaseInterfaceFormController::ManageShowMeasuringSystemTableRequest(FFSDatabaseInterface* view, bool isFirstLoad)
{
    auto ui = view->GetUI();
    QString tableName = "measuring system";

    if (view->GetActualTable() != tableName)
    {
        ResetTableModel((FFSTableModel*)ui.majorTableView->model());
        ResetTableModel((FFSTableModel*)ui.minorTableView->model());
        ResetTableModel((FFSTableModel*)ui.minorSubtableView->model());
        ui.tableSelector->setDisabled(false);
        ui.minorTableView->setDisabled(false);
        DisableButtonActivity(view);
        view->SetSelectedId(0);
        view->SetMinorSelectedId(0);
        view->SetActualSubtable("measurements");
        QString title = tableName + "s:";
        title[0] = title[0].toUpper();
        ui.groupBox->setTitle(title);
        ui.minorTableSelector->clear();
        ui.tableSelector->clear();
        ui.tableSelector->addItem("Measurements");
        ui.tableSelector->addItem("Equipments");
        view->SetActualTable(tableName);
        ShowMeasuringSystemTableRequestReceiver(view->GetUI().majorTableView);
        view->SetIsRowSelected(false);
        view->SetIsSubRowSelected(false);
        DeactivateChildSearchInputs(ui);
    }
}

void FFSDatabaseInterfaceFormController::ManageShowCharacteristicsTableRequest(FFSDatabaseInterface* view)
{
    QString tableName = "characteristic";

    if (view->GetActualTable() != tableName)
    {
        auto ui = view->GetUI();
        ResetTableModel((FFSTableModel*)ui.majorTableView->model());
        ResetTableModel((FFSTableModel*)ui.minorTableView->model());
        ResetTableModel((FFSTableModel*)ui.minorSubtableView->model());
        view->SetSelectedId(0);
        view->SetMinorSelectedId(0);
        QString title = tableName + "s:";
        title[0] = title[0].toUpper();
        ui.groupBox->setTitle(title);
        ui.minorTableSelector->clear();
        ui.tableSelector->clear();
        ui.minorSubtableView->setDisabled(true);
        ui.minorTableSelector->setDisabled(true);
        ui.tableSelector->setDisabled(true);
        ui.minorTableView->setDisabled(true);
        DisableButtonActivity(view);
        view->SetActualTable(tableName);
        ShowCharacteristicsTableRequestReceiver(ui.majorTableView);
        view->SetIsRowSelected(false);
        view->SetIsSubRowSelected(false);
        DeactivateChildSearchInputs(ui);
    }
}

void FFSDatabaseInterfaceFormController::ManageLoadDataToSubtableRequest(FFSDatabaseInterface* view)
{
    auto ui = view->GetUI();
    
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

            ui.minorDeleteButton->setDisabled(true);
            ui.minorPreviewButton->setDisabled(true);
            ui.minorAddSubbutton->setDisabled(true);
            ui.minorPreviewSubbutton->setDisabled(true);
            ui.minorDeleteSubbutton->setDisabled(true);
            ui.searchInput->setDisabled(false);
            ui.searchInput->setText("");
            ui.searchImage->setDisabled(false);
            ui.advancedSearchCheckbox->setDisabled(false);
            ui.minorSearchInput->setDisabled(true);
            ui.minorSearchInput->setText("");
            ui.minorSearchImage->setDisabled(true);
            ui.minorAdvancedSearchCheckbox->setDisabled(true);
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
            ui.majorPreviewButton->setDisabled(false);
        }

        ui.majorDeleteButton->setDisabled(false);
    }
}

void FFSDatabaseInterfaceFormController::ManageLoadDataToMinorSubtableRequest(FFSDatabaseInterface* view)
{
    auto ui = view->GetUI();
    
    if (!view->GetEndMinorNodes().contains(view->GetActualSubtable()))
    {
        int selectedRow = view->GetUI().minorTableView->currentIndex().row();
        QModelIndex indexId = view->GetUI().minorTableView->model()->index(selectedRow, 0);
        int selectedId = view->GetUI().minorTableView->model()->data(indexId).toInt();

        if (selectedId != view->GetMinorSelectedId() || view->GetIsMinorSubtableChanged())
        {
            ResetTableModel((FFSTableModel*)ui.minorSubtableView->model());
            ui.minorDeleteButton->setDisabled(false);
            ui.minorAddSubbutton->setDisabled(false);
            ui.minorSearchInput->setDisabled(false);
            ui.minorSearchInput->setText("");
            ui.minorSearchImage->setDisabled(false);
            ui.minorAdvancedSearchCheckbox->setDisabled(false);
            view->SetMinorSelectedId(selectedId);
            view->SetIsMinorSubtableChanged(false);
            QString transformedTable = view->GetActualSubtable();
            transformedTable.chop(1);
            LoadDataToSubtableRequestReceiver(ui, ui.minorSubtableView, transformedTable.replace(' ', '_'), view->GetActualMinorSubtable(), selectedId);
            view->SetIsSubRowSelected(true);

            if (view->GetMinorFirstLoad())
            {
                view->SetTableSettings(ui.minorSubtableView);
                view->SetMinorFirstLoad(false);
            }
        }
    }
    else
    {
        if (view->GetActualSubtable() == "characteristics")
        {
            ui.minorPreviewButton->setDisabled(false);
        }

        ui.minorDeleteButton->setDisabled(false);
    }
}

void FFSDatabaseInterfaceFormController::ManageSwitchButtonsRequest(FFSDatabaseInterface* view)
{
    auto ui = view->GetUI();
    ui.minorDeleteSubbutton->setDisabled(false);

    if (view->GetActualMinorSubtable() == "characteristics")
    {
        ui.minorPreviewSubbutton->setDisabled(false);
    }
}

void FFSDatabaseInterfaceFormController::ManageRepresentSubtableRequest(FFSDatabaseInterface* view)
{
    auto ui = view->GetUI();
    QString newSubtable = ui.tableSelector->currentText().replace(' ', '_').toLower();

    if (newSubtable != view->GetActualSubtable())
    {
        view->SetIsSubtableChanged(true);
        view->SetIsSubRowSelected(false);
        view->SetActualSubtable(newSubtable);
        ui.minorDeleteButton->setDisabled(true);
        ui.minorPreviewButton->setDisabled(true);
        ui.minorAddSubbutton->setDisabled(true);
        ui.searchInput->setText("");
        ui.minorSearchInput->setDisabled(true);
        ui.minorSearchImage->setDisabled(true);
        ui.minorAdvancedSearchCheckbox->setDisabled(true);

        if (newSubtable == "measuring_systems")
        {
            ui.minorAddButton->setDisabled(true);
        }

        if (view->GetIsRowSelected())
        {
            ManageLoadDataToSubtableRequest(view);
        }
    }
}

void FFSDatabaseInterfaceFormController::ManageRepresentMinorSubtableRequest(FFSDatabaseInterface* view)
{
    auto ui = view->GetUI();
    QString newMinorSubtable = ui.minorTableSelector->currentText().replace(' ', '_').toLower();

    if (newMinorSubtable != view->GetActualMinorSubtable())
    {
        view->SetIsMinorSubtableChanged(true);
        view->SetActualMinorSubtable(newMinorSubtable);
        ui.minorDeleteSubbutton->setDisabled(true);
        ui.minorPreviewSubbutton->setDisabled(true);
        ui.minorSearchInput->setText("");

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
        auto ui = view->GetUI();
        ResetTableModel((FFSTableModel*)ui.majorTableView->model());
        ResetTableModel((FFSTableModel*)ui.minorTableView->model());
        ResetTableModel((FFSTableModel*)ui.minorSubtableView->model());
        ui.tableSelector->setDisabled(false);
        ui.minorTableView->setDisabled(false);
        DisableButtonActivity(view);
        view->SetSelectedId(0);
        view->SetMinorSelectedId(0);
        view->SetActualSubtable(subtableName);
        QString title = tableName + "s:";
        title[0] = title[0].toUpper();
        ui.groupBox->setTitle(title);
        ui.minorTableSelector->clear();
        ui.tableSelector->clear();

        foreach(QString item, selectorItems)
        {
            ui.tableSelector->addItem(item);
        }

        DeactivateChildSearchInputs(ui);
        view->SetActualTable(tableName);
        ManageFillIndependentTableRequest(tableName, ui.majorTableView);
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
    int selectedRow = tableView->currentIndex().row();
    QModelIndex indexId = tableView->model()->index(selectedRow, 0);
    int selectedId = tableView->model()->data(indexId).toInt();
    OperationStatusMessage* operationStatusMessage = FFSDatabaseInterfaceService::DeleteRowRequestReceiver(tableName, selectedId);

    if (!operationStatusMessage->GetIsSuccessfull())
    {
        ErrorForm* errorForm = new ErrorForm(operationStatusMessage->GetOperationMessage());
        errorForm->show();
    }
}

void FFSDatabaseInterfaceFormController::ManageUpdateTableRequest(QString tableName, QTableView* tableView, FFSDatabaseInterface* view)
{
    if (view->GetIsInEditMode())
    {
        auto model = tableView->model();
        view->SetIsInEditMode(false);

        if (IsValueAllowed(tableName, tableView, tableView->currentIndex().row()))
        {
            QVariant cellValue = tableView->currentIndex().data();
            if (cellValue.toString() != view->GetPreviousCellValue().toString())
            {
                tableName = tableName.replace(' ', '_');
                int selectedColumn = tableView->currentIndex().column();
                QString columnName = model->headerData(selectedColumn, Qt::Horizontal, Qt::DisplayRole).toString();
                columnName = columnName.replace(' ', '_').toLower();
                int selectedRow = tableView->currentIndex().row();
                QModelIndex indexId = model->index(selectedRow, 0);
                int selectedId = model->data(indexId).toInt();
                OperationStatusMessage* operationStatusMessage = 
                    FFSDatabaseInterfaceService::UpdateTableRequestReceiver(tableName, columnName, cellValue, selectedId);

                if (!operationStatusMessage->GetIsSuccessfull())
                {
                    model->setData(tableView->currentIndex(), view->GetPreviousCellValue());
                    ErrorForm* errorForm = new ErrorForm(operationStatusMessage->GetOperationMessage());
                    errorForm->show();
                }
            }
        }
        else
        {
            model->setData(tableView->currentIndex(), view->GetPreviousCellValue());
            QString errorMessage = "The %1 you are trying to add already exists in database";
            tableName.chop(1);
            tableName.replace('_', ' ');
            ErrorForm* errorForm = new ErrorForm(errorMessage.arg(tableName));
            errorForm->show();
        }
    }
}

void FFSDatabaseInterfaceFormController::ManageRefreshMajorTableRequest(FFSDatabaseInterface* view)
{
    auto ui = view->GetUI();
    ResetTableModel((FFSTableModel*)view->GetUI().majorTableView->model());
    ResetTableModel((FFSTableModel*)view->GetUI().minorTableView->model());
    ResetTableModel((FFSTableModel*)view->GetUI().minorSubtableView->model());
    view->SetSelectedId(0);
    view->SetMinorSelectedId(0);
    ui.minorTableSelector->clear();
    ui.minorSubtableView->setDisabled(true);
    ui.minorTableSelector->setDisabled(true);
    DisableButtonActivity(view);
    ManageFillIndependentTableRequest(view->GetActualTable(), view->GetUI().majorTableView);
    view->SetIsRowSelected(false);
    view->SetIsSubRowSelected(false);
    DeactivateChildSearchInputs(ui);
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
    auto ui = view->GetUI();
    int selectedRow = ui.majorTableView->currentIndex().row();
    QModelIndex indexId = ui.majorTableView->model()->index(selectedRow, 0);
    int selectedId = ui.majorTableView->model()->data(indexId).toInt();

    QString majorTableName = view->GetActualTable();
    view->GetForeignKeys()[majorTableName] = selectedId;
    ShowAddViewRequestReceiver(tableName, view, view->GetForeignKeys());
    view->GetForeignKeys()[view->GetActualTable()] = 0;
}

void FFSDatabaseInterfaceFormController::ManageShowMinorAddViewSubRequest(QString tableName, FFSDatabaseInterface* view)
{
    auto ui = view->GetUI();
    int selectedRow = ui.minorTableView->currentIndex().row();
    QModelIndex indexId = ui.minorTableView->model()->index(selectedRow, 0);
    int selectedId = ui.minorTableView->model()->data(indexId).toInt();

    QString majorTableName = view->GetActualSubtable();
    majorTableName.chop(1);
    view->GetForeignKeys()[majorTableName] = selectedId;
    ShowAddViewRequestReceiver(tableName, view, view->GetForeignKeys());
    view->GetForeignKeys()[view->GetActualSubtable()] = 0;
}

void FFSDatabaseInterfaceFormController::ManageShowCharacteristicPreviewRequest(QTableView* tableView, FFSDatabaseInterface* view)
{
    int selectedRow = tableView->currentIndex().row();
    QModelIndex indexId = tableView->model()->index(selectedRow, 0);
    int selectedId = tableView->model()->data(indexId).toInt();

    if (view->GetOpenedCharacteristicPreviewWindows().contains(selectedId))
    {
        view->GetOpenedCharacteristicPreviewWindows()[selectedId]->showNormal();
    }
    else
    {

        QVector<double> x;
        QVector<double> y;

        OperationStatusMessage* readAbscissaRequestStatusMessage = FFSDatabaseInterfaceService::ReadAbscissaRequestReceiver(selectedId, x);
        OperationStatusMessage* readOrdinateRequestStatusMessage = FFSDatabaseInterfaceService::ReadOrdinateRequestReceiver(selectedId, y);

        if (readAbscissaRequestStatusMessage->GetIsSuccessfull() &&
            readOrdinateRequestStatusMessage->GetIsSuccessfull())
        {
            QString title = BuildTitle(tableView, selectedRow);
            WindowManager::GetWindowManagerInstance().ShowCharacteristicPreview(title, x, y, view, selectedId);
        }
        else
        {
            if (!readAbscissaRequestStatusMessage->GetIsSuccessfull())
            {
                ErrorForm* errorForm = new ErrorForm(readAbscissaRequestStatusMessage->GetOperationMessage());
                errorForm->show();
            }

            if (!readOrdinateRequestStatusMessage->GetIsSuccessfull())
            {
                ErrorForm* errorForm = new ErrorForm(readOrdinateRequestStatusMessage->GetOperationMessage());
                errorForm->show();
            }
        }
    }
}

void FFSDatabaseInterfaceFormController::ManageShowMajorFilteredRowsRequest(FFSDatabaseInterface* view, QString keyword)
{    
    auto ui = view->GetUI();
    RowManager::GetRowManagerInstance().ShowAllRows(ui.majorTableView);
    RowManager::GetRowManagerInstance().FilterRowsByKeyword(ui.majorTableView, keyword);

    if (!view->GetEndMajorNodes().contains(view->GetActualTable()))
    {
        if (ui.majorTableView->isRowHidden(ui.majorTableView->currentIndex().row()))
        {
            if (ui.searchInput->isEnabled())
            {
                RowManager::GetRowManagerInstance().HideAllRows(ui.minorTableView);
                ui.searchInput->setDisabled(true);
                ui.searchImage->setDisabled(true);
                ui.advancedSearchCheckbox->setDisabled(true);
            }

            if (ui.minorSearchInput->isEnabled())
            {
                RowManager::GetRowManagerInstance().HideAllRows(ui.minorSubtableView);
                ui.minorSearchInput->setDisabled(true);
                ui.minorSearchImage->setDisabled(true);
                ui.minorAdvancedSearchCheckbox->setDisabled(true);
            }
        }
        else
        {
            if (ui.majorTableView->currentIndex().row() != -1)
            {
                RowManager::GetRowManagerInstance().ShowAllRows(ui.minorTableView);
                RowManager::GetRowManagerInstance().FilterRowsByKeyword(ui.minorTableView, ui.searchInput->text());
                ui.searchInput->setDisabled(false);
                ui.searchImage->setDisabled(false);
                ui.advancedSearchCheckbox->setDisabled(false);
            }

            if (ui.minorTableView->currentIndex().row() != -1)
            {
                RowManager::GetRowManagerInstance().ShowAllRows(ui.minorSubtableView);
                RowManager::GetRowManagerInstance().FilterRowsByKeyword(ui.minorSubtableView, ui.minorSearchInput->text());
                ui.minorSearchInput->setDisabled(false);
                ui.minorSearchImage->setDisabled(false);
                ui.minorAdvancedSearchCheckbox->setDisabled(false);
            }
        }
    }
    else
    {
        if (ui.searchInput->isEnabled())
        {
            RowManager::GetRowManagerInstance().HideAllRows(ui.minorTableView);
            ui.searchInput->setDisabled(true);
            ui.searchImage->setDisabled(true);
            ui.advancedSearchCheckbox->setDisabled(true);
        }
    }
}

void FFSDatabaseInterfaceFormController::ManageShowFilteredRowsRequest(FFSDatabaseInterface* view, QString keyword)
{
    auto ui = view->GetUI();
    RowManager::GetRowManagerInstance().ShowAllRows(ui.minorTableView);
    RowManager::GetRowManagerInstance().FilterRowsByKeyword(ui.minorTableView, keyword);

    if (!view->GetEndMinorNodes().contains(view->GetActualSubtable()))
    {
        if (ui.minorTableView->isRowHidden(ui.minorTableView->currentIndex().row()))
        {
            if (ui.minorSearchInput->isEnabled())
            {
                RowManager::GetRowManagerInstance().HideAllRows(ui.minorSubtableView);
                ui.minorSearchInput->setDisabled(true);
                ui.minorSearchImage->setDisabled(true);
                ui.minorAdvancedSearchCheckbox->setDisabled(true);
            }
        }
        else
        {
            if (ui.minorTableView->currentIndex().row() != -1)
            {
                RowManager::GetRowManagerInstance().ShowAllRows(ui.minorSubtableView);
                RowManager::GetRowManagerInstance().FilterRowsByKeyword(ui.minorSubtableView, ui.minorSearchInput->text());
                ui.minorSearchInput->setDisabled(false);
                ui.minorSearchImage->setDisabled(false);
                ui.minorAdvancedSearchCheckbox->setDisabled(false);
            }
        }
    }
    else
    {
        if (ui.minorSearchInput->isEnabled())
        {
            RowManager::GetRowManagerInstance().HideAllRows(ui.minorSubtableView);
            ui.minorSearchInput->setDisabled(true);
            ui.minorSearchImage->setDisabled(true);
            ui.minorAdvancedSearchCheckbox->setDisabled(true);
        }
    }
}

void FFSDatabaseInterfaceFormController::ManageShowMinorFilteredRowsRequest(FFSDatabaseInterface* view, QString keyword)
{
    auto ui = view->GetUI();
    RowManager::GetRowManagerInstance().ShowAllRows(ui.minorSubtableView);
    RowManager::GetRowManagerInstance().FilterRowsByKeyword(ui.minorSubtableView, keyword);
}

void FFSDatabaseInterfaceFormController::ManageShowAdvancedFilteredRowsRequest(QTableView* tableView, QString request)
{
    RowManager::GetRowManagerInstance().ShowAllRows(tableView);

    if (request != "")
    {
        RowManager::GetRowManagerInstance().AdvancedFilterRowsByRequest(tableView, request);
    }
    else
    {
        tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        tableView->horizontalHeader()->setStretchLastSection(true);
    }
    
    tableView->clearSelection();
}

void FFSDatabaseInterfaceFormController::ManageCreateMeasuringSystemInputFormRequest()
{
    WindowManager::GetWindowManagerInstance().BindMeasuringSystemToInputForm();
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
    TableWriter::GetTableWriterInstance().RouteRequest(ui, tableView, majorTableName, minorTableName, majorTableId);
}

void FFSDatabaseInterfaceFormController::ShowAddViewRequestReceiver(QString tableName, FFSDatabaseInterface* view, QMap<QString, int> foreignKeys)
{
    WindowManager::GetWindowManagerInstance().ManageWindows(tableName, view, foreignKeys);
}

void FFSDatabaseInterfaceFormController::ShowMeasuringSystemTableRequestReceiver(QTableView* tableView)
{
    TableWriter::GetTableWriterInstance().FillMeasuringSystemsTable(tableView);
}

void FFSDatabaseInterfaceFormController::ShowCharacteristicsTableRequestReceiver(QTableView* tableView)
{
    TableWriter::GetTableWriterInstance().FillCharacteristicsTable(tableView);
}

bool FFSDatabaseInterfaceFormController::IsValueAllowed(QString tableName, QTableView* tableView, int selectedRow)
{
    if (tableName.contains("parameter"))
    {
        return ContainsEqualRow(selectedRow, tableView);
    }

    return true;
}

bool FFSDatabaseInterfaceFormController::ContainsEqualRow(int selectedRow, QTableView* tableView)
{
    auto model = tableView->model();
    
    for (int i = 0; i < model->rowCount(); i++)
    {
        if (i != selectedRow)
        {
            bool contains = true;

            for (int j = 1; j < model->columnCount(); j++)
            {
                if (model->index(i, j).data() == model->index(selectedRow, j).data())
                {
                    contains = contains && true;
                }
                else
                {
                    contains = false;
                    break;
                }
            }

            if (contains)
            {
                return false;
            }
        }
    }

    return true;
}

void FFSDatabaseInterfaceFormController::DeactivateChildSearchInputs(Ui::FFSDatabaseInterfaceClass ui)
{
    ui.searchInput->setDisabled(true);
    ui.searchInput->setText("");
    ui.searchImage->setDisabled(true);
    ui.minorSearchInput->setDisabled(true);
    ui.minorSearchInput->setText("");
    ui.minorSearchImage->setDisabled(true);
    ui.majorSearchInput->setText("");
    ui.advancedSearchCheckbox->setDisabled(true);
    ui.minorAdvancedSearchCheckbox->setDisabled(true);
}

QString FFSDatabaseInterfaceFormController::BuildTitle(QTableView* tableView, int selectedRow)
{
    QString channel = tableView->model()->index(selectedRow, 2).data().toString().trimmed();
    QString numberOfPoints = tableView->model()->index(selectedRow, 3).data().toString().trimmed();
    QString binTime = tableView->model()->index(selectedRow, 4).data().toString().trimmed();
    QString type = tableView->model()->index(selectedRow, 6).data().toString().trimmed();
    return channel + ", Number of points: " + numberOfPoints + ", Bin time: " + binTime + ", " + type;
}