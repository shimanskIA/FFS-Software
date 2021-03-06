#include "TableWriter.h"
#include "TableItemDelegate.h"

#include <QStandardItemModel>

TableWriter& TableWriter::GetTableWriterInstance()
{
	static TableWriter* tableWriterInstance = 0;

	if (tableWriterInstance == 0)
	{
		tableWriterInstance = new TableWriter();
	}

	return *tableWriterInstance;
}

void TableWriter::FillMeasuringSystemsTable(QTableView* tableView)
{
	QList<MeasuringSystemContext*> measuringSystems = DbReader::GetDbReaderInstance().ReadMeasuringSystemsFromDatabase();
	FFSTableModel* tableModel = (FFSTableModel*)tableView->model();
	tableModel->setRowCount(measuringSystems.length());
	tableModel->setColumnCount(4);

	for (int j = 0; j < tableModel->columnCount(); j++)
	{
		tableModel->setHeaderData(j, Qt::Horizontal, measuringSystemColumnNames.at(j));
	}

	for (int i = 0; i < tableModel->rowCount(); i++)
	{
		
		tableModel->setData(tableModel->index(i, 0), measuringSystems.at(i)->GetId());
		tableModel->setData(tableModel->index(i, 1), measuringSystems.at(i)->GetName());
		tableModel->itemFromIndex(tableModel->index(i, 1))->setTextAlignment(Qt::AlignBottom);
		tableModel->setData(tableModel->index(i, 2), measuringSystems.at(i)->GetDescription());
		tableModel->itemFromIndex(tableModel->index(i, 2))->setTextAlignment(Qt::AlignBottom);
		tableModel->setData(tableModel->index(i, 3), measuringSystems.at(i)->GetMainContributorName());
		tableModel->itemFromIndex(tableModel->index(i, 3))->setTextAlignment(Qt::AlignBottom);
	}

	tableView->setColumnHidden(0, true);
}

void TableWriter::FillMeasuringSystemsTable(QTableView* tableView, QString majorTableName, int majorTableId)
{
	QList<BindingContext*> bindings = DbReader::GetDbReaderInstance().ReadBindingsFromDatabase(majorTableName, majorTableId);
	QList<MeasuringSystemContext*> measuringSystems;

	foreach(BindingContext * binding, bindings)
	{
		QString sqlReadRequest = "SELECT * FROM measuring_systems WHERE id = %1";
		QSqlQuery query = DbReader::GetDbReaderInstance().ReadFromDatabase(sqlReadRequest.arg(binding->GetFKMeasuringSystem()));

		if (query.next())
		{
			int id = query.value(0).toInt();
			MeasuringSystemContext* measuringSystem = new MeasuringSystemContext(id);
			measuringSystem->SetName(query.value(1).toString().trimmed());
			measuringSystem->SetDescription(query.value(2).toString().trimmed());
			measuringSystem->SetMainContributorName(query.value(3).toString().trimmed());
			measuringSystems.append(measuringSystem);
		}
	}

	FFSTableModel* tableModel = (FFSTableModel*)tableView->model();
	tableModel->setRowCount(measuringSystems.length());
	tableModel->setColumnCount(4);

	for (int j = 0; j < tableModel->columnCount(); j++)
	{
		tableModel->setHeaderData(j, Qt::Horizontal, measuringSystemColumnNames.at(j));
	}

	for (int i = 0; i < tableModel->rowCount(); i++)
	{
		tableModel->setData(tableModel->index(i, 0), measuringSystems.at(i)->GetId());
		tableModel->setData(tableModel->index(i, 1), measuringSystems.at(i)->GetName());
		tableModel->itemFromIndex(tableModel->index(i, 1))->setTextAlignment(Qt::AlignBottom);
		tableModel->setData(tableModel->index(i, 2), measuringSystems.at(i)->GetDescription());
		tableModel->itemFromIndex(tableModel->index(i, 2))->setTextAlignment(Qt::AlignBottom);
		tableModel->setData(tableModel->index(i, 3), measuringSystems.at(i)->GetMainContributorName());
		tableModel->itemFromIndex(tableModel->index(i, 3))->setTextAlignment(Qt::AlignBottom);
	}

	tableView->setColumnHidden(0, true);
}

