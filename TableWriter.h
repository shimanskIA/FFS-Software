#pragma once

#include "ui_FFSDatabaseInterface.h"
#include "FFSDatabaseInterface.h"

#include <QString>
#include <QList>

class TableWriter 
{
public:
	TableWriter();

	void FillMeasurementsTable(Ui::FFSDatabaseInterfaceClass ui);
	void FillMeasurementsTable(Ui::FFSDatabaseInterfaceClass ui, QString majorTableName, int majorTableId);
	void FillSamplesTable(Ui::FFSDatabaseInterfaceClass ui);
	void FillEquipmentsTable(Ui::FFSDatabaseInterfaceClass ui);
	void FillEquipmentsTable(Ui::FFSDatabaseInterfaceClass ui, QString majorTableName, int majorTableId);

	void FillParametersTable(Ui::FFSDatabaseInterfaceClass ui, QString majorTableName, QString minorTableName, int majorTableId);
	void FillCharacteristicsTable(Ui::FFSDatabaseInterfaceClass ui, QString majorTableName, int majorTableId);

	void RouteRequest(Ui::FFSDatabaseInterfaceClass ui, QString majorTableName, QString minorTableName, int majorTableId);

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
};