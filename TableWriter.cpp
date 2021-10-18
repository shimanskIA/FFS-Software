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
			tableModel->setData(tableModel->index(i, 2), measurements.at(i)->GetDateTime());
			tableModel->setData(tableModel->index(i, 3), measurements.at(i)->GetFileLink());
			tableModel->setData(tableModel->index(i, 4), measurements.at(i)->GetRepeatCount());
			tableModel->setData(tableModel->index(i, 5), measurements.at(i)->GetKineticsCount());
			tableModel->setData(tableModel->index(i, 6), measurements.at(i)->GetNumberOfChannels());
			tableModel->setData(tableModel->index(i, 7), measurements.at(i)->GetNumberPositions());
			tableModel->setData(tableModel->index(i, 8), measurements.at(i)->GetSampleName());
		}
	}	
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
			tableModel->setData(tableModel->index(i, 2), samples.at(i)->GetDescription());
		}
	}
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
			tableModel->setData(tableModel->index(i, 2), equipments.at(i)->GetDescription());
		}
	}
}