#pragma once

#include <QTableView>

class RowManager
{
public:
	static RowManager& GetRowManagerInstance();

	void FilterRowsByKeyword(QTableView* tableView, QString keyword);
	void FilterRowsByKeyword(QTableView* tableView, QString keyword, int columnIndex);
	void AdvancedFilterRowsByRequest(QTableView* tableView, QString request);
	void ShowAllRows(QTableView* tableView);
	void HideAllRows(QTableView* tableView);

private:
	RowManager() {};
	RowManager(const RowManager&) {}
};
