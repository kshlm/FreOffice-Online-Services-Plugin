#include <QApplication>

#include "loginwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    LoginWindow *login = new LoginWindow();

    return app.exec();
}