void TableWriter::FillMeasurementsTable(QTableView* tableView)
{
	QList<MeasurementContext*> measurements = DbReader::GetDbReaderInstance().ReadMeasurementsFromDatabase();
	FFSTableModel* tableModel = (FFSTableModel*)tableView->model();
	tableModel->setRowCount(measurements.length());
	tableModel->setColumnCount(9);

	for (int j = 0; j < tableModel->columnCount(); j++)
	{
		tableModel->setHeaderData(j, Qt::Horizontal, measurementColumnNames.at(j));
	}

	for (int i = 0; i < tableModel->rowCount(); i++)
	{
		FillMeasurementRow(i, tableModel, measurements);
		tableModel->setData(tableModel->index(i, 8), measurements.at(i)->GetSampleName());
		tableModel->itemFromIndex(tableModel->index(i, 8))->setTextAlignment(Qt::AlignBottom);
	}

	tableView->setColumnHidden(0, true);
}

void TableWriter::FillMeasurementsTable(QTableView* tableView, QString majorTableName, int majorTableId)
{
	QList<MeasurementContext*> measurements = DbReader::GetDbReaderInstance().ReadMeasurementsFromDatabase(majorTableName, majorTableId);
	FFSTableModel* tableModel = (FFSTableModel*)tableView->model();
	tableModel->setRowCount(measurements.length());
	tableModel->setColumnCount(8);

	for (int j = 0; j < tableModel->columnCount(); j++)
	{
		tableModel->setHeaderData(j, Qt::Horizontal, measurementColumnNames.at(j));
	}

	for (int i = 0; i < tableModel->rowCount(); i++)
	{
		FillMeasurementRow(i, tableModel, measurements);
	}

	tableView->setColumnHidden(0, true);
}

void TableWriter::FillSamplesTable(QTableView* tableView)
{
	QList<SampleContext*> samples = DbReader::GetDbReaderInstance().ReadSamplesFromDatabase();
	FFSTableModel* tableModel = (FFSTableModel*)tableView->model();
	tableModel->setRowCount(samples.length());
	tableModel->setColumnCount(3);

	for (int j = 0; j < tableModel->columnCount(); j++)
	{
		tableModel->setHeaderData(j, Qt::Horizontal, sampleColumnNames.at(j));
	}

	for (int i = 0; i < tableModel->rowCount(); i++)
	{
		tableModel->setData(tableModel->index(i, 0), samples.at(i)->GetId());
		tableModel->setData(tableModel->index(i, 1), samples.at(i)->GetName());
		tableModel->itemFromIndex(tableModel->index(i, 1))->setTextAlignment(Qt::AlignBottom);
		tableModel->setData(tableModel->index(i, 2), samples.at(i)->GetDescription());
		tableModel->itemFromIndex(tableModel->index(i, 2))->setTextAlignment(Qt::AlignBottom);
	}

	tableView->setColumnHidden(0, true);
}

void TableWriter::FillEquipmentsTable(QTableView* tableView, QString majorTableName, int majorTableId)
{
	QList<BindingContext*> bindings = DbReader::GetDbReaderInstance().ReadBindingsFromDatabase(majorTableName, majorTableId);
	QList<EquipmentContext*> equipments;

	foreach(BindingContext * binding, bindings)
	{
		QString sqlReadRequest = "SELECT * FROM equipments WHERE id = %1";
		QSqlQuery query = DbReader::GetDbReaderInstance().ReadFromDatabase(sqlReadRequest.arg(binding->GetFKEquipment()));

		if (query.next())
		{
			int id = query.value(0).toInt();
			EquipmentContext* equipment = new EquipmentContext(id);
			equipment->SetName(query.value(1).toString().trimmed());
			equipment->SetDescription(query.value(2).toString().trimmed());
			equipments.append(equipment);
		}
	}

	FillEquipmentsTable(tableView, equipments);
}

