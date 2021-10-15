#pragma once

#include <QString>

#include "SampleContext.h"
#include "TableContext.h"

class MeasurementContext : public TableContext
{
public:
	MeasurementContext(QString stateFilePath);
	void SetName(QString name);
	void SetDateTime(QString dateTime);
	void SetFileLink(QString fileLink);
	void SetNumberOfChannels(int numberOfChannels);
	void SetRepeatCount(int repeatCount);
	void SetKineticsCount(int kineticsCount);
	void SetNumberPositions(int numberPositions);
	void SetFKSample(SampleContext* fk_sample);

	QString GetName();
	QString GetDateTime();
	QString GetFileLink();
	int GetNumberOfChannels();
	int GetRepeatCount();
	int GetKineticsCount();
	int GetNumberPositions();
	int GetFKSample();

private:
	QString name = "";
	QString dateTime = "";
	QString fileLink = "";
	int numberOfChannels = 0;
	int repeatCount = 0;
	int numberPositions = 0;
	int kineticsCount = 0;
	SampleContext* fk_sample = nullptr;
};
