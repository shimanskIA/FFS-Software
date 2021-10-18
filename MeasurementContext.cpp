#include "MeasurementContext.h"
#include "TextFileInteractionHelper.h"
#include "qmath.h"

MeasurementContext::MeasurementContext(QString stateFilePath) : TableContext(stateFilePath)
{
	measurementParameters = QList<MeasurementParameterContext*>();
	characteristics = QList<CharacteristicsContext*>();
}

MeasurementContext::MeasurementContext(int id) : TableContext(id)
{

}

MeasurementContext::~MeasurementContext()
{
	qDeleteAll(measurementParameters);
	measurementParameters.clear();
	qDeleteAll(characteristics);
	characteristics.clear();
}

void MeasurementContext::SetId(int id)
{
	TableContext::SetId(id);
	ChangeMeasurementParametersFK(id);
	ChangeCharacteristicsFK(id);
}

void MeasurementContext::SetName(QString name)
{
	this->name = name;
}

void MeasurementContext::SetDateTime(QString dateTime)
{
	this->dateTime = dateTime;
}

void MeasurementContext::SetFileLink(QString fileLink)
{
	this->fileLink = fileLink;
}

void MeasurementContext::SetNumberOfChannels(int numberOfChannels)
{
	this->numberOfChannels = numberOfChannels;
}

void MeasurementContext::SetRepeatCount(int repeatCount)
{
	this->repeatCount = repeatCount;
}

void MeasurementContext::SetKineticsCount(int kineticsCount)
{
	this->kineticsCount = kineticsCount;
}

void MeasurementContext::SetNumberPositions(int numberPositions)
{
	this->numberPositions = numberPositions;
}

void MeasurementContext::SetFKSample(SampleContext* fk_sample)
{
	this->fk_sample = fk_sample;
}

void MeasurementContext::ChangeMeasurementParametersFK(int new_fk)
{
	foreach(MeasurementParameterContext * measurementParameter, measurementParameters)
	{
		measurementParameter->SetFKMeasurement(new_fk);
	}
}

void MeasurementContext::ChangeCharacteristicsFK(int new_fk)
{
	foreach(CharacteristicsContext * characteristic, characteristics)
	{
		characteristic->SetFKMeasurement(new_fk);
	}
}


void MeasurementContext::AddNewMeasurementParameter(MeasurementParameterContext* measurementParameter)
{
	measurementParameters.append(measurementParameter);
	measurementParameter->IncrementId();
}

void MeasurementContext::AddNewCharacteristicsSet(CharacteristicsContext* characteristic)
{
	characteristics.append(characteristic);
	characteristic->IncrementId();
}

QString MeasurementContext::GetName()
{
	return this->name;
}

QString MeasurementContext::GetDateTime() 
{
	return this->dateTime;
}

QString MeasurementContext::GetFileLink()
{
	return this->fileLink;
}

int MeasurementContext::GetNumberOfChannels()
{
	return this->numberOfChannels;
}

int MeasurementContext::GetNumberPositions()
{
	return this->numberPositions;
}

int MeasurementContext::GetKineticsCount()
{
	return this->kineticsCount;
}

int MeasurementContext::GetRepeatCount()
{
	return this->repeatCount;
}

int MeasurementContext::GetFKSample()
{
	return this->fk_sample->GetId();
}

QString MeasurementContext::GetSampleName()
{
	return this->fk_sample->GetName();
}

QList<MeasurementParameterContext*> MeasurementContext::GetMeasurementParameters()
{
	return this->measurementParameters;
}

QList<CharacteristicsContext*> MeasurementContext::GetCharacteristics()
{
	return this->characteristics;
}

int MeasurementContext::GetAmountOfMeasurementParameters()
{
	return this->measurementParameters.length();
}

int MeasurementContext::GetAmountOfCharacteristics()
{
	return this->characteristics.length();
}

bool MeasurementContext::ContainsMeasurementParameter(MeasurementParameterContext* measurementParameter)
{
	QString parameterName = measurementParameter->GetName();
	QString parameterValue = measurementParameter->GetValue();

	foreach(MeasurementParameterContext * innerMeasurementParameter, measurementParameters)
	{
		if (innerMeasurementParameter->GetName() == parameterName && innerMeasurementParameter->GetValue() == parameterValue)
		{
			return true;
		}
	}

	return false;
}

bool MeasurementContext::ContainsCharacteristic(CharacteristicsContext* characteristic)
{
	QString channel = characteristic->GetChannel();
	int numberOfPoints = characteristic->GetNumberOfPoints();
	double binTime = characteristic->GetBinTime();
	QString x = characteristic->GetX();
	QString y = characteristic->GetY();
	double weight = characteristic->GetWeight();
	int fk_characteristic_type = characteristic->GetFKCharacteristicType();

	foreach(CharacteristicsContext * innerCharacteristic, characteristics)
	{
		if (channel == innerCharacteristic->GetChannel() &&
			numberOfPoints == innerCharacteristic->GetNumberOfPoints() &&
			qFabs(binTime - innerCharacteristic->GetBinTime()) < 1e-05 &&
			x == innerCharacteristic->GetX().trimmed() &&
			y == innerCharacteristic->GetY().trimmed() &&
			qFabs(weight - innerCharacteristic->GetWeight()) < 1e-05 &&
			fk_characteristic_type == innerCharacteristic->GetFKCharacteristicType())
		{
			return true;
		}
	}

	return false;
}