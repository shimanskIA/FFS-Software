#include "TableContext.h"
#include "TextFileInteractionHelper.h"

TableContext::TableContext(QString tableStatePath)
{
	this->id = TextFileInteractionHelper::ReadIdFromTextFile(tableStatePath);
	this->stateFilePath = tableStatePath;
}

TableContext::TableContext()
{

}

void TableContext::SetId(int id)
{
	TextFileInteractionHelper::DeleteIdFromTextFile(this->GetId(), stateFilePath);
	this->id = id;
}

void TableContext::IncrementId()
{
	TextFileInteractionHelper::WriteIdToTextFile(id, stateFilePath);
}

int TableContext::GetId()
{
	return this->id;
}