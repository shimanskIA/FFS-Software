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
	void FillSamplesTable(Ui::FFSDatabaseInterfaceClass ui);
	void FillEquipmentsTable(Ui::FFSDatabaseInterfaceClass ui);

private:
	const QStringList measurementColumnNames = {
		"Name",
		"Date",
		"File",
		"Repeat count",
		"Kinetics count",
		"Number of channels",
		"Number positions",
		"Sample" };
	const QStringList sampleColumnNames = {};
	const QStringList equipmentColumnNames = {};
};