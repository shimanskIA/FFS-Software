#include "DbConnection.h"

DbConnection::DbConnection()
{
	database = QSqlDatabase::addDatabase("QODBC");
	database.setDatabaseName("DRIVER={SQL SERVER};SERVER=ACER-A515\\SQLEXPRESS;DATABASE=ffsdbv2;UID=Наташа Лапушка;PWD=;Trusted_Connection=Yes;");
	
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

}

