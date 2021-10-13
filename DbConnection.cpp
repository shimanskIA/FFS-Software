#include "DbConnection.h"

DbConnection::DbConnection()
{
	database = QSqlDatabase::addDatabase("QODBC");
	database.setDatabaseName("DRIVER={SQL SERVER};SERVER=ACER-A515\\SQLEXPRESS;DATABASE=ffsdbv2;UID=Ivan;PWD=;Trusted_Connection=Yes;");
	
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

void DbConnection::AddToDatabase(DbContext* dbContext)
{
	QSqlQuery query("SET IDENTITY_INSERT samples ON");
	query.prepare("INSERT INTO samples (id, name, description) "
		"VALUES (:id, :name, :description)");
	query.bindValue(":id", 20);
	query.bindValue(":name", "Cy5");
	query.bindValue(":description", "");
	query.exec();
}

void DbConnection::ReadFromDataBase()
{
	QSqlQuery query;
	QString sampleName;
	if (query.exec("SELECT * FROM samples"))
	{
		while (query.next()) 
		{
			int id = query.value(0).toInt();
			QString name = query.value(1).toString();
		}
	}
}

