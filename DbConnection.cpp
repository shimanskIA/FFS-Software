#include "DbConnection.h"

DbConnection::DbConnection()
{
	database = QSqlDatabase::addDatabase("QODBC");
	database.setDatabaseName("DRIVER={SQL SERVER};SERVER=ACER-A515\\SQLEXPRESS;DATABASE=ffsdbv3;UID=Ivan;PWD=;Trusted_Connection=Yes;");
	
	if (!database.open())
	{
		qWarning("Unable to connect to database.");
	}
}

DbConnection& DbConnection::GetDbConnectionInstance()
{
	static DbConnection* dbConnectionInstance = 0;
	if (dbConnectionInstance == 0)
	{
		dbConnectionInstance = new DbConnection();
	}
	return *dbConnectionInstance;
}

void DbConnection::WriteToDatabase(QString sqlRequest, QString tableName)
{
	QString idSet = "SET IDENTITY_INSERT %1 ON";
	QSqlQuery query(idSet.arg(tableName));
	query.exec(sqlRequest);
}

QSqlQuery DbConnection::ReadFromDatabase(QString sqlRequest)
{
	QSqlQuery query;
	if (!query.exec(sqlRequest))
	{
		qWarning("Database request wasn't proceeded.");
	}
	return query;
}

void DbConnection::AddToDatabase(DbContext* dbContext)
{
	AddSamples(dbContext->GetSamples());
	AddCharacteristicTypes(dbContext->GetCharacteristicTypes());
}

void DbConnection::AddSamples(QList<SampleContext*> samples)
{
	foreach(SampleContext* sample, samples)
	{
		QString sqlReadRequest = "SELECT * FROM samples WHERE name = '%1' AND description = '%2'";
		int id = sample->GetId();
		QString name = sample->GetName();
		QString description = sample->GetDescription();
		QSqlQuery query = ReadFromDatabase(sqlReadRequest.arg(name).arg(description));
		if (!query.next())
		{
			QString sqlWriteRequest = "INSERT INTO samples(id, name, description) VALUES (%1, '%2', '%3')";
			WriteToDatabase(sqlWriteRequest.arg(id).arg(name).arg(description), "samples");
		}
		else
		{
			sample->SetId(query.value(0).toInt());
		}
	}
}

void DbConnection::AddCharacteristicTypes(QList<CharacteristicTypeContext*> characteristic_types)
{
	foreach(CharacteristicTypeContext* characteristic_type, characteristic_types)
	{
		QString sqlReadRequest = "SELECT * FROM characteristic_types WHERE name = '%1' AND description = '%2'";
		int id = characteristic_type->GetId();
		QString name = characteristic_type->GetName();
		QString description = characteristic_type->GetDescription();
		QSqlQuery query = ReadFromDatabase(sqlReadRequest.arg(name).arg(description));
		if (!query.next())
		{
			QString sqlWriteRequest = "INSERT INTO characteristic_types(id, name, description) VALUES (%1, '%2', '%3')";
			WriteToDatabase(sqlWriteRequest.arg(id).arg(name).arg(description), "characteristic_types");
		}
		else
		{
			characteristic_type->SetId(query.value(0).toInt());
		}
	}
}