void TableWriter::FillEquipmentsTable(QTableView* tableView, QList<EquipmentContext*> equipments)
{
	FFSTableModel* tableModel = (FFSTableModel*)tableView->model();
	tableModel->setRowCount(equipments.length());
	tableModel->setColumnCount(3);

	for (int j = 0; j < tableModel->columnCount(); j++)
	{
		tableModel->setHeaderData(j, Qt::Horizontal, equipmentColumnNames.at(j));
	}

	for (int i = 0; i < tableModel->rowCount(); i++)
	{
		QString equipmentName = equipments.at(i)->GetName();
		int amountOfEquipmentWithEqualName = tableModel->getColumnItemsThatContainValue(1, equipmentName).length();

		if (amountOfEquipmentWithEqualName > 0)
		{
			equipmentName += " (" + QString::number(amountOfEquipmentWithEqualName) + ")";
		}

		tableModel->setData(tableModel->index(i, 0), equipments.at(i)->GetId());
		tableModel->setData(tableModel->index(i, 1), equipmentName);
		tableModel->itemFromIndex(tableModel->index(i, 1))->setTextAlignment(Qt::AlignBottom);
		tableModel->setData(tableModel->index(i, 2), equipments.at(i)->GetDescription());
		tableModel->itemFromIndex(tableModel->index(i, 2))->setTextAlignment(Qt::AlignBottom);
	}

	tableView->setColumnHidden(0, true);
}

void TableWriter::FillExistingEquipmentTable(EquipmentAddForm* view, int fk_measuring_system)
{
	FFSTableModel* allEquipmentTableModel = view->GetAllEquipmentTableModel();
	FFSTableModel* chosenEquipmentTableModel = view->GetChosenEquipmentTableModel();
	QList<EquipmentContext*> existingEquipment = DbReader::GetDbReaderInstance().ReadExistingEquipmentFromDatabase(fk_measuring_system);
	QList<EquipmentContext*> bindedEquipment = DbReader::GetDbReaderInstance().ReadBindedEquipmentFromDatabase(fk_measuring_system);
	allEquipmentTableModel->setRowCount(existingEquipment.length());
	allEquipmentTableModel->setColumnCount(3);
	chosenEquipmentTableModel->setRowCount(bindedEquipment.length());
	chosenEquipmentTableModel->setColumnCount(3);

	for (int j = 0; j < allEquipmentTableModel->columnCount(); j++)
	{
		allEquipmentTableModel->setHeaderData(j, Qt::Horizontal, equipmentColumnNames.at(j));
		chosenEquipmentTableModel->setHeaderData(j, Qt::Horizontal, equipmentColumnNames.at(j));
	}
	
	for (int i = 0; i < allEquipmentTableModel->rowCount(); i++)
	{
		QString equipmentName = existingEquipment.at(i)->GetName();
		int amountOfExistingEquipmentWithEqualName = allEquipmentTableModel->getColumnItemsThatContainValue(1, equipmentName).length();

		if (amountOfExistingEquipmentWithEqualName > 0)
		{
			equipmentName += " (" + QString::number(amountOfExistingEquipmentWithEqualName) + ")";
		}
		
		allEquipmentTableModel->setData(allEquipmentTableModel->index(i, 0), existingEquipment.at(i)->GetId());
		allEquipmentTableModel->setData(allEquipmentTableModel->index(i, 1), equipmentName);
		allEquipmentTableModel->itemFromIndex(allEquipmentTableModel->index(i, 1))->setTextAlignment(Qt::AlignBottom);
		allEquipmentTableModel->setData(allEquipmentTableModel->index(i, 2), existingEquipment.at(i)->GetDescription());
		allEquipmentTableModel->itemFromIndex(allEquipmentTableModel->index(i, 2))->setTextAlignment(Qt::AlignBottom);
	}

	view->GetUI().allEquipmentTable->setColumnHidden(0, true);

	for (int i = 0; i < chosenEquipmentTableModel->rowCount(); i++)
	{
		QString equipmentName = bindedEquipment.at(i)->GetName();
		int amountOfBindedEquipmentWithEqualName = chosenEquipmentTableModel->getColumnItemsThatContainValue(1, equipmentName).length();
		int amountOfExistingEquipmentWithEqualName = allEquipmentTableModel->getColumnItemsThatContainValue(1, equipmentName).length();
		amountOfBindedEquipmentWithEqualName += amountOfExistingEquipmentWithEqualName;

		if (amountOfBindedEquipmentWithEqualName > 0)
		{
			equipmentName += " (" + QString::number(amountOfBindedEquipmentWithEqualName) + ")";
		}
		
		chosenEquipmentTableModel->setData(chosenEquipmentTableModel->index(i, 0), bindedEquipment.at(i)->GetId());
		chosenEquipmentTableModel->setData(chosenEquipmentTableModel->index(i, 1), equipmentName);
		chosenEquipmentTableModel->itemFromIndex(chosenEquipmentTableModel->index(i, 1))->setTextAlignment(Qt::AlignBottom);
		chosenEquipmentTableModel->setData(chosenEquipmentTableModel->index(i, 2), bindedEquipment.at(i)->GetDescription());
		chosenEquipmentTableModel->itemFromIndex(chosenEquipmentTableModel->index(i, 2))->setTextAlignment(Qt::AlignBottom);
	}

	view->GetUI().chosenEquipmentTable->setColumnHidden(0, true);
}

