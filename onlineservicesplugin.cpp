#include "onlineservicesplugin.h"
#include "loginwindow.h"
#include <KoDocument.h>

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
    this->doc = (KoDocument *) doc;
}

QWidget *onlineServicesPlugin::view()
{
    window = new LoginWindow();
    if(doc) {
        window->setOpenDoc(doc->url().path());
    }
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
