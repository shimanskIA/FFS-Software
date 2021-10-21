#include "TableWriter.h"
#include "DbConnection.h"

#include <QStandardItemModel>

TableWriter::TableWriter()
{

}

void TableWriter::FillMeasuringSystemsTable(Ui::FFSDatabaseInterfaceClass ui)
{
	QList<MeasuringSystemContext*> measuringSystems = DbConnection::GetDbConnectionInstance().ReadMeasuringSystemsFromDatabase();
	QStandardItemModel* tableModel = new QStandardItemModel(measuringSystems.length(), 4);
	ui.majorTableView->setModel(tableModel);

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

	ui.majorTableView->setColumnHidden(0, true);
}

void TableWriter::FillMeasuringSystemsTable(Ui::FFSDatabaseInterfaceClass ui, QString majorTableName, int majorTableId)
{
	QList<BindingContext*> bindings = DbConnection::GetDbConnectionInstance().ReadBindingsFromDatabase(majorTableName, majorTableId);
	QList<MeasuringSystemContext*> measuringSystems;

	foreach(BindingContext * binding, bindings)
	{
		QString sqlReadRequest = "SELECT * FROM measuring_systems WHERE id = %1";
		QSqlQuery query = DbConnection::GetDbConnectionInstance().ReadFromDatabase(sqlReadRequest.arg(binding->GetFKMeasuringSystem()));

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

	QStandardItemModel* tableModel = new QStandardItemModel(measuringSystems.length(), 4);
	ui.minorTableView->setModel(tableModel);

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
		tableModel->setData(tableModel->index(i, 2), measuringSystems.at(i)->GetMainContributorName());
		tableModel->itemFromIndex(tableModel->index(i, 2))->setTextAlignment(Qt::AlignBottom);
	}

	ui.minorTableView->setColumnHidden(0, true);
}

void TableWriter::FillMeasurementsTable(Ui::FFSDatabaseInterfaceClass ui)
{
	QList<MeasurementContext*> measurements = DbConnection::GetDbConnectionInstance().ReadMeasurementsFromDatabase();
	QStandardItemModel* tableModel = new QStandardItemModel(measurements.length(), 9);
	ui.majorTableView->setModel(tableModel);

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

	ui.majorTableView->setColumnHidden(0, true);
}

void TableWriter::FillSamplesTable(Ui::FFSDatabaseInterfaceClass ui)
{
	QList<SampleContext*> samples = DbConnection::GetDbConnectionInstance().ReadSamplesFromDatabase();
	QStandardItemModel* tableModel = new QStandardItemModel(samples.length(), 3);
	ui.majorTableView->setModel(tableModel);

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

	ui.majorTableView->setColumnHidden(0, true);
}

void TableWriter::FillEquipmentsTable(Ui::FFSDatabaseInterfaceClass ui)
{
	QList<EquipmentContext*> equipments = DbConnection::GetDbConnectionInstance().ReadEquipmentsFromDatabase();
	QStandardItemModel* tableModel = new QStandardItemModel(equipments.length(), 3);
	ui.majorTableView->setModel(tableModel);

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

	ui.majorTableView->setColumnHidden(0, true);
}

void TableWriter::FillMeasurementsTable(Ui::FFSDatabaseInterfaceClass ui, QString majorTableName, int majorTableId)
{
	QList<MeasurementContext*> measurements = DbConnection::GetDbConnectionInstance().ReadMeasurementsFromDatabase(majorTableName, majorTableId);
	QStandardItemModel* tableModel = new QStandardItemModel(measurements.length(), 8);
	ui.minorTableView->setModel(tableModel);

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

	ui.minorTableView->setColumnHidden(0, true);
}

