#include "FFSDatabaseInterfaceFormController.h"
#include "FFSDatabaseInterfaceService.h"

FFSDatabaseInterfaceFormController::FFSDatabaseInterfaceFormController()
{

}

void FFSDatabaseInterfaceFormController::ManageFileImportRequest(QString fileName)
{
	FFSDatabaseInterfaceService::ImportRequestReceiver(fileName);
}

void FFSDatabaseInterfaceFormController::ManageShowMeasurementTableRequest(FFSDatabaseInterface* view)
{
    QString tableName = "measurement";

    if (view->GetActualTable() != tableName)
    {
        view->GetUI().minorTableView->setModel(nullptr);
        view->GetUI().minorSubtableView->setModel(nullptr);
        view->GetUI().tableSelector->setDisabled(false);
        view->GetUI().minorTableView->setDisabled(false);
        view->SetActualSubtable("measurement_parameters");
        view->GetUI().tableName->setText((tableName + "s:").toUpper());
        view->GetUI().minorTableSelector->clear();
        view->GetUI().tableSelector->clear();
        view->GetUI().tableSelector->addItem("Measurement parameters");
        view->GetUI().tableSelector->addItem("Characteristics");
        view->GetUI().minorSubtableView->setDisabled(true);
        view->GetUI().minorTableSelector->setDisabled(true);
        view->SetActualTable(tableName);
        FFSDatabaseInterfaceService::ShowMeasurementTableRequestReceiver(view->GetUI().majorTableView);
        view->SetIsRowSelected(false);
        view->SetIsSubRowSelected(false);
    }
}

void FFSDatabaseInterfaceFormController::ManageShowSampleTableRequest(FFSDatabaseInterface* view)
{
    QString tableName = "sample";

    if (view->GetActualTable() != tableName)
    {
        view->GetUI().minorTableView->setModel(nullptr);
        view->GetUI().minorSubtableView->setModel(nullptr);
        view->GetUI().tableSelector->setDisabled(false);
        view->GetUI().minorTableView->setDisabled(false);
        view->SetActualSubtable("measurements");
        view->GetUI().tableName->setText((tableName + "s:").toUpper());
        view->GetUI().minorTableSelector->clear();
        view->GetUI().tableSelector->clear();
        view->GetUI().tableSelector->addItem("Measurements");
        view->GetUI().minorSubtableView->setDisabled(true);
        view->GetUI().minorTableSelector->setDisabled(true);
        view->SetActualTable(tableName);
        FFSDatabaseInterfaceService::ShowSampleTableRequestReceiver(view->GetUI().majorTableView);
        view->SetIsRowSelected(false);
        view->SetIsSubRowSelected(false);
    }
}

void FFSDatabaseInterfaceFormController::ManageShowEquipmentTableRequest(FFSDatabaseInterface* view)
{
    QString tableName = "equipment";

    if (view->GetActualTable() != tableName)
    {
        view->GetUI().minorTableView->setModel(nullptr);
        view->GetUI().minorSubtableView->setModel(nullptr);
        view->GetUI().tableSelector->setDisabled(false);
        view->GetUI().minorTableView->setDisabled(false);
        view->SetActualSubtable("equipment_parameters");
        view->GetUI().tableName->setText((tableName + "s:").toUpper());
        view->GetUI().minorTableSelector->clear();
        view->GetUI().tableSelector->clear();
        view->GetUI().tableSelector->addItem("Equipment parameters");
        view->GetUI().tableSelector->addItem("Measuring systems");
        view->GetUI().minorSubtableView->setDisabled(true);
        view->GetUI().minorTableSelector->setDisabled(true);
        view->SetActualTable(tableName);
        FFSDatabaseInterfaceService::ShowEquipmentTableRequestReceiver(view->GetUI().majorTableView);
        view->SetIsRowSelected(false);
        view->SetIsSubRowSelected(false);
    }
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

void FFSDatabaseInterfaceFormController::ManageShowCharacteristicTypesTableRequest(FFSDatabaseInterface* view)
{
    QString tableName = "characteristic type";

    if (view->GetActualTable() != tableName)
    {
        view->GetUI().minorTableView->setModel(nullptr);
        view->GetUI().minorSubtableView->setModel(nullptr);
        view->GetUI().tableSelector->setDisabled(false);
        view->GetUI().minorTableView->setDisabled(false);
        view->SetActualSubtable("characteristics");
        view->GetUI().tableName->setText((tableName + "s:").toUpper());
        view->GetUI().minorTableSelector->clear();
        view->GetUI().tableSelector->clear();
        view->GetUI().tableSelector->addItem("Characteristics");
        view->GetUI().minorSubtableView->setDisabled(true);
        view->GetUI().minorTableSelector->setDisabled(true);
        view->SetActualTable(tableName);
        FFSDatabaseInterfaceService::ShowCharacteristicTypesTableRequestReceiver(view->GetUI().majorTableView);
        view->SetIsRowSelected(false);
        view->SetIsSubRowSelected(false);
    }
}

void FFSDatabaseInterfaceFormController::ManageShowCharacteristicsTableRequest(FFSDatabaseInterface* view)
{
    QString tableName = "characteristic";

    if (view->GetActualTable() != tableName)
    {
        view->GetUI().minorTableView->setModel(nullptr);
        view->GetUI().minorSubtableView->setModel(nullptr);
        view->GetUI().tableName->setText((tableName + "s:").toUpper());
        view->GetUI().minorTableSelector->clear();
        view->GetUI().tableSelector->clear();
        view->GetUI().minorSubtableView->setDisabled(true);
        view->GetUI().minorTableSelector->setDisabled(true);
        view->GetUI().tableSelector->setDisabled(true);
        view->GetUI().minorTableView->setDisabled(true);
        view->SetActualTable(tableName);
        FFSDatabaseInterfaceService::ShowCharacteristicsTableRequestReceiver(view->GetUI().majorTableView);
        view->SetIsRowSelected(false);
        view->SetIsSubRowSelected(false);
    }
}

void FFSDatabaseInterfaceFormController::ManageLoadDataToSubtableRequest(FFSDatabaseInterface* view)
{
    int selectedRow = view->GetUI().majorTableView->currentIndex().row();
    QModelIndex indexId = view->GetUI().majorTableView->model()->index(selectedRow, 0);
    int selectedId = view->GetUI().majorTableView->model()->data(indexId).toInt();

    if (selectedId != view->GetSelectedId() || view->GetIsSubtableChanged())
    {
        view->GetUI().minorSubtableView->setModel(nullptr);
        view->SetSelectedId(selectedId);
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

void FFSDatabaseInterfaceFormController::ManageLoadDataToMinorSubtableRequest(FFSDatabaseInterface* view)
{
    int selectedRow = view->GetUI().minorTableView->currentIndex().row();
    QModelIndex indexId = view->GetUI().minorTableView->model()->index(selectedRow, 0);
    int selectedId = view->GetUI().minorTableView->model()->data(indexId).toInt();

    if (selectedId != view->GetMinorSelectedId() || view->GetIsMinorSubtableChanged())
    {
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

void FFSDatabaseInterfaceFormController::ManageRepresentSubtableRequest(FFSDatabaseInterface* view)
{
    QString newSubtable = view->GetUI().tableSelector->currentText().replace(' ', '_').toLower();
    if (newSubtable != view->GetActualSubtable())
    {
        view->SetIsSubtableChanged(true);
        view->SetIsSubRowSelected(false);
        view->SetActualSubtable(newSubtable);

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