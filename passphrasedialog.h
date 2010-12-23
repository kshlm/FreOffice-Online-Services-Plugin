#ifndef PASSPHRASEDIALOG_H
#define PASSPHRASEDIALOG_H

#include <QDialog>

class passphraseDialogPrivate;
class passphraseDialog : public QDialog
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(passphraseDialogPrivate)
public:
    explicit passphraseDialog(QWidget *parent = 0);
    static QString getPassphrase(int &val, QWidget *parent = 0);
};

#endif // PASSPHRASEDIALOG_H