void TableWriter::FillEquipmentsTable(Ui::FFSDatabaseInterfaceClass ui, QString majorTableName, int majorTableId)
{
	QList<BindingContext*> bindings = DbConnection::GetDbConnectionInstance().ReadBindingsFromDatabase(majorTableName, majorTableId);
	QList<EquipmentContext*> equipments;

	foreach(BindingContext* binding, bindings)
	{
		QString sqlReadRequest = "SELECT * FROM equipments WHERE id = %1";
		QSqlQuery query = DbConnection::GetDbConnectionInstance().ReadFromDatabase(sqlReadRequest.arg(binding->GetFKEquipment()));

		if (query.next())
		{
			int id = query.value(0).toInt();
			EquipmentContext* equipment = new EquipmentContext(id);
			equipment->SetName(query.value(1).toString().trimmed());
			equipment->SetDescription(query.value(2).toString().trimmed());
			equipments.append(equipment);
		}
	}

	QStandardItemModel* tableModel = new QStandardItemModel(equipments.length(), 3);
	ui.minorTableView->setModel(tableModel);

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

	ui.minorTableView->setColumnHidden(0, true);
}

void TableWriter::FillParametersTable(Ui::FFSDatabaseInterfaceClass ui, QString majorTableName, QString minorTableName, int majorTableId)
{
	QList<ParameterTableContext*> parameters = DbConnection::GetDbConnectionInstance().ReadParametersFromDatabase(majorTableName, minorTableName, majorTableId);
	QStandardItemModel* tableModel = new QStandardItemModel(parameters.length(), 3);
	ui.minorTableView->setModel(tableModel);

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

	ui.minorTableView->setColumnHidden(0, true);
}

void TableWriter::FillCharacteristicsTable(Ui::FFSDatabaseInterfaceClass ui, int majorTableId)
{
	QList<CharacteristicsContext*> characteristics = DbConnection::GetDbConnectionInstance().ReadCharacteristicsFromDatabase(majorTableId);
	QStandardItemModel* tableModel = new QStandardItemModel(characteristics.length(), 6);
	ui.minorTableView->setModel(tableModel);

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
			tableModel->setData(tableModel->index(i, 2), characteristics.at(i)->GetNumberOfPoints());
			tableModel->itemFromIndex(tableModel->index(i, 2))->setTextAlignment(Qt::AlignBottom);
			tableModel->setData(tableModel->index(i, 3), QString::number(characteristics.at(i)->GetBinTime(), 'f', 3));
			tableModel->itemFromIndex(tableModel->index(i, 3))->setTextAlignment(Qt::AlignBottom);
			tableModel->setData(tableModel->index(i, 4), QString::number(characteristics.at(i)->GetWeight(), 'f', 3));
			tableModel->itemFromIndex(tableModel->index(i, 4))->setTextAlignment(Qt::AlignBottom);
			tableModel->setData(tableModel->index(i, 5), characteristics.at(i)->GetCharacteristicTypeName());
			tableModel->itemFromIndex(tableModel->index(i, 5))->setTextAlignment(Qt::AlignBottom);
		}
	}

	ui.minorTableView->setColumnHidden(0, true);
}

void TableWriter::FillMeasurementRow(int rowNumber, QStandardItemModel* tableModel, QList<MeasurementContext*> measurements)
{
	tableModel->setData(tableModel->index(rowNumber, 0), measurements.at(rowNumber)->GetId());
	tableModel->setData(tableModel->index(rowNumber, 1), measurements.at(rowNumber)->GetName());
	tableModel->itemFromIndex(tableModel->index(rowNumber, 1))->setTextAlignment(Qt::AlignBottom);
	tableModel->setData(tableModel->index(rowNumber, 2), measurements.at(rowNumber)->GetDateTime());
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

void TableWriter::RouteRequest(Ui::FFSDatabaseInterfaceClass ui, QString majorTableName, QString minorTableName, int majorTableId)
{
	if (minorTableName == "equipment_parameters")
	{
		FillParametersTable(ui, majorTableName, minorTableName, majorTableId);
	}
	else if (minorTableName == "equipments")
	{
		FillEquipmentsTable(ui, majorTableName, majorTableId);
	}
	else if (minorTableName == "measurements")
	{
		FillMeasurementsTable(ui, majorTableName, majorTableId);
	}
	else if (minorTableName == "measuring_systems")
	{
		FillMeasuringSystemsTable(ui, majorTableName, majorTableId);
	}
	else
	{

	}
}