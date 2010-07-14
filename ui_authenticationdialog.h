/********************************************************************************
** Form generated from reading UI file 'authenticationdialog.ui'
**
** Created: Wed Jul 14 11:23:20 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHENTICATIONDIALOG_H
#define UI_AUTHENTICATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QComboBox *comboBox;
    QLabel *label_2;
    QLineEdit *userEdit;
    QLabel *label_3;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(449, 135);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setWordWrap(false);

        verticalLayout->addWidget(label);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_4 = new QLabel(Dialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        comboBox = new QComboBox(Dialog);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 0, 1, 1, 1);

        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        userEdit = new QLineEdit(Dialog);
        userEdit->setObjectName(QString::fromUtf8("userEdit"));

        gridLayout->addWidget(userEdit, 1, 1, 1, 1);

        label_3 = new QLabel(Dialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        passwordEdit = new QLineEdit(Dialog);
        passwordEdit->setObjectName(QString::fromUtf8("passwordEdit"));
        passwordEdit->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(passwordEdit, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        loginButton = new QPushButton(Dialog);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));

        verticalLayout->addWidget(loginButton);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Account Signin", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Dialog", "You need to supply Username and Password to access documents", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Dialog", "Site:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Dialog", "Username:", 0, QApplication::UnicodeUTF8));
        userEdit->setText(QApplication::translate("Dialog", "@gmail.com", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Dialog", "Password:", 0, QApplication::UnicodeUTF8));
        passwordEdit->setInputMask(QString());
        passwordEdit->setText(QString());
        loginButton->setText(QApplication::translate("Dialog", "Sign In", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHENTICATIONDIALOG_H
