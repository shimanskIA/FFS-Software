#pragma once

#include <QString>

class MeasurementContext
{
public:
	MeasurementContext();
	void SetName(QString name);
	void SetDateTime(QString dateTime);
	void SetFileLink(QString fileLink);
	void SetNumberOfChannels(int numberOfChannels);
	void SetRepeatCount(int repeatCount);
	void SetKineticsCount(int kineticsCount);
	void SetNumberPositions(int numberPositions);
	void SetFKSample(int fk_sample);
	void SetFKMeasuringSystem(int fk_measuring_system);
	void IncrementId();
	int GetId();

private:
	int id;
	QString name;
	QString dateTime;
	QString fileLink;
	int numberOfChannels;
	int repeatCount;
	int numberPositions;
	int kineticsCount;
	int fk_sample;
	int fk_measuring_system;

	QString stateFilePath = "measurementstate.txt";

};
