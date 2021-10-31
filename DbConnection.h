#pragma once

#include <QtSql>
#include <QSqlDatabase>

class DbConnection
{
public:
	static DbConnection& GetDbConnectionInstance();

private:
	DbConnection();
	DbConnection(const DbConnection&) {}
	QSqlDatabase database;

	bool wasEquipmentAdded = false;
};




