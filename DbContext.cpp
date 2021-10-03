#include "DbContext.h"

DbContext::DbContext()
{

}

void DbContext::SetMeasurementName(QString measurementName)
{
	this->measurementName = measurementName;
}

void DbContext::SetMeasurementDate(QString measurementDate)
{
	this->measurementDate = measurementDate;
}

void DbContext::SetMeasurementFileLink(QString measurementFileLink)
{
	this->measurementFileLink = measurementFileLink;
}

void DbContext::SetNumberOfPoints(QString numberOfPoints)
{
	this->numberOfPoints = numberOfPoints.toInt();
}

void DbContext::SetBinTime(QString binTime)
{
	this->binTime = binTime.toDouble();
}

void DbContext::SetSampleName(QString sampleName)
{
	this->sampleName = sampleName;
}

void DbContext::SetSampleDescription(QString sampleDescription)
{
	this->sampleDescription = sampleDescription;
}

void DbContext::SetMeasurementParameters(QString parameterName, QString parameterValue)
{
	this->measurementParameters.insert(parameterName, parameterValue.toInt());
}

void DbContext::SetMeasuringSystemName(QString measuringSystemName)
{
	this->measuringSystemName = measuringSystemName;
}

void DbContext::SetEquipment(QString equipmentName, QString equipmentDescription)
{
	this->equipment.insert(equipmentName, equipmentDescription);
}

void DbContext::SetEquipmentParameters(QString parameterName, QString parameterValue)
{
	this->equipmentParameters.insert(parameterName, parameterValue.toDouble());
}