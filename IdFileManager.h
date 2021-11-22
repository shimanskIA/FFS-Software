#pragma once

#include <QString>

class IdFileManager
{
public:
	IdFileManager() {};

	void RemoveUnusedIds();
	void AddIdsInUse();

private:
	void AddIdsToSingleFile(QString fileName, QString stateFilePath);
};