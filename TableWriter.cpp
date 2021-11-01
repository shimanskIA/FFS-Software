#include "TableWriter.h"
#include "TableItemDelegate.h"

#include <QStandardItemModel>

TableWriter::TableWriter()
{
	dbReader = new DbReader();
}

void TableWriter::FillMeasuringSystemsTable(QTableView* tableView)
{
	QList<MeasuringSystemContext*> measuringSystems = dbReader->ReadMeasuringSystemsFromDatabase();
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
	DbReader* dbReader = new DbReader();
	QList<BindingContext*> bindings = dbReader->ReadBindingsFromDatabase(majorTableName, majorTableId);
	QList<MeasuringSystemContext*> measuringSystems;

	foreach(BindingContext * binding, bindings)
	{
		QString sqlReadRequest = "SELECT * FROM measuring_systems WHERE id = %1";
		QSqlQuery query = dbReader->ReadFromDatabase(sqlReadRequest.arg(binding->GetFKMeasuringSystem()));

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
	QList<MeasurementContext*> measurements = dbReader->ReadMeasurementsFromDatabase();
	FFSTableModel* tableModel = (FFSTableModel*)tableView->model();
	tableModel->setRowCount(measurements.length());
	tableModel->setColumnCount(9);

	for (int i = 0, j = 0; i < tableModel->rowCount() || j < tableModel->columnCount(); i++, j++)
	{
		if (j < tableModel->columnCount())
		{
			tableModel->setHeaderData(j, Qt::Horizontal, measurementColumnNames.at(j));
		}

		if (i < tableModel->rowCount())
		{
			FillMeasurementRow(i, tableModel, measurements);
			tableModel->setData(tableModel->index(i, 8), measurements.at(i)->GetSampleName());
			tableModel->itemFromIndex(tableModel->index(i, 8))->setTextAlignment(Qt::AlignBottom);
		}
	}	

	tableView->setColumnHidden(0, true);
}

void TableWriter::FillSamplesTable(QTableView* tableView)
{
	QList<SampleContext*> samples = dbReader->ReadSamplesFromDatabase();
	FFSTableModel* tableModel = (FFSTableModel*)tableView->model();
	tableModel->setRowCount(samples.length());
	tableModel->setColumnCount(3);

	for (int i = 0, j = 0; i < tableModel->rowCount() || j < tableModel->columnCount(); i++, j++)
	{
		if (j < tableModel->columnCount())
		{
			tableModel->setHeaderData(j, Qt::Horizontal, sampleColumnNames.at(j));
		}

		if (i < tableModel->rowCount())
		{
			tableModel->setData(tableModel->index(i, 0), samples.at(i)->GetId());
			tableModel->setData(tableModel->index(i, 1), samples.at(i)->GetName());
			tableModel->itemFromIndex(tableModel->index(i, 1))->setTextAlignment(Qt::AlignBottom);
			tableModel->setData(tableModel->index(i, 2), samples.at(i)->GetDescription());
			tableModel->itemFromIndex(tableModel->index(i, 2))->setTextAlignment(Qt::AlignBottom);
		}
	}

	tableView->setColumnHidden(0, true);
}

void TableWriter::FillEquipmentsTable(QTableView* tableView)
{
	QList<EquipmentContext*> equipments = dbReader->ReadEquipmentsFromDatabase();
	FFSTableModel* tableModel = (FFSTableModel*)tableView->model();
	tableModel->setRowCount(equipments.length());
	tableModel->setColumnCount(3);

	for (int i = 0, j = 0; i < tableModel->rowCount() || j < tableModel->columnCount(); i++, j++)
	{
		if (j < tableModel->columnCount())
		{
			tableModel->setHeaderData(j, Qt::Horizontal, equipmentColumnNames.at(j));
		}

		if (i < tableModel->rowCount())
		{
			tableModel->setData(tableModel->index(i, 0), equipments.at(i)->GetId());
			tableModel->setData(tableModel->index(i, 1), equipments.at(i)->GetName());
			tableModel->itemFromIndex(tableModel->index(i, 1))->setTextAlignment(Qt::AlignBottom);
			tableModel->setData(tableModel->index(i, 2), equipments.at(i)->GetDescription());
			tableModel->itemFromIndex(tableModel->index(i, 2))->setTextAlignment(Qt::AlignBottom);
		}
	}

	tableView->setColumnHidden(0, true);
}

void TableWriter::FillMeasurementsTable(QTableView* tableView, QString majorTableName, int majorTableId)
{
	QList<MeasurementContext*> measurements = dbReader->ReadMeasurementsFromDatabase(majorTableName, majorTableId);
	FFSTableModel* tableModel = (FFSTableModel*)tableView->model();
	tableModel->setRowCount(measurements.length());
	tableModel->setColumnCount(8);

	for (int i = 0, j = 0; i < tableModel->rowCount() || j < tableModel->columnCount(); i++, j++)
	{
		if (j < tableModel->columnCount())
		{
			tableModel->setHeaderData(j, Qt::Horizontal, measurementColumnNames.at(j));
		}

		if (i < tableModel->rowCount())
		{
			FillMeasurementRow(i, tableModel, measurements);
		}
	}

	tableView->setColumnHidden(0, true);
}

void TableWriter::FillEquipmentsTable(QTableView* tableView, QString majorTableName, int majorTableId)
{
	QList<BindingContext*> bindings = dbReader->ReadBindingsFromDatabase(majorTableName, majorTableId);
	QList<EquipmentContext*> equipments;

	foreach(BindingContext* binding, bindings)
	{
		QString sqlReadRequest = "SELECT * FROM equipments WHERE id = %1";
		QSqlQuery query = dbReader->ReadFromDatabase(sqlReadRequest.arg(binding->GetFKEquipment()));

		if (query.next())
		{
			int id = query.value(0).toInt();
			EquipmentContext* equipment = new EquipmentContext(id);
			equipment->SetName(query.value(1).toString().trimmed());
			equipment->SetDescription(query.value(2).toString().trimmed());
			equipments.append(equipment);
		}
	}

	FFSTableModel* tableModel = (FFSTableModel*)tableView->model();
	tableModel->setRowCount(equipments.length());
	tableModel->setColumnCount(3);

	for (int i = 0, j = 0; i < tableModel->rowCount() || j < tableModel->columnCount(); i++, j++)
	{
		if (j < tableModel->columnCount())
		{
			tableModel->setHeaderData(j, Qt::Horizontal, equipmentColumnNames.at(j));
		}

		if (i < tableModel->rowCount())
		{
			tableModel->setData(tableModel->index(i, 0), equipments.at(i)->GetId());
			tableModel->setData(tableModel->index(i, 1), equipments.at(i)->GetName());
			tableModel->itemFromIndex(tableModel->index(i, 1))->setTextAlignment(Qt::AlignBottom);
			tableModel->setData(tableModel->index(i, 2), equipments.at(i)->GetDescription());
			tableModel->itemFromIndex(tableModel->index(i, 2))->setTextAlignment(Qt::AlignBottom);
		}
	}

	tableView->setColumnHidden(0, true);
}

void TableWriter::FillParametersTable(QTableView* tableView, QString majorTableName, QString minorTableName, int majorTableId)
{
	QList<ParameterTableContext*> parameters = dbReader->ReadParametersFromDatabase(majorTableName, minorTableName, majorTableId);
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

void TableWriter::FillCharacteristicsTable(QTableView* tableView, QString sqlReadRequest)
{
	QList<CharacteristicsContext*> characteristics = dbReader->ReadCharacteristicsFromDatabase(sqlReadRequest);
	TableItemDelegate* decDelegate = new TableItemDelegate(tableView);
	tableView->setItemDelegateForColumn(3, decDelegate);
	tableView->setItemDelegateForColumn(4, decDelegate);
	FFSTableModel* tableModel = (FFSTableModel*)tableView->model();
	tableModel->setRowCount(characteristics.length());
	tableModel->setColumnCount(6);

	for (int i = 0, j = 0; i < tableModel->rowCount() || j < tableModel->columnCount(); i++, j++)
	{
		if (j < tableModel->columnCount())
		{
			tableModel->setHeaderData(j, Qt::Horizontal, characteristicsColumnNames.at(j));
		}

		if (i < tableModel->rowCount())
		{
			tableModel->setData(tableModel->index(i, 0), characteristics.at(i)->GetId());
			tableModel->setData(tableModel->index(i, 1), characteristics.at(i)->GetChannel());
			tableModel->itemFromIndex(tableModel->index(i, 1))->setTextAlignment(Qt::AlignBottom);
			tableModel->setData(tableModel->index(i, 2), (uint)characteristics.at(i)->GetNumberOfPoints());
			tableModel->itemFromIndex(tableModel->index(i, 2))->setTextAlignment(Qt::AlignBottom);
			tableModel->setData(tableModel->index(i, 3), QString::number(characteristics.at(i)->GetBinTime(), 'f', 4)
				.remove(QRegExp("0+$"))
				.remove(QRegExp("[.]$"))
				.toDouble());
			tableModel->itemFromIndex(tableModel->index(i, 3))->setTextAlignment(Qt::AlignBottom);
			tableModel->setData(tableModel->index(i, 4), QString::number(characteristics.at(i)->GetWeight(), 'f', 4)
				.remove(QRegExp("0+$"))
				.remove(QRegExp("[.]$"))
				.toDouble());
			tableModel->itemFromIndex(tableModel->index(i, 4))->setTextAlignment(Qt::AlignBottom);
			tableModel->setData(tableModel->index(i, 5), characteristics.at(i)->GetCharacteristicTypeName());
			tableModel->itemFromIndex(tableModel->index(i, 5))->setTextAlignment(Qt::AlignBottom);
		}
	}

	tableView->setColumnHidden(0, true);
}

void TableWriter::FillCharacteristicTypesTable(QTableView* tableView)
{
	QList<CharacteristicTypeContext*> characteristicTypes = dbReader->ReadCharacteristicTypesFromDatabase();
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
	tableModel->setData(tableModel->index(rowNumber, 4), (uint)measurements.at(rowNumber)->GetRepeatCount());
	tableModel->itemFromIndex(tableModel->index(rowNumber, 4))->setTextAlignment(Qt::AlignBottom);
	tableModel->setData(tableModel->index(rowNumber, 5), (uint)measurements.at(rowNumber)->GetKineticsCount());
	tableModel->itemFromIndex(tableModel->index(rowNumber, 5))->setTextAlignment(Qt::AlignBottom);
	tableModel->setData(tableModel->index(rowNumber, 6), (uint)measurements.at(rowNumber)->GetNumberOfChannels());
	tableModel->itemFromIndex(tableModel->index(rowNumber, 6))->setTextAlignment(Qt::AlignBottom);
	tableModel->setData(tableModel->index(rowNumber, 7), (uint)measurements.at(rowNumber)->GetNumberPositions());
	tableModel->itemFromIndex(tableModel->index(rowNumber, 7))->setTextAlignment(Qt::AlignBottom);
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
		QString sqlReadRequest = "SELECT * FROM characteristics";
		FillCharacteristicsTable(tableView, sqlReadRequest);
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
		QString sqlReadRequest = "SELECT * FROM characteristics WHERE fk_%1 = %2";
		FillCharacteristicsTable(tableView, sqlReadRequest.arg(majorTableName).arg(majorTableId));
	}
}