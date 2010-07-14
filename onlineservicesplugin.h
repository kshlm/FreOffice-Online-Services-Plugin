#ifndef ONLINESERVICESPLUGIN_H
#define ONLINESERVICESPLUGIN_H

#include "OfficeInterface.h"
#include <QObject>

class LoginWindow;

class onlineServicesPlugin: public QObject, public OfficeInterface
{
    Q_OBJECT
    Q_INTERFACES(OfficeInterface)
public:
    onlineServicesPlugin();
    ~onlineServicesPlugin();
    void setDocument(void *doc);
    QWidget * view();
    QString pluginName();
    QStringList pluginSupportTypes();

private:
    QString name;
    LoginWindow *window;
};

#endif // ONLINESERVICESPLUGIN_H
