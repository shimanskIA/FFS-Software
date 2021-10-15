#pragma once

#include <QString>

class TableContext 
{
public:
	
	void SetId(int id);
	void IncrementId();
	int GetId();

protected:
	TableContext(QString stateFilePath);
	int id = 0;
	QString stateFilePath = "";
};
