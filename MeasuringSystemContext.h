#pragma once

#include <QString>

class MeasuringSystemContext
{
public:
	MeasuringSystemContext();
	void SetName(QString name);
	void IncrementId();
	int GetId();

private:
	int id;
	QString name;

	QString stateFilePath = "measuringsystemstate.txt";
};
