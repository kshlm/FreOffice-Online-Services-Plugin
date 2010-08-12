#include "encryptsupport.h"

#include <QString>
#include <QByteArray>
#include <QSettings>
#include <QInputDialog>
#include <QLineEdit>
#include <QLabel>
#include <QCryptographicHash>
#include <QFile>
#include <QMaemo5InformationBox>

#include  <openssl/evp.h>

encryptSupport::encryptSupport(QWidget *parent)
    : QWidgett(parent)
{
    getDetails();
}

void encryptSupport::getDetails()
{
    QSettings passphraseConf("freoffice", "pluginEncryptionSupport");
    QSettings passphraseTemp("/tmp/freoffice-encryption-support-temp.conf");
    if (!passphraseTemp.contains("key")) {
        enterPassphraseDialog();
        return;
    }
    key = passphraseTemp.value("key").toByteArray();
    iv = passphraseConf.value("iv").toByteArray();
}

void encryptSupport::enterPassphraseDialog()
{
    QSettings passphraseConf("freoffice", "plugin-encryption-support");
    if(!passphraseConf.contains("hash")) {
        newPassphraseDialog();
        return;
    }
    QString hash = passphraseConf.value("hash").toString();
    QString passphrase;
    while(true) {
        passphrase = QInputDialog::getText(this,"Enter Passphrase", "Enter the passphrase you used to encrypt.\n This will be done once every session only", QLineEdit::Normal,"");
        if(QCryptographicHash::hash(passphrase.toUtf8(), QCryptographicHash::Sha1).toHex() == QByteArray::fromHex(hash.toUtf8()))
            break;
        QMaemo5InformationBox::information(this, "Wrong passphrase.\nEnter again.", QMaemo5InformationBox::NoTimeout);
    }
    QSettings passphraseTemp("/tmp/freoffice-encryption-support-temp.conf");
    passphraseTemp.setValue("key", passphrase);
    passphraseTemp.sync();
    getDetails();
}

void encryptSupport::newPassphraseDialog()
{
    QString passphrase;
    while("" == passphrase) {
        passphrase = QInputDialog::getText(this,"New Passphrase", "Please enter a phrase which is at least 4 characters long.The longer the better.\nThis phrase will be used to encrypt your passwords and details", QLineEdit::Normal,"");
    }
    QSettings passphraseConf("freoffice","plugin-encryption-support");
    QString hash(QCryptographicHash::hash(passphrase.toUtf8(), QCryptographicHash::Sha1).toHex());
    passphraseConf.setValue("hash",hash);
    QFile f("/dev/urandom");
    f.open(QFile::ReadOnly);
    QByteArray ivInit = f.read(8);
    f.close();
    passphraseConf.setValue("iv", ivInit);
    passphraseConf.sync();
    QSettings passphraseTemp("/tmp/freoffice-encryption-support-temp.conf");
    passphraseTemp.setValue("key", passphrase);
    passphraseTemp.sync();
}

QString encryptSupport::encrypt(const QString & dataString)
{
    QByteArray data = dataString.toUtf8();
    EVP_CIPHER_CTX ctx;
    EVP_CIPHER_CTX_init(&ctx);
    EVP_EncryptInit_ex(&ctx, EVP_bf_cbc(), NULL, (unsigned char*)key.constData(), (unsigned char*)iv.constData());
    unsigned char outbuf[1024];
    int len = data.length();
    int outlen, tmplen;
    EVP_EncryptUpdate(&ctx, outbuf, &outlen, (unsigned char*)data.constData(), len);
    EVP_EncryptFinal_ex(&ctx, outbuf+len, &tmplen);
    outlen += tmplen;
    EVP_CIPHER_CTX_cleanup(&ctx);
    QByteArray encData((const char*)outbuf, outlen);
    return QString(encData.toHex());
}

QString encryptSupport::decrypt(const QString &dataString)
{
    QByteArray data = QByteArray::fromHex(dataString.toUtf8());
    EVP_CIPHER_CTX ctx;
    EVP_CIPHER_CTX_init(&ctx);
    EVP_DecryptInit_ex(&ctx, EVP_bf_cbc(), NULL, (unsigned char*)key.constData(), (unsigned char*)iv.constData());
    unsigned char outbuf[1024];
    int len = data.length();
    int outlen, tmplen;
    EVP_DecryptUpdate(&ctx, outbuf, &outlen, (unsigned char*)data.constData(), len);
    EVP_DecryptFinal_ex(&ctx, outbuf+outlen, &tmplen);
    outlen += tmplen;
    EVP_CIPHER_CTX_cleanup(&ctx);
    QByteArray decData((const char*)outbuf, outlen);
    return QString(decData);
}
