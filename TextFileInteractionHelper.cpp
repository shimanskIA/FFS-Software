#include "TextFileInteractionHelper.h"

#include <QFile>
#include <QTextStream>

int TextFileInteractionHelper::ReadIdFromTextFile(QString stateFilePath)
{
    QFile file(stateFilePath);

    if (!file.open(QIODevice::ReadOnly)) 
    {
        qWarning("Cannot open file for reading");
    }

    QTextStream in(&file);
    QStringList ids;
    QList<int> convertedIds;
    QString line = in.readLine();
    file.close();
    ids = line.split(' ');
    ids.removeFirst();

    for (int i = 0; i < ids.size(); i++)
    {
        convertedIds.append(ids.at(i).toInt());
    }

    for (int i = 1; ; i++)
    {
        if (!convertedIds.contains(i))
        {
            return i;
        }
    }

}

void TextFileInteractionHelper::WriteIdToTextFile(int id, QString stateFilePath)
{
    QFile rfile(stateFilePath);

    if (!rfile.open(QIODevice::ReadOnly))
    {
        qWarning("Cannot open file for reading");
    }

    QTextStream in(&rfile);
    QString line = in.readLine();

    rfile.close();

    line += " ";
    line += QString::number(id);
    
    QTextStream out(stdout);

    QString filename = stateFilePath;
    QFile wfile(filename);

    if (wfile.open(QIODevice::WriteOnly)) 
    {
        QTextStream out(&wfile);
        out << line;
    }
    else 
    {
        qWarning("Could not open file");
    }

    wfile.close();
}

void TextFileInteractionHelper::DeleteIdFromTextFile(int id, QString stateFilePath)
{
    QFile rfile(stateFilePath);

    if (!rfile.open(QIODevice::ReadOnly))
    {
        qWarning("Cannot open file for reading");
    }

    QTextStream in(&rfile);
    QString line = in.readLine();

    rfile.close();

    QStringList ids = line.split(' ');
    ids.removeFirst();
    ids.removeOne(QString::number(id));
    line = "";

    for (int i = 0; i < ids.size(); i++)
    {
        line += " ";
        line += ids.at(i);
    }

    QTextStream out(stdout);

    QString filename = stateFilePath;
    QFile wfile(filename);

    if (wfile.open(QIODevice::WriteOnly))
    {
        QTextStream out(&wfile);
        out << line;
    }
    else
    {
        qWarning("Could not open file");
    }

    wfile.close();
}

void TextFileInteractionHelper::ClearTextFile(QString fileLink)
{
    QFile file(fileLink);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        file.close();
    }
}