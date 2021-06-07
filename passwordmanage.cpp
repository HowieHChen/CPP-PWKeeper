#include <QRandomGenerator>
#include <QDateTime>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

#include "passwordmanage.h"

PasswordManage::PasswordManage(QString tcurrentUser)
{
    //根据当前用户生成对应密码配置文件路径并自动连接配置文件
    currentUser=tcurrentUser;
    passwordINIPath ="/INI/POF"+ currentUser +".ini";
    INIPWManage = new INIService;
    INIPWManage->connectINI(passwordINIPath);
}

//读取所有密码
void PasswordManage::readAllLabel()
{
    listOfAllLabel.clear();
    listOfAllLabel=INIPWManage->getAllValue("LabelList");
}

//读取选中的密码的具体内容
void PasswordManage::readSelectedLabel(QString tlabel)
{
    nowLabel = tlabel;
    nowName = INIPWManage->getValue(tlabel,"Name");
    nowPassword = INIPWManage->getValue(tlabel,"Password");
    nowTarget = INIPWManage->getValue(tlabel,"Target");
    nowOthers = INIPWManage->getValue(tlabel,"Others");
}

//编辑选中的密码
void PasswordManage::editSelectedLabel(QString tlabel,QString tname,QString tpassword,QString ttarget,QString tothers)
{
    if(nowLabel != tlabel)
    {
        deleSelectedLabel(nowLabel);
        addNewLabel(tlabel,tname,tpassword,ttarget,tothers);
        //如果标签已存在，删除后重新添加
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
    //更新当前密码并保存
}

//删除选中的密码
void PasswordManage::deleSelectedLabel(QString tlabel)
{
    INIPWManage->removeKey("LabelList",tlabel);
    INIPWManage->removeSection(tlabel);
}

//添加密码
void PasswordManage::addNewLabel(QString tlabel,QString tname,QString tpassword,QString ttarget,QString tothers)
{
    //qDebug()<<"addNewLabel";
    nowLabel = tlabel;
    nowName = tname;
    nowPassword = tpassword;
    nowTarget = ttarget;
    nowOthers = tothers;
    //qDebug()<<nowLabel<<" "<<nowName<<" "<<nowPassword<<" "<<nowTarget<<" "<<nowOthers;
    INIPWManage->setValue("LabelList",nowLabel,"True");
    INIPWManage->setValue(nowLabel,"Name",nowName);
    INIPWManage->setValue(nowLabel,"Password",nowPassword);
    INIPWManage->setValue(nowLabel,"Target",nowTarget);
    INIPWManage->setValue(nowLabel,"Others",nowOthers);
    //更新当前密码并保存
}

//导出所有密码
bool PasswordManage::outputAllInfo(QString filePath)
{
    QFile *file = new QFile(filePath);
    if(!file->open(QIODevice::ReadWrite|QIODevice::Text))
    {
        //文件打开失败
        return false;
    }
    //文本流保存输出内容
    QTextStream txtOutput(file);
    QString cacheLabel;
    QString cacheName;
    QString cachePassword;
    QString cacheTarget;
    QString cacheOthers;
    for (const auto& i : listOfAllLabel )
    {
        //逐一读取所有密码，获取对应的密码内容并写出
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

//获取所有密码
QStringList PasswordManage::getAllLabel()
{
    return listOfAllLabel;
}

//获取选中的密码的具体内容
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

//获取一个随机字符串（随机密码）
QString PasswordManage::getRandomPW(int minLength,int maxLength)
{
    //随机密码长度
    int length = QRandomGenerator::global()->bounded(minLength, maxLength+1);
    //qDebug() << length;
    const char tmp[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int chrs_size = sizeof(tmp);
    char* ch = new char[length + 1];
    memset(ch, 0, length + 1);
    int ir=0;
    //为字符串逐一添加随机字符
    for (int i = 0; i < length; i++)
        {
            ir = QRandomGenerator::global()->bounded(length*10) % (chrs_size - 1);
            ch[i] = tmp[ir];
        }
    QString resultStr(ch);
    delete[] ch;
    //qDebug() << resultStr;
    return resultStr;
}

//查询密码是否已存在
bool PasswordManage::labelExist(QString tlabel)
{
    return listOfAllLabel.contains(tlabel);
}
