#pragma once

#include "ui_FFSDatabaseInterface.h"
#include "ui_EquipmentAddForm.h"
#include "FFSDatabaseInterface.h"
#include "EquipmentAddForm.h"
#include "MeasurementContext.h"
#include "FFSTableModel.h"
#include "DbReader.h"

#include <QString>
#include <QList>
#include <QStandardItemModel>

class TableWriter 
{
public:
	static TableWriter& GetTableWriterInstance();

	void FillMeasuringSystemsTable(QTableView* tableView);
	void FillMeasuringSystemsTable(QTableView* tableView, QString majorTableName, int majorTableId);

	void FillMeasurementsTable(QTableView* tableView);
	void FillMeasurementsTable(QTableView* tableView, QString majorTableName, int majorTableId);

	void FillEquipmentsTable(QTableView* tableView, QString majorTableName, int majorTableId);
	void FillEquipmentsTable(QTableView* tableView, QList<EquipmentContext*> equipments = DbReader::GetDbReaderInstance().ReadEquipmentsFromDatabase());

	void FillSamplesTable(QTableView* tableView);

	void FillCharacteristicTypesTable(QTableView* tableView);

	void FillParametersTable(QTableView* tableView, QString majorTableName, QString minorTableName, int majorTableId);

	void FillCharacteristicsTable(QTableView* tableView);
	void FillCharacteristicsTable(QTableView* tableView, QString majorTableName, int majorTableId);

	void FillMeasurementRow(int rowNumber, FFSTableModel* tableModel, QList<MeasurementContext*> measurements);
	void FillCharacteristicsRow(int rowNumber, FFSTableModel* tableModel, QList<CharacteristicsContext*> characteristics);
	void FillBaseCharacteristicsTable(QTableView* tableView, QList<CharacteristicsContext*> characteristics);

	void FillExistingEquipmentTable(EquipmentAddForm* view, int fk_measuring_system);

	void RouteMajorRequest(QString tableName, QTableView* tableView);
	void RouteRequest(Ui::FFSDatabaseInterfaceClass ui, QTableView* tableView, QString majorTableName, QString minorTableName, int majorTableId);

private:
	TableWriter() {};
	TableWriter(const TableWriter&) {}

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
		"Name",
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
		"Main contributor name" };

	const QStringList characteristicTypeColumnNames =
	{
		"Id",
		"Name",
		"Description" };
};