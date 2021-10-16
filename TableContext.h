#pragma once

#include <QString>

class TableContext 
{
public:
	virtual void SetId(int id);
	void IncrementId();
	int GetId();

protected:
	TableContext(QString stateFilePath);
	TableContext();
	int id = 0;
	QString stateFilePath = "";
};
