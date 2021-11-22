#include "CZConfoCor1Parser.h"
#include "NamesHelper.h"

#include <QFile>
#include <QTextStream>

CZConfoCor1Parser::CZConfoCor1Parser() : ConfoCorParser()
{

}

CZConfoCor1Parser& CZConfoCor1Parser::GetCZConfoCor1ParserInstance()
{
	static CZConfoCor1Parser* czConfoCor1ParserInstance = 0;

	if (czConfoCor1ParserInstance == 0)
	{
		czConfoCor1ParserInstance = new CZConfoCor1Parser();
	}

	return *czConfoCor1ParserInstance;
}

OperationStatusMessage* CZConfoCor1Parser::ParseRawDataFile(DbContext* dbContext, QString fileLink)
{
	OperationStatusMessage* errorStatusMessage = new OperationStatusMessage(false);
	errorStatusMessage->SetOperationMessage("Parser for this type of device is not implemented yet.");
	return errorStatusMessage;
}

void CZConfoCor1Parser::CascadeEquipmentParametersRead(QString line, bool& flag, QString endLine, EquipmentContext*& equipmentItem, DbContext* dbContext)
{

}

void CZConfoCor1Parser::CreateNewEquipmentItem(QString name, bool& flag, EquipmentContext*& equipmentItem)
{

}

void CZConfoCor1Parser::Bind(MeasuringSystemContext* measuringSystem, EquipmentContext*& equipmentItem, DbContext* dbContext)
{

}

QStringList CZConfoCor1Parser::GetCoordinates(QString line)
{
	return QStringList();
}