void TableWriter::FillParametersTable(QTableView* tableView, QString majorTableName, QString minorTableName, int majorTableId)
{
	QList<ParameterTableContext*> parameters = DbReader::GetDbReaderInstance().ReadParametersFromDatabase(majorTableName, minorTableName, majorTableId);
	FFSTableModel* tableModel = (FFSTableModel*)tableView->model();
	tableModel->setRowCount(parameters.length());
	tableModel->setColumnCount(3);

	for (int i = 0, j = 0; i < tableModel->rowCount() || j < tableModel->columnCount(); i++, j++)
	{
		if (j < tableModel->columnCount())
		{
			tableModel->setHeaderData(j, Qt::Horizontal, parametersColumnNames.at(j));
		}

		if (i < tableModel->rowCount())
		{
			tableModel->setData(tableModel->index(i, 0), parameters.at(i)->GetId());
			tableModel->setData(tableModel->index(i, 1), parameters.at(i)->GetName());
			tableModel->itemFromIndex(tableModel->index(i, 1))->setTextAlignment(Qt::AlignBottom);
			tableModel->setData(tableModel->index(i, 2), parameters.at(i)->GetValue());
			tableModel->itemFromIndex(tableModel->index(i, 2))->setTextAlignment(Qt::AlignBottom);
		}
	}

	
	tableView->setColumnHidden(0, true);
}

void TableWriter::FillCharacteristicsTable(QTableView* tableView)
{
	QList<CharacteristicsContext*> characteristics = DbReader::GetDbReaderInstance().ReadCharacteristicsFromDatabase();
	FillBaseCharacteristicsTable(tableView, characteristics);
}

void TableWriter::FillCharacteristicsTable(QTableView* tableView, QString majorTableName, int majorTableId)
{
	QList<CharacteristicsContext*> characteristics = DbReader::GetDbReaderInstance().ReadCharacteristicsFromDatabase(majorTableName, majorTableId);
	FillBaseCharacteristicsTable(tableView, characteristics);

	if (majorTableName == "characteristic_type")
	{
		tableView->setColumnHidden(6, true);
	}
	else
	{
		tableView->setColumnHidden(1, true);
	}
}

