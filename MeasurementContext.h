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

private:
	QString name;
	QString dateTime;
	QString fileLink;
	int numberOfChannels;
	int repeatCount;
	int numberPositions;
	int kineticsCount;
	SampleContext* fk_sample;
};
