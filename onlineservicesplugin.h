#ifndef ONLINESERVICESPLUGIN_H
#define ONLINESERVICESPLUGIN_H

#include "OfficeInterface.h"
#include <QObject>

class LoginWindow;
class KoDocument;

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
    KoDocument *doc;
    LoginWindow *window;
};

#endif // ONLINESERVICESPLUGIN_H
