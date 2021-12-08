#include "Reporter.h"
#include "DbReader.h"

#include <QSqlQuery>
#include <QtPrintSupport>

Reporter& Reporter::GetReporterInstance()
{
    static Reporter* dbReporterInstance = 0;

    if (dbReporterInstance == 0)
    {
        dbReporterInstance = new Reporter();
    }

    return *dbReporterInstance;
}

void Reporter::Report(QString fileLink)
{
    QString report;
    report.append("<html><head></head><body><center>" + QString("FFS DATABASE REPORT TYPE 1<br>"));
    report.append("<table border=1><tr>");
    report.append("<td>" + QString("Name") + "</td>");
    report.append("<td>" + QString("Date") + "</td>");
    report.append("<td>" + QString("File") + "</td>");
    report.append("<td>" + QString("Repeat count") + "</td>");
    report.append("<td>" + QString("Kinetics count") + "</td>");
    report.append("<td>" + QString("Number of channels") + "</td>");
    report.append("<td>" + QString("Number positions") + "</td>");
    report.append("<td>" + QString("Sample") + "</td>");
    report.append("<td>" + QString("Measuring system") + "</td></tr>");

    QString sqlReadRequest = "SELECT measurements.name, date, file_link, repeat_count, kinetics_count, number_of_channels, number_positions, samples.name, measuring_systems.name FROM measurements "
        "JOIN samples "
        "ON samples.id = measurements.fk_sample "
        "JOIN measuring_systems "
        "ON measuring_systems.id = measurements.fk_measuring_system ";
    QSqlQuery query = DbReader::GetDbReaderInstance().ReadFromDatabase(sqlReadRequest);

    while (query.next())
    {
        report.append("<tr><td>");
        report.append(query.value(0).toString().trimmed());
        report.append("</td><td>");
        report.append(query.value(1).toString().trimmed());
        report.append("</td><td>");
        report.append(query.value(2).toString().trimmed());
        report.append("</td><td>");
        report.append(query.value(3).toString().trimmed());
        report.append("</td><td>");
        report.append(query.value(4).toString().trimmed());
        report.append("</td><td>");
        report.append(query.value(5).toString().trimmed());
        report.append("</td><td>");
        report.append(query.value(6).toString().trimmed());
        report.append("</td><td>");
        report.append(query.value(7).toString().trimmed());
        report.append("</td><td>");
        report.append(query.value(8).toString().trimmed());
        report.append("</td></tr>");
    }

    report.append("</table><br>");

    report.append("<table border=1><tr>");
    report.append("<td>" + QString("Characteristic type") + "</td>");
    report.append("<td>" + QString("Amount of characteristics of this type") + "</td></tr>");

    sqlReadRequest = "SELECT characteristic_types.name, COUNT(*) FROM characteristic_types "
        "JOIN characteristics ON characteristic_types.id = characteristics.fk_characteristic_type "
        "GROUP BY characteristic_types.name";

    query = DbReader::GetDbReaderInstance().ReadFromDatabase(sqlReadRequest);

    while (query.next())
    {
        report.append("<tr><td>");
        report.append(query.value(0).toString().trimmed());
        report.append("</td><td>");
        report.append(query.value(1).toString().trimmed());
        report.append("</td></tr>");
    }

    report.append("</table></center></body></html>");

    QPrinter printer;
    printer.setOrientation(QPrinter::Portrait);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileLink);

    QTextDocument document;
    document.setHtml(report);
    document.print(&printer);
}