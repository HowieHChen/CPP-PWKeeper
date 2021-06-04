#include "signinpage.h"
#include "userprofile.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SignInPage w;
    w.show();
    return a.exec();
}
