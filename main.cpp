#include "signinpage.h"
#include "userprofile.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //添加自定义字体
    QFontDatabase::addApplicationFont(":/fonts/SamsungSharpSans_Bold");
    SignInPage w;
    w.show();
    return a.exec();
}
