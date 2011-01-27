#ifndef PASSPHRASEDIALOG_H
#define PASSPHRASEDIALOG_H

#include <QDialog>

class passphraseDialog : public QDialog
{
    Q_OBJECT
public:
    explicit passphraseDialog(QWidget *parent = 0);
    static QString getPassphrase(int &val, QWidget *parent = 0);

private:
    bool okClicked;
    bool changeClicked;

    void init();

private slots:
    void okClickedSlot();
    void changeClickedSlot();
};

#endif // PASSPHRASEDIALOG_H
