#include "DbImporter.h"
#include "DbWriter.h"
#include "CZConfoCor2Parser.h"
#include "CZConfoCor1Parser.h"
#include "SomeOtherDeviceParser.h"

DbImporter& DbImporter::GetDbImporterInstance()
{
	static DbImporter* dbImporterInstance = 0;

	if (dbImporterInstance == 0)
	{
		dbImporterInstance = new DbImporter();
	}

	return *dbImporterInstance;
}

OperationStatusMessage* DbImporter::ImportToDatabase(QString fileLink)
{
	DbContext* dbContext = new DbContext();
	OperationStatusMessage* operationStatusMessage = LinkParser(dbContext, fileLink);

	if (!operationStatusMessage->GetIsSuccessfull())
	{
		return operationStatusMessage;
	}

	bool wasAnyElementInFileAdded = DbWriter::GetDbWriterInstance().AddToDatabase(dbContext);

	if (!wasAnyElementInFileAdded)
	{
		OperationStatusMessage* errorStatusMessage = new OperationStatusMessage(false);
		errorStatusMessage->SetOperationMessage("The file you are trying to add already exists in database.");
		return errorStatusMessage;
	}

	return new OperationStatusMessage(true);
}

OperationStatusMessage* DbImporter::LinkParser(DbContext* dbContext, QString fileLink)
{
	QString header = ReadHeader(fileLink);

	if (header.contains("Carl Zeiss ConfoCor1"))
	{
		return CZConfoCor1Parser::GetCZConfoCor1ParserInstance().ParseRawDataFile(dbContext, fileLink);
	}
	else if (header.contains("Carl Zeiss ConfoCor2"))
	{
		return CZConfoCor2Parser::GetCZConfoCor2ParserInstance().ParseRawDataFile(dbContext, fileLink);
	}
	else if (header.contains("Some other device"))
	{
		return SomeOtherDeviceParser::GetSomeOtherDeviceParserInstance().ParseRawDataFile(dbContext, fileLink);
	}

	OperationStatusMessage* errorStatusMessage = new OperationStatusMessage(false);
	errorStatusMessage->SetOperationMessage("There's no parser found for chosen file.");
	return errorStatusMessage;
}

QString DbImporter::ReadHeader(QString fileLink)
{
	QFile file(fileLink);

	if (!file.open(QIODevice::ReadOnly))
	{
		qWarning("Cannot open file for reading");
		return 1;
	}

	QTextStream in(&file);
	QString header = in.readLine();
	file.close();
	return header;
}