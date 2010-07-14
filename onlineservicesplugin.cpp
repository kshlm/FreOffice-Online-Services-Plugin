#include "onlineservicesplugin.h"
#include "loginwindow.h"

onlineServicesPlugin::onlineServicesPlugin()
{
    name = "Online Services";
    window = 0;
}
onlineServicesPlugin::~onlineServicesPlugin()
{
    delete window;
    window = 0;
}

void onlineServicesPlugin::setDocument(void *doc)
{
    Q_UNUSED(doc);
}

QWidget *onlineServicesPlugin::view()
{
    window = new LoginWindow();
    return window;
}

QString onlineServicesPlugin::pluginName()
{
    return name;
}

QStringList onlineServicesPlugin::pluginSupportTypes()
{
    QStringList types;
    types << "All";
    return types;
}

Q_EXPORT_PLUGIN2(OnlineServicesPlugin, onlineServicesPlugin)