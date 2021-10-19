#include "TableWriter.h"
#include "DbConnection.h"

#include <QStandardItemModel>

TableWriter::TableWriter()
{

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
			tableModel->setData(tableModel->index(i, 0), measurements.at(i)->GetId());
			tableModel->setData(tableModel->index(i, 1), measurements.at(i)->GetName());
			tableModel->itemFromIndex(tableModel->index(i, 1))->setTextAlignment(Qt::AlignBottom);
			tableModel->setData(tableModel->index(i, 2), measurements.at(i)->GetDateTime());
			tableModel->itemFromIndex(tableModel->index(i, 2))->setTextAlignment(Qt::AlignBottom);
			tableModel->setData(tableModel->index(i, 3), measurements.at(i)->GetFileLink().split('/').last());
			tableModel->itemFromIndex(tableModel->index(i, 3))->setTextAlignment(Qt::AlignBottom);
			tableModel->setData(tableModel->index(i, 4), measurements.at(i)->GetRepeatCount());
			tableModel->itemFromIndex(tableModel->index(i, 4))->setTextAlignment(Qt::AlignBottom);
			tableModel->setData(tableModel->index(i, 5), measurements.at(i)->GetKineticsCount());
			tableModel->itemFromIndex(tableModel->index(i, 5))->setTextAlignment(Qt::AlignBottom);
			tableModel->setData(tableModel->index(i, 6), measurements.at(i)->GetNumberOfChannels());
			tableModel->itemFromIndex(tableModel->index(i, 6))->setTextAlignment(Qt::AlignBottom);
			tableModel->setData(tableModel->index(i, 7), measurements.at(i)->GetNumberPositions());
			tableModel->itemFromIndex(tableModel->index(i, 7))->setTextAlignment(Qt::AlignBottom);
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

}

void TableWriter::FillEquipmentsTable(Ui::FFSDatabaseInterfaceClass ui, QString majorTableName, int majorTableId)
{

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

void TableWriter::RouteRequest(Ui::FFSDatabaseInterfaceClass ui, QString majorTableName, QString minorTableName, int majorTableId)
{
	if (minorTableName.contains("parameters"))
	{
		FillParametersTable(ui, majorTableName, minorTableName, majorTableId);
	}
	else if (minorTableName == "characteristics")
	{
		FillCharacteristicsTable(ui, majorTableId);
	}
	else if (minorTableName == "equipments")
	{
		FillEquipmentsTable(ui, majorTableName, majorTableId);
	}
	else if (minorTableName == "measurements")
	{
		FillMeasurementsTable(ui, majorTableName, majorTableId);
	}
}