void TableWriter::FillCharacteristicTypesTable(QTableView* tableView)
{
	QList<CharacteristicTypeContext*> characteristicTypes = DbReader::GetDbReaderInstance().ReadCharacteristicTypesFromDatabase();
	FFSTableModel* tableModel = (FFSTableModel*)tableView->model();
	tableModel->setRowCount(characteristicTypes.length());
	tableModel->setColumnCount(3);

	for (int j = 0; j < tableModel->columnCount(); j++)
	{
		tableModel->setHeaderData(j, Qt::Horizontal, characteristicTypeColumnNames.at(j));
	}

	for (int i = 0; i < tableModel->rowCount(); i++)
	{
		tableModel->setData(tableModel->index(i, 0), characteristicTypes.at(i)->GetId());
		tableModel->setData(tableModel->index(i, 1), characteristicTypes.at(i)->GetName());
		tableModel->itemFromIndex(tableModel->index(i, 1))->setTextAlignment(Qt::AlignBottom);
		tableModel->setData(tableModel->index(i, 2), characteristicTypes.at(i)->GetDescription());
		tableModel->itemFromIndex(tableModel->index(i, 2))->setTextAlignment(Qt::AlignBottom);
	}

	tableView->setColumnHidden(0, true);
}

void TableWriter::FillMeasurementRow(int rowNumber, FFSTableModel* tableModel, QList<MeasurementContext*> measurements)
{
	QDateTime DateTime;
	tableModel->setData(tableModel->index(rowNumber, 0), measurements.at(rowNumber)->GetId());
	tableModel->setData(tableModel->index(rowNumber, 1), measurements.at(rowNumber)->GetName());
	tableModel->itemFromIndex(tableModel->index(rowNumber, 1))->setTextAlignment(Qt::AlignBottom);
	tableModel->setData(tableModel->index(rowNumber, 2), DateTime.fromString(measurements.at(rowNumber)->GetDateTime(), "H:m:s M/d/yyyy"));
	tableModel->itemFromIndex(tableModel->index(rowNumber, 2))->setTextAlignment(Qt::AlignBottom);
	tableModel->setData(tableModel->index(rowNumber, 3), measurements.at(rowNumber)->GetFileLink().split('/').last());
	tableModel->itemFromIndex(tableModel->index(rowNumber, 3))->setTextAlignment(Qt::AlignBottom);
	tableModel->setData(tableModel->index(rowNumber, 4), measurements.at(rowNumber)->GetRepeatCount());
	tableModel->itemFromIndex(tableModel->index(rowNumber, 4))->setTextAlignment(Qt::AlignBottom);
	tableModel->setData(tableModel->index(rowNumber, 5), measurements.at(rowNumber)->GetKineticsCount());
	tableModel->itemFromIndex(tableModel->index(rowNumber, 5))->setTextAlignment(Qt::AlignBottom);
	tableModel->setData(tableModel->index(rowNumber, 6), measurements.at(rowNumber)->GetNumberOfChannels());
	tableModel->itemFromIndex(tableModel->index(rowNumber, 6))->setTextAlignment(Qt::AlignBottom);
	tableModel->setData(tableModel->index(rowNumber, 7), measurements.at(rowNumber)->GetNumberPositions());
	tableModel->itemFromIndex(tableModel->index(rowNumber, 7))->setTextAlignment(Qt::AlignBottom);
}

void TableWriter::FillCharacteristicsRow(int rowNumber, FFSTableModel* tableModel, QList<CharacteristicsContext*> characteristics)
{
	tableModel->setData(tableModel->index(rowNumber, 0), characteristics.at(rowNumber)->GetId());
	tableModel->setData(tableModel->index(rowNumber, 1), characteristics.at(rowNumber)->GetName());
	tableModel->itemFromIndex(tableModel->index(rowNumber, 1))->setTextAlignment(Qt::AlignBottom);
	tableModel->setData(tableModel->index(rowNumber, 2), characteristics.at(rowNumber)->GetChannel());
	tableModel->itemFromIndex(tableModel->index(rowNumber, 2))->setTextAlignment(Qt::AlignBottom);
	tableModel->setData(tableModel->index(rowNumber, 3), characteristics.at(rowNumber)->GetNumberOfPoints());
	tableModel->itemFromIndex(tableModel->index(rowNumber, 3))->setTextAlignment(Qt::AlignBottom);
	tableModel->setData(tableModel->index(rowNumber, 4), QString::number(characteristics.at(rowNumber)->GetBinTime(), 'f', 4)
		.remove(QRegExp("0+$"))
		.remove(QRegExp("[.]$"))
		.toDouble());
	tableModel->itemFromIndex(tableModel->index(rowNumber, 4))->setTextAlignment(Qt::AlignBottom);
	tableModel->setData(tableModel->index(rowNumber, 5), QString::number(characteristics.at(rowNumber)->GetWeight(), 'f', 4)
		.remove(QRegExp("0+$"))
		.remove(QRegExp("[.]$"))
		.toDouble());
	tableModel->itemFromIndex(tableModel->index(rowNumber, 5))->setTextAlignment(Qt::AlignBottom);
	tableModel->setData(tableModel->index(rowNumber, 6), characteristics.at(rowNumber)->GetCharacteristicTypeName());
	tableModel->itemFromIndex(tableModel->index(rowNumber, 6))->setTextAlignment(Qt::AlignBottom);
}

void TableWriter::FillBaseCharacteristicsTable(QTableView* tableView, QList<CharacteristicsContext*> characteristics)
{
	TableItemDelegate* decDelegate = new TableItemDelegate(tableView);
	tableView->setItemDelegateForColumn(3, decDelegate);
	tableView->setItemDelegateForColumn(4, decDelegate);
	FFSTableModel* tableModel = (FFSTableModel*)tableView->model();
	tableModel->setRowCount(characteristics.length());
	tableModel->setColumnCount(7);

	for (int i = 0, j = 0; i < tableModel->rowCount() || j < tableModel->columnCount(); i++, j++)
	{
		if (j < tableModel->columnCount())
		{
			tableModel->setHeaderData(j, Qt::Horizontal, characteristicsColumnNames.at(j));
		}

		if (i < tableModel->rowCount())
		{
			FillCharacteristicsRow(i, tableModel, characteristics);
		}
	}

	tableView->setColumnHidden(0, true);
}

void TableWriter::RouteMajorRequest(QString tableName, QTableView* tableView)
{
	if (tableName == "measuring system")
	{
		FillMeasuringSystemsTable(tableView);
	}
	else if (tableName == "sample")
	{
		FillSamplesTable(tableView);
	}
	else if (tableName == "equipment")
	{
		FillEquipmentsTable(tableView);
	}
	else if (tableName == "measurement")
	{
		FillMeasurementsTable(tableView);
	}
	else if (tableName == "characteristic type")
	{
		FillCharacteristicTypesTable(tableView);
	}
	else if (tableName == "characteristic")
	{
		FillCharacteristicsTable(tableView);
	}
}

void TableWriter::RouteRequest(Ui::FFSDatabaseInterfaceClass ui, QTableView* tableView, QString majorTableName, QString minorTableName, int majorTableId)
{
	if (minorTableName.contains("parameters"))
	{
		FillParametersTable(tableView, majorTableName, minorTableName, majorTableId);
	}
	else if (minorTableName == "equipments")
	{
		FillEquipmentsTable(tableView, majorTableName, majorTableId);
		ui.minorSubtableView->setDisabled(false);
		ui.minorTableSelector->setDisabled(false);
		ui.minorTableSelector->clear();
		ui.minorTableSelector->addItem("Equipment parameters");
	}
	else if (minorTableName == "measurements")
	{
		FillMeasurementsTable(tableView, majorTableName, majorTableId);
		ui.minorSubtableView->setDisabled(false);
		ui.minorTableSelector->setDisabled(false);
		ui.minorTableSelector->clear();
		ui.minorTableSelector->addItem("Measurement parameters");
		ui.minorTableSelector->addItem("Characteristics");
	}
	else if (minorTableName == "measuring_systems")
	{
		FillMeasuringSystemsTable(tableView, majorTableName, majorTableId);
	}
	else if (minorTableName == "characteristics")
	{
		FillCharacteristicsTable(tableView, majorTableName, majorTableId);
	}
}