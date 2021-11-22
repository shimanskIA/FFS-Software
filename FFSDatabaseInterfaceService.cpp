#include "FFSDatabaseInterfaceService.h"
#include "DbImporter.h"
#include "DbEditor.h"
#include "DbWriter.h"
#include "IdFileManager.h"
#include "DbConnection.h"

OperationStatusMessage* FFSDatabaseInterfaceService::ImportRequestReceiver(QString fileLink)
{
	return DbImporter::GetDbImporterInstance().ImportToDatabase(fileLink);
}

OperationStatusMessage* FFSDatabaseInterfaceService::DeleteRowRequestReceiver(QString tableName, int selectedId)
{
	return DbEditor::GetDbEditorInstance().DeleteFromDatabase(tableName, selectedId);
}

OperationStatusMessage* FFSDatabaseInterfaceService::UpdateTableRequestReceiver(QString tableName, QString columnName, QVariant cellValue, int selectedId)
{
	return DbEditor::GetDbEditorInstance().UpdateRow(tableName, columnName, cellValue, selectedId);
}

OperationStatusMessage* FFSDatabaseInterfaceService::ReadAbscissaRequestReceiver(int selectedId, QVector<double>& x)
{
	return DbReader::GetDbReaderInstance().ReadAbscissaFromDatabase(selectedId, x);
}

OperationStatusMessage* FFSDatabaseInterfaceService::ReadOrdinateRequestReceiver(int selectedId, QVector<double>& y)
{
	return DbReader::GetDbReaderInstance().ReadOrdinateFromDatabase(selectedId, y);
}

OperationStatusMessage* FFSDatabaseInterfaceService::InitializeMeasuringSystemRequestReceiver(QMap<QString, QString> credentials)
{
	QString sqlReadRequest = "SELECT * FROM measuring_systems WHERE name = '%1' AND main_contributor_name = '%2'";
	QSqlQuery query = DbReader::GetDbReaderInstance().ReadFromDatabase(sqlReadRequest.arg(credentials["name"]).arg(credentials["contributor"]));

	if (query.next())
	{
		OperationStatusMessage* errorStatusMessage = new OperationStatusMessage(false);
		errorStatusMessage->SetOperationMessage("Measuring system with these credentials already exists.");
		return errorStatusMessage;
	}
	else
	{
		DbWriter::GetDbWriterInstance().SetInputMeasuringSystemCredentials(credentials);
		return new OperationStatusMessage(true);
	}
}

void FFSDatabaseInterfaceService::RemoveUnusedIdsRequestReceiver()
{
	IdFileManager* idFileManager = new IdFileManager();
	idFileManager->RemoveUnusedIds();
	idFileManager->AddIdsInUse();
}