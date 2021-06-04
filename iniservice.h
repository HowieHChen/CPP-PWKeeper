#ifndef INISERVICE_H
#define INISERVICE_H

#include <QString>
#include <QSettings>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>

class INIService
{
public:
    INIService();

    QSettings *activatedINI;

    void connectINI(QString tFilePath);

    bool keyExist(QString tSection, QString tKey);
    bool sectionExist(QString tSection);
    QString getValue(QString tSection,QString tKey);
    QStringList getAllValue(QString tSection);

    void setValue(QString tSection,QString tKey,QString tValue);
    void removeSection(QString tSection);
    void removeKey(QString tSection,QString tKey);

private:

};

#endif // INISERVICE_H
