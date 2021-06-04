#include "iniservice.h"

INIService::INIService()
{

}

//连接配置文件
void INIService::connectINI(QString tFilePath)
{
    QString fileFullName = QCoreApplication::applicationDirPath() + tFilePath;
    activatedINI = new QSettings(fileFullName, QSettings::IniFormat);
    qDebug()<<"connectINI"<<fileFullName;
}

//查询键是否存在
bool INIService::keyExist(QString tSection, QString tKey)
{
    bool resultExist;
    QString initPath = "/"+tSection+"/"+tKey;
    resultExist = (INIService::activatedINI->contains(initPath));
    return resultExist;
}

//查询节点是否存在
bool INIService::sectionExist(QString tSection)
{
    bool resultExist;
    QString initPath = "/"+tSection;
    resultExist = (INIService::activatedINI->contains(initPath));
    return resultExist;
}

//获取指定节点的键值
QString INIService::getValue(QString tSection, QString tKey)
{
    QString resultValue;
    QString initPath = "/"+tSection+"/"+tKey;
    resultValue = activatedINI->value(initPath).toString();
    return resultValue;
}

//获取指定节点内的全部键
QStringList INIService::getAllValue(QString tSection)
{
    QStringList resultList;
    activatedINI->beginGroup(tSection);
    resultList=activatedINI->allKeys();
    activatedINI->endGroup();
    return resultList;
}

//添加值到指定节点的键
void INIService::setValue(QString tSection, QString tKey, QString tValue)
{
    activatedINI->beginGroup(tSection);
    activatedINI->setValue(tKey,tValue);
    activatedINI->endGroup();
}

//移除节点
void INIService::removeSection(QString tSection)
{
    activatedINI->remove(tSection);
}

//移除键
void INIService::removeKey(QString tSection, QString tKey)
{
    activatedINI->beginGroup(tSection);
    activatedINI->remove(tKey);
    activatedINI->endGroup();
}
