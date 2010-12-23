#include "passphrasedialog.h"

#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QDialogButtonBox>

class passphraseDialogPrivate: public QDialogPrivate {
    Q_OBJECT
    Q_DECLARE_PUBLIC(passphraseDialog)
public:
    passphraseDialogPrivate();
    QLineEdit *linedit;
    QPushButton *okButton;
    QPushButton *changeButton;

    bool change;

    void init();

private slots:
    void changeButtonClicked();
};

passphraseDialogPrivate::passphraseDialogPrivate()
    : QDialogPrivate(),
    change(false) {

}

void passphraseDialogPrivate::init() {
    Q_Q(passphraseDialog);
    QVBoxLayout *layout = new QVBoxLayout(q);

    QLabel *label = new QLabel("Enter the passphrase", q);
    layout->addWidget(label);

    linedit = new QLineEdit(q);
    linedit->setEchoMode(QLineEdit::Password);
    layout->addWidget(linedit);

    okButton = new QPushButton("Ok",q);
    changeButton = new QPushButton("Change Passphrase", q);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(Qt::Horizontal, q);
    buttonBox->addButton(changeButton, QDialogButtonBox::AcceptRole);
    buttonBox->addButton(okButton, QDialogButtonBox::AcceptRole);
    okButton->setDefault(true);
    layout->addWidget(buttonBox);
    connect(buttonBox, SIGNAL(accepted()), q, SLOT(accept()));
    connect(changeButton, SIGNAL(clicked()), this, SLOT(changeButtonClicked()));
}

void passphraseDialogPrivate::changeButtonClicked() {
    change = true;
}

passphraseDialog::passphraseDialog(QWidget *parent) :
    QDialog(*new passphraseDialogPrivate, parent)
{
    Q_D(passphraseDialog);
    d->init();
}

QString passphraseDialog::getPassphrase(int &val, QWidget *parent) {
    passphraseDialog dialog(parent);

    QString passphrase;
    bool accepted = (dialog.exec() == QDialog::Accepted);

    if(accepted) {
        if(dialog.d_func()->change) {
            val = 1;
        }
        else {
            QLineEdit *linedit = dialog.d_func()->linedit;
            passphrase = linedit->text();
            val = 0;
        }
    }
    else {
        val = -1;
    }

    return passphrase;
}
