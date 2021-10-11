#pragma once

#include <QString>

class SampleContext
{
public:
	SampleContext();
	void SetName(QString name);
	void SetDescription(QString description);
	void IncrementId();
	int GetId();

private:
	int id;
	QString name;
	QString description;

	QString stateFilePath = "samplestate.txt";

};
