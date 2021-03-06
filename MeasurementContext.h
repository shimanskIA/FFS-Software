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
	MeasurementContext(int id);
	~MeasurementContext();
	void SetId(int id) override;
	void SetName(QString name);
	void SetDateTime(QString dateTime);
	void SetFileLink(QString fileLink);
	void SetNumberOfChannels(uint numberOfChannels);
	void SetRepeatCount(uint repeatCount);
	void SetKineticsCount(uint kineticsCount);
	void SetNumberPositions(uint numberPositions);
	void SetFKSample(SampleContext* fk_sample);
	void SetFKMeasuringSystem(int fk_measuring_system);
	void ChangeMeasurementParametersFK(int new_fk);
	void ChangeCharacteristicsFK(int new_fk);

	void AddNewMeasurementParameter(MeasurementParameterContext* measurementParameter);
	void AddNewCharacteristicsSet(CharacteristicsContext* characteristic);

	QString GetName();
	QString GetDateTime();
	QString GetFileLink();
	QString GetSampleName();
	uint GetNumberOfChannels();
	uint GetRepeatCount();
	uint GetKineticsCount();
	uint GetNumberPositions();
	int GetFKSample();
	int GetFKMeasuringSystem();

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
	uint numberOfChannels = 0;
	uint repeatCount = 0;
	uint numberPositions = 0;
	uint kineticsCount = 0;
	SampleContext* fk_sample = nullptr;
	int fk_measuring_system = 0;

	QString sampleName;

	QList<MeasurementParameterContext*> measurementParameters;
	QList<CharacteristicsContext*> characteristics;
};
