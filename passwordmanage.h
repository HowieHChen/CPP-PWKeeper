#ifndef PASSWORDMANAGE_H
#define PASSWORDMANAGE_H

#include <QString>
#include "iniservice.h"
#include <QFile>
#include <QIODevice>

class PasswordManage
{
public:
    PasswordManage(QString tcurrentUser);

    INIService *INIPWManage;

    void readAllLabel();

    void readSelectedLabel(QString tlabel);
    void editSelectedLabel(QString tlabel,QString tname,QString tpassword,QString ttarget,QString tothers);
    void deleSelectedLabel(QString tlabel);
    void addNewLabel(QString tlabel,QString tname,QString tpassword,QString ttarget,QString tothers);

    bool outputAllInfo(QString filePath);

    QStringList getAllLabel();
    QString getNowLabel();
    QString getNowName();
    QString getNowPassword();
    QString getNowTarget();
    QString getNowOthers();

    QString getRandomPW(int minLength,int maxLength);

    bool labelExist(QString tlabel);

private:
    QString currentUser;
    QString passwordINIPath;

    QStringList listOfAllLabel;
    QString nowLabel;
    QString nowName;
    QString nowPassword;
    QString nowTarget;
    QString nowOthers;
};

#endif // PASSWORDMANAGE_H
