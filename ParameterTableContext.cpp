#include "ParameterTableContext.h"

ParameterTableContext::ParameterTableContext(QString stateFilePath) : TableContext(stateFilePath)
{

}

ParameterTableContext::ParameterTableContext() : TableContext()
{

}

QString ParameterTableContext::GetName()
{
	return this->name;
}

QString ParameterTableContext::GetValue()
{
	return this->value;
}

void ParameterTableContext::SetName(QString name)
{
	this->name = name;
}

void ParameterTableContext::SetValue(QString value)
{
	this->value = value;
}