#ifndef ENCRYPTSUPPORT_H
#define ENCRYPTSUPPORT_H

#include <QObject>
class QString;
class QByteArray;

class encryptSupport:public QObject
{
public:
    encryptSupport(QObject * parent = 0);
    QByteArray encrypt(const QString &);
    QByteArray decrypt(const QString &);
private:
    QByteArray key;
    QByteArray iv;

    void getDetails();
    void newPassphraseDialog();
    void enterPassphraseDialog();
};

#endif // ENCRYPTSUPPORT_H
