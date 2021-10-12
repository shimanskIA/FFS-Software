#pragma once

#include <QtSql>
#include <QSqlDatabase>

#include "DbContext.h"

class DbConnection
{
public:
	static DbConnection& GetDbConnectionInstance();
	void AddToDatabase(DbContext* dbContext);

private:
	DbConnection();
	DbConnection(const DbConnection&) {}
	QSqlDatabase database;
};




