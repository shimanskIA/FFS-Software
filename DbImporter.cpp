#include "DbImporter.h"
#include "DbWriter.h"

DbImporter::DbImporter(DbContext *dbContext, RawDataParser *rawDataParser)
{
	this->dbContext = dbContext;
	this->rawDataParser = rawDataParser;
}

DbImporter::~DbImporter()
{
	delete dbContext;
	delete rawDataParser;
}

OperationStatusMessage* DbImporter::ImportToDatabase()
{
	OperationStatusMessage* operationStatusMessage = rawDataParser->ParseRawDataFile(dbContext);

	if (!operationStatusMessage->GetIsSuccessfull())
	{
		return operationStatusMessage;
	}

	DbWriter* dbWriter = new DbWriter();
	bool wasAnyElementInFileAdded = dbWriter->AddToDatabase(dbContext);

	if (!wasAnyElementInFileAdded)
	{
		OperationStatusMessage* errorStatusMessage = new OperationStatusMessage(false);
		errorStatusMessage->SetOperationMessage("The file you are trying to add already exists in database.");
		return errorStatusMessage;
	}

	return new OperationStatusMessage(true);
}