#pragma once

#include <QString>

class SampleContext
{
public:
	SampleContext();
	void SetId(int id);
	void SetName(QString name);
	void SetDescription(QString description);
	void IncrementId();
	int GetId();
	QString GetName();
	QString GetDescription();

private:
	int id;
	QString name;
	QString description;

	QString stateFilePath = "samplestate.txt";

};
