#include "BaseDependentAddForm.h"

#include <QHeaderView>

BaseDependentAddForm::BaseDependentAddForm(QWidget* parent) : BaseAddForm(parent)
{

}

void BaseDependentAddForm::SetTableSettings(QTableView* table)
{
	table->setColumnHidden(0, true);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	table->horizontalHeader()->setStretchLastSection(true);
	table->verticalHeader()->setDefaultSectionSize(20);
	table->verticalHeader()->sectionResizeMode(QHeaderView::Fixed);
	table->setStyleSheet(
		"QHeaderView::section { background-color: rgb(217, 217, 217)}"
		"QTableView {selection-background-color: steelblue}");
}