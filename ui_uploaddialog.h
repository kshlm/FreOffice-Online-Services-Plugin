/********************************************************************************
** Form generated from reading UI file 'uploaddialog.ui'
**
** Created: Wed Jul 14 11:40:10 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPLOADDIALOG_H
#define UI_UPLOADDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_uploadDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *fileSelectEdit;
    QPushButton *fileSelectButton;
    QLabel *label_2;
    QLineEdit *titleEdit;
    QPlainTextEdit *descriptionBox;
    QLabel *label_3;
    QLineEdit *tagsEdit;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QLabel *uploadLabel;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *uploadButton;
    QProgressBar *uploadProgress;
    QPushButton *doneButton;

    void setupUi(QDialog *uploadDialog)
    {
        if (uploadDialog->objectName().isEmpty())
            uploadDialog->setObjectName(QString::fromUtf8("uploadDialog"));
        uploadDialog->resize(640, 227);
        verticalLayout = new QVBoxLayout(uploadDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        label = new QLabel(uploadDialog);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        fileSelectEdit = new QLineEdit(uploadDialog);
        fileSelectEdit->setObjectName(QString::fromUtf8("fileSelectEdit"));
        fileSelectEdit->setEnabled(true);
        fileSelectEdit->setReadOnly(true);

        horizontalLayout_2->addWidget(fileSelectEdit);

        fileSelectButton = new QPushButton(uploadDialog);
        fileSelectButton->setObjectName(QString::fromUtf8("fileSelectButton"));

        horizontalLayout_2->addWidget(fileSelectButton);


        formLayout->setLayout(0, QFormLayout::FieldRole, horizontalLayout_2);

        label_2 = new QLabel(uploadDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        titleEdit = new QLineEdit(uploadDialog);
        titleEdit->setObjectName(QString::fromUtf8("titleEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, titleEdit);

        descriptionBox = new QPlainTextEdit(uploadDialog);
        descriptionBox->setObjectName(QString::fromUtf8("descriptionBox"));

        formLayout->setWidget(2, QFormLayout::FieldRole, descriptionBox);

        label_3 = new QLabel(uploadDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        tagsEdit = new QLineEdit(uploadDialog);
        tagsEdit->setObjectName(QString::fromUtf8("tagsEdit"));

        formLayout->setWidget(3, QFormLayout::FieldRole, tagsEdit);

        label_4 = new QLabel(uploadDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);


        verticalLayout->addLayout(formLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        uploadLabel = new QLabel(uploadDialog);
        uploadLabel->setObjectName(QString::fromUtf8("uploadLabel"));

        horizontalLayout_3->addWidget(uploadLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        uploadButton = new QPushButton(uploadDialog);
        uploadButton->setObjectName(QString::fromUtf8("uploadButton"));
        uploadButton->setEnabled(true);

        horizontalLayout->addWidget(uploadButton);

        uploadProgress = new QProgressBar(uploadDialog);
        uploadProgress->setObjectName(QString::fromUtf8("uploadProgress"));
        uploadProgress->setValue(0);
        uploadProgress->setTextVisible(false);
        uploadProgress->setInvertedAppearance(false);

        horizontalLayout->addWidget(uploadProgress);

        doneButton = new QPushButton(uploadDialog);
        doneButton->setObjectName(QString::fromUtf8("doneButton"));
        doneButton->setEnabled(false);

        horizontalLayout->addWidget(doneButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(uploadDialog);
        QObject::connect(doneButton, SIGNAL(clicked()), uploadDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(uploadDialog);
    } // setupUi

    void retranslateUi(QDialog *uploadDialog)
    {
        uploadDialog->setWindowTitle(QApplication::translate("uploadDialog", "Upload", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("uploadDialog", "Select a file", 0, QApplication::UnicodeUTF8));
        fileSelectButton->setText(QApplication::translate("uploadDialog", "Select", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("uploadDialog", "Title", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("uploadDialog", "Description", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("uploadDialog", "Tags", 0, QApplication::UnicodeUTF8));
        uploadLabel->setText(QString());
        uploadButton->setText(QApplication::translate("uploadDialog", "Upload", 0, QApplication::UnicodeUTF8));
        doneButton->setText(QApplication::translate("uploadDialog", "Done", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class uploadDialog: public Ui_uploadDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPLOADDIALOG_H
