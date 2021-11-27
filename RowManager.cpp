#include "RowManager.h"
#include "FFSTableModel.h"

#include <QHeaderView>

RowManager& RowManager::GetRowManagerInstance()
{
	static RowManager* windowManagerInstance = 0;

	if (windowManagerInstance == 0)
	{
		windowManagerInstance = new RowManager();
	}

	return *windowManagerInstance;
}

void RowManager::FilterRowsByKeyword(QTableView* tableView, QString keyword)
{
	FFSTableModel* model = (FFSTableModel*)tableView->model();
	
	for (int i = 0; i < model->rowCount(); i++)
	{
		bool containsEqual = false;

		for (int j = 0; j < model->columnCount(); j++)
		{
			if (model->index(i, j).data().toString().toLower().contains(keyword.toLower()))
			{
				containsEqual = true;
				break;
			}
		}

		if (!containsEqual)
		{
			tableView->hideRow(i);
		}
	}

	tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	tableView->horizontalHeader()->setStretchLastSection(true);
}

void RowManager::FilterRowsByKeyword(QTableView* tableView, QString keyword, int columnIndex)
{
	FFSTableModel* model = (FFSTableModel*)tableView->model();

	for (int i = 0; i < model->rowCount(); i++)
	{
		if (!model->index(i, columnIndex).data().toString().toLower().contains(keyword.toLower()))
		{
			tableView->hideRow(i);
		}
	}

	tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	tableView->horizontalHeader()->setStretchLastSection(true);
}

void RowManager::AdvancedFilterRowsByRequest(QTableView* tableView, QString request)
{
	FFSTableModel* model = (FFSTableModel*)tableView->model();
	QStringList singleRequests = request.split(',');

	foreach (QString singleRequest, singleRequests)
	{
		singleRequest = singleRequest.trimmed();
		QStringList nameValuePair = singleRequest.split(':');
		QString columnName = nameValuePair.first().trimmed();
		QString searchedValue = nameValuePair.last().trimmed();
		int searchedColumn = -1;

		for (int j = 0; j < model->columnCount(); j++)
		{
			if (columnName.toLower() == model->headerData(j, Qt::Horizontal).toString().toLower())
			{
				searchedColumn = j;
				break;
			}
		}

		if (searchedColumn == -1)
		{
			HideAllRows(tableView);
			return;
		}

		auto columnType = model->index(1, searchedColumn).data().type();

		if (columnType == QVariant::Type::Int ||
			columnType == QVariant::Type::UInt ||
			columnType == QVariant::Type::Double || 
			columnType == QVariant::Type::LongLong || 
			columnType == QVariant::Type::ULongLong)
		{

		}
		else if (
			columnType == QVariant::Type::String ||
			columnType == QVariant::Type::Char)
		{
			FilterRowsByKeyword(tableView, searchedValue, searchedColumn);
		}
		else if (
			columnType == columnType == QVariant::Type::Date ||
			columnType == columnType == QVariant::Type::DateTime)
		{

		}
	}
}

void RowManager::ShowAllRows(QTableView* tableView)
{
	FFSTableModel* model = (FFSTableModel*)tableView->model();

	for (int i = 0; i < model->rowCount(); i++)
	{
		tableView->showRow(i);
	}
}

void RowManager::HideAllRows(QTableView* tableView)
{
	FFSTableModel* model = (FFSTableModel*)tableView->model();

	for (int i = 0; i < model->rowCount(); i++)
	{
		tableView->hideRow(i);
	}
}