#include "FFSDatabaseInterfaceFormController.h"
#include "FFSDatabaseInterfaceService.h"

FFSDatabaseInterfaceFormController::FFSDatabaseInterfaceFormController()
{

}

void FFSDatabaseInterfaceFormController::ManageFileImportRequest(QString fileName)
{
	FFSDatabaseInterfaceService::ImportRequestReceiver(fileName);
}

void FFSDatabaseInterfaceFormController::ManageShowMeasuringSystemTableRequest(FFSDatabaseInterface* view, bool isFirstLoad)
{
    if (isFirstLoad)
    {
        FFSDatabaseInterfaceService::ShowMeasuringSystemTableRequestReceiver(view->GetUI().majorTableView);
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
            view->GetUI().minorTableView->setModel(nullptr);
            view->GetUI().minorSubtableView->setModel(nullptr);
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
            FFSDatabaseInterfaceService::ShowMeasuringSystemTableRequestReceiver(view->GetUI().majorTableView);
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
        view->GetUI().minorTableView->setModel(nullptr);
        view->GetUI().minorSubtableView->setModel(nullptr);
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
        FFSDatabaseInterfaceService::ShowCharacteristicsTableRequestReceiver(view->GetUI().majorTableView);
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
            view->GetUI().minorSubtableView->setModel(nullptr);
            view->GetUI().majorDeleteButton->setDisabled(false);
            view->GetUI().minorAddButton->setDisabled(false);
            view->GetUI().minorDeleteButton->setDisabled(true);
            view->GetUI().minorPreviewButton->setDisabled(true);
            view->GetUI().minorAddSubbutton->setDisabled(true);
            view->GetUI().minorPreviewSubbutton->setDisabled(true);
            view->GetUI().minorDeleteSubbutton->setDisabled(true);
            view->SetSelectedId(selectedId);
            view->SetMinorSelectedId(0);
            view->SetIsSubtableChanged(false);
            QString transformedTable = view->GetActualTable();
            FFSDatabaseInterfaceService::LoadDataToSubtableRequestReceiver(view->GetUI(), view->GetUI().minorTableView, transformedTable.replace(' ', '_'), view->GetActualSubtable(), selectedId);
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
            view->GetUI().minorDeleteButton->setDisabled(false);
            view->GetUI().minorAddSubbutton->setDisabled(false);
            view->SetMinorSelectedId(selectedId);
            view->SetIsMinorSubtableChanged(false);
            QString transformedTable = view->GetActualSubtable();
            transformedTable.chop(1);
            FFSDatabaseInterfaceService::LoadDataToSubtableRequestReceiver(view->GetUI(), view->GetUI().minorSubtableView, transformedTable.replace(' ', '_'), view->GetActualMinorSubtable(), selectedId);
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
        view->GetUI().minorTableView->setModel(nullptr);
        view->GetUI().minorSubtableView->setModel(nullptr);
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
        FFSDatabaseInterfaceService::ShowMajorTableRequestReceiver(view);
        view->SetIsRowSelected(false);
        view->SetIsSubRowSelected(false);
    }
}

void FFSDatabaseInterfaceFormController::ManageRemoveUnusedIdsRequest()
{
    FFSDatabaseInterfaceService::RemoveUnusedIdsRequestReceiver();
}

void FFSDatabaseInterfaceFormController::ManageDeleteRowRequest(QTableView* tableView, QString tableName)
{
    tableName = tableName.replace(' ', '_');
    FFSDatabaseInterfaceService::DeleteRowRequestReceiver(tableView, tableName);
}

void FFSDatabaseInterfaceFormController::ManageRefreshMajorTableRequest(FFSDatabaseInterface* view)
{
    view->GetUI().minorTableView->setModel(nullptr);
    view->GetUI().minorSubtableView->setModel(nullptr);
    view->SetSelectedId(0);
    view->SetMinorSelectedId(0);
    view->GetUI().minorTableSelector->clear();
    view->GetUI().minorSubtableView->setDisabled(true);
    view->GetUI().minorTableSelector->setDisabled(true);
    DisableButtonActivity(view);
    FFSDatabaseInterfaceService::ShowMajorTableRequestReceiver(view);
    view->SetIsRowSelected(false);
    view->SetIsSubRowSelected(false);
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