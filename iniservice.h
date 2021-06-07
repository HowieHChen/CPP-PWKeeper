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

    //连接配置文件
    void connectINI(QString tFilePath);

    //查询键是否存在
    bool keyExist(QString tSection, QString tKey);

    //查询节点是否存在
    bool sectionExist(QString tSection);

    //获取键值
    QString getValue(QString tSection,QString tKey);

    //获取节点内所有键
    QStringList getAllValue(QString tSection);

    //设置键值
    void setValue(QString tSection,QString tKey,QString tValue);

    //移除节点
    void removeSection(QString tSection);

    //移除键
    void removeKey(QString tSection,QString tKey);

private:
};

#endif // INISERVICE_H
