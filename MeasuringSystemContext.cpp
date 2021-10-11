#include "MeasuringSystemContext.h"
#include "TextFileInteractionHelper.h"

MeasuringSystemContext::MeasuringSystemContext()
{
	this->id = TextFileInteractionHelper::ReadIdFromTextFile(stateFilePath);
}

void MeasuringSystemContext::SetName(QString name)
{
	this->name = name;
}

void MeasuringSystemContext::IncrementId()
{
	TextFileInteractionHelper::WriteIdToTextFile(id, stateFilePath);
}

int MeasuringSystemContext::GetId()
{
	return this->id;
}