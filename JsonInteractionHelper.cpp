#include "JsonInteractionHelper.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

int JsonInteractionHelper::ReadItemFromJsonFile(QString item, QString configFilePath)
{
	QString val;
	QFile file;
	file.setFileName(configFilePath);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	val = file.readAll();
	file.close();
	QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
	QJsonObject json = doc.object();
	int id = json[item].toInt();
	return id;
}

void JsonInteractionHelper::EditJsonFile(QString item, int value, QString configFilePath)
{
	QString val;
	QFile file;
	file.setFileName(configFilePath);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QJsonParseError JsonParseError;
	val = file.readAll();
	file.close();
	QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
	QJsonObject json = doc.object();
	json[item] = value;
	file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
	file.write(doc.toJson());
	file.close();
}

