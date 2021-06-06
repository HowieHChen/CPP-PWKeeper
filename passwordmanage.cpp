#include <QRandomGenerator>
#include <QDateTime>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

#include "passwordmanage.h"

PasswordManage::PasswordManage(QString tcurrentUser)
{
    currentUser=tcurrentUser;
    passwordINIPath ="/INI/POF"+ currentUser +".ini";
    INIPWManage = new INIService;
    INIPWManage->connectINI(passwordINIPath);
}

void PasswordManage::readAllLabel()
{
    listOfAllLabel.clear();
    listOfAllLabel=INIPWManage->getAllValue("LabelList");
}

void PasswordManage::readSelectedLabel(QString tlabel)
{
    nowLabel = tlabel;
    nowName = INIPWManage->getValue(tlabel,"Name");
    nowPassword = INIPWManage->getValue(tlabel,"Password");
    nowTarget = INIPWManage->getValue(tlabel,"Target");
    nowOthers = INIPWManage->getValue(tlabel,"Others");
}

void PasswordManage::editSelectedLabel(QString tlabel,QString tname,QString tpassword,QString ttarget,QString tothers)
{
    if(nowLabel != tlabel)
    {
        deleSelectedLabel(nowLabel);
        addNewLabel(tlabel,tname,tpassword,ttarget,tothers);
        return;
    }
    nowLabel = tlabel;
    nowName = tname;
    nowPassword = tpassword;
    nowTarget = ttarget;
    nowOthers = tothers;
    INIPWManage->setValue(nowLabel,"Name",nowName);
    INIPWManage->setValue(nowLabel,"Password",nowPassword);
    INIPWManage->setValue(nowLabel,"Target",nowTarget);
    INIPWManage->setValue(nowLabel,"Others",nowOthers);
}

void PasswordManage::deleSelectedLabel(QString tlabel)
{
    INIPWManage->removeKey("LabelList",tlabel);
    INIPWManage->removeSection(tlabel);
}

void PasswordManage::addNewLabel(QString tlabel,QString tname,QString tpassword,QString ttarget,QString tothers)
{
    nowLabel = tlabel;
    nowName = tname;
    nowPassword = tpassword;
    nowTarget = ttarget;
    nowOthers = tothers;
    qDebug()<<nowLabel<<" "<<nowName<<" "<<nowPassword<<" "<<nowTarget<<" "<<nowOthers;
    INIPWManage->setValue("LabelList",nowLabel,"True");
    INIPWManage->setValue(nowLabel,"Name",nowName);
    INIPWManage->setValue(nowLabel,"Password",nowPassword);
    INIPWManage->setValue(nowLabel,"Target",nowTarget);
    INIPWManage->setValue(nowLabel,"Others",nowOthers);
}

bool PasswordManage::outputAllInfo(QString filePath)
{
    QFile *file = new QFile(filePath);
    if(!file->open(QIODevice::ReadWrite|QIODevice::Text))
    {
        return false;
    }
    QTextStream txtOutput(file);
    QString cacheLabel;
    QString cacheName;
    QString cachePassword;
    QString cacheTarget;
    QString cacheOthers;
    for (const auto& i : listOfAllLabel )
    {
        cacheLabel = i;
        cacheName = INIPWManage->getValue(cacheLabel,"Name");
        cachePassword = INIPWManage->getValue(cacheLabel,"Password");
        cacheTarget = INIPWManage->getValue(cacheLabel,"Target");
        cacheOthers = INIPWManage->getValue(cacheLabel,"Others");
        txtOutput << "Label:" << cacheLabel <<'\n';
        txtOutput << "Name:" << cacheName << '\n';
        txtOutput << "Password:" << cachePassword << '\n';
        txtOutput << "Target:" << cacheTarget << '\n';
        txtOutput << "Others:" << cacheOthers << '\n';
        txtOutput << '\n';
    }
    file->close();
    delete file;
    return true;
}

QStringList PasswordManage::getAllLabel()
{
    return listOfAllLabel;
}

QString PasswordManage::getNowLabel()
{
    return nowLabel;
}

QString PasswordManage::getNowName()
{
    return nowName;
}

QString PasswordManage::getNowPassword()
{
    return nowPassword;
}

QString PasswordManage::getNowTarget()
{
    return nowTarget;
}

QString PasswordManage::getNowOthers()
{
    return nowOthers;
}

QString PasswordManage::getRandomPW(int minLength,int maxLength)
{
    int length = QRandomGenerator::global()->bounded(minLength, maxLength+1);
    qDebug() << length;
    const char tmp[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int chrs_size = sizeof(tmp);
    char* ch = new char[length + 1];
    memset(ch, 0, length + 1);

    int ir=0;
    for (int i = 0; i < length; i++)
        {
            ir = QRandomGenerator::global()->bounded(length*10) % (chrs_size - 1);
            ch[i] = tmp[ir];
        }
    QString resultStr(ch);
    delete[] ch;
    qDebug() << resultStr;
    return resultStr;
}

bool PasswordManage::labelExist(QString tlabel)
{
    return listOfAllLabel.contains(tlabel);
}
