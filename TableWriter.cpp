#include "TableWriter.h"
#include "DbConnection.h"

#include <QStandardItemModel>

TableWriter::TableWriter()
{

}

void TableWriter::FillMeasurementsTable(Ui::FFSDatabaseInterfaceClass ui)
{
	QList<MeasurementContext*> measurements = DbConnection::GetDbConnectionInstance().ReadMeasurementsFromDatabase();
	QStandardItemModel* tableModel = new QStandardItemModel(measurements.length(), 8);
	ui.majorTableView->setModel(tableModel);

	for (int i = 0, j = 0; j < tableModel->columnCount(); i++, j++)
	{
		tableModel->setHeaderData(j, Qt::Horizontal, measurementColumnNames.at(j));
		if (i < tableModel->rowCount())
		{
			tableModel->setData(tableModel->index(i, 0), measurements.at(i)->GetName());
			tableModel->setData(tableModel->index(i, 1), measurements.at(i)->GetDateTime());
			tableModel->setData(tableModel->index(i, 2), measurements.at(i)->GetFileLink());
			tableModel->setData(tableModel->index(i, 3), measurements.at(i)->GetRepeatCount());
			tableModel->setData(tableModel->index(i, 4), measurements.at(i)->GetKineticsCount());
			tableModel->setData(tableModel->index(i, 5), measurements.at(i)->GetNumberOfChannels());
			tableModel->setData(tableModel->index(i, 6), measurements.at(i)->GetNumberPositions());
			tableModel->setData(tableModel->index(i, 7), measurements.at(i)->GetSampleName());
		}
	}	
}