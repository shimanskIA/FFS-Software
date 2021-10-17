#pragma once

#include "SampleContext.h"
#include "TableContext.h"
#include "MeasurementParameterContext.h"
#include "CharacteristicsContext.h"

#include <QString>
#include <QList>

class MeasurementContext : public TableContext
{
public:
	MeasurementContext(QString stateFilePath);
	MeasurementContext();
	~MeasurementContext();
	void SetId(int id) override;
	void SetName(QString name);
	void SetDateTime(QString dateTime);
	void SetFileLink(QString fileLink);
	void SetNumberOfChannels(int numberOfChannels);
	void SetRepeatCount(int repeatCount);
	void SetKineticsCount(int kineticsCount);
	void SetNumberPositions(int numberPositions);
	void SetFKSample(SampleContext* fk_sample);
	void ChangeMeasurementParametersFK(int new_fk);
	void ChangeCharacteristicsFK(int new_fk);

	void AddNewMeasurementParameter(MeasurementParameterContext* measurementParameter);
	void AddNewCharacteristicsSet(CharacteristicsContext* characteristic);

	QString GetName();
	QString GetDateTime();
	QString GetFileLink();
	QString GetSampleName();
	int GetNumberOfChannels();
	int GetRepeatCount();
	int GetKineticsCount();
	int GetNumberPositions();
	int GetFKSample();

	QList<MeasurementParameterContext*> GetMeasurementParameters();
	QList<CharacteristicsContext*> GetCharacteristics();

	int GetAmountOfMeasurementParameters();
	int GetAmountOfCharacteristics();

	bool ContainsMeasurementParameter(MeasurementParameterContext* measurementParameter);
	bool ContainsCharacteristic(CharacteristicsContext* characteristic);

private:
	QString name = "";
	QString dateTime = "";
	QString fileLink = "";
	int numberOfChannels = 0;
	int repeatCount = 0;
	int numberPositions = 0;
	int kineticsCount = 0;
	SampleContext* fk_sample = nullptr;

	QString sampleName;

	QList<MeasurementParameterContext*> measurementParameters;
	QList<CharacteristicsContext*> characteristics;
};
