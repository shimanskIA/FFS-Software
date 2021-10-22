#pragma once

#include "ui_FFSDatabaseInterface.h"
#include "FFSDatabaseInterface.h"
#include "MeasurementContext.h"

#include <QString>
#include <QList>
#include <QStandardItemModel>

class TableWriter 
{
public:
	TableWriter();

	void FillMeasuringSystemsTable(QTableView* tableView);
	void FillMeasuringSystemsTable(QTableView* tableView, QString majorTableName, int majorTableId);

	void FillMeasurementsTable(QTableView* tableView);
	void FillMeasurementsTable(QTableView* tableView, QString majorTableName, int majorTableId);

	void FillSamplesTable(QTableView* tableView);

	void FillEquipmentsTable(QTableView* tableView);
	void FillEquipmentsTable(QTableView* tableView, QString majorTableName, int majorTableId);

	void FillCharacteristicTypesTable(QTableView* tableView);

	void FillParametersTable(QTableView* tableView, QString majorTableName, QString minorTableName, int majorTableId);

	void FillCharacteristicsTable(QTableView* tableView, QString sqlReadRequest);

	void FillMeasurementRow(int rowNumber, QStandardItemModel* tableModel, QList<MeasurementContext*> measurements);

	void RouteRequest(Ui::FFSDatabaseInterfaceClass ui, QTableView* tableView, QString majorTableName, QString minorTableName, int majorTableId);

private:
	const QStringList measurementColumnNames = {
		"Id",
		"Name",
		"Date",
		"File",
		"Repeat count",
		"Kinetics count",
		"Number of channels",
		"Number positions",
		"Sample" };

	const QStringList sampleColumnNames = {
		"Id",
		"Name",
		"Description" };

	const QStringList equipmentColumnNames = {
		"Id",
		"Name",
		"Description" };

	const QStringList parametersColumnNames = {
		"Id",
		"Name",
		"Value" };

	const QStringList characteristicsColumnNames =
	{
		"Id",
		"Channel",
		"Number of points",
		"Bin time",
		"Weight",
		"Type" };

	const QStringList measuringSystemColumnNames =
	{
		"Id",
		"Name",
		"Description",
		"Main contributor" };

	const QStringList characteristicTypeColumnNames =
	{
		"Id",
		"Name",
		"Description" };
};