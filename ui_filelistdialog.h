/********************************************************************************
** Form generated from reading UI file 'filelistdialog.ui'
**
** Created: Wed Jul 14 11:23:20 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILELISTDIALOG_H
#define UI_FILELISTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_fileListDialog
{
public:
    QVBoxLayout *verticalLayout_4;
    QTabWidget *listTab;
    QWidget *documentTab;
    QVBoxLayout *verticalLayout;
    QListWidget *documentList;
    QWidget *presentationTab;
    QVBoxLayout *verticalLayout_2;
    QListWidget *presentationList;
    QWidget *spreadsheetTab;
    QVBoxLayout *verticalLayout_3;
    QListWidget *spreadsheetList;
    QWidget *othersTab;
    QVBoxLayout *verticalLayout_5;
    QListWidget *othersList;
    QProgressBar *downloadProgressBar;
    QHBoxLayout *horizontalLayout;
    QPushButton *uploadButton;
    QPushButton *refreshButton;
    QPushButton *downloadButton;

    void setupUi(QDialog *fileListDialog)
    {
        if (fileListDialog->objectName().isEmpty())
            fileListDialog->setObjectName(QString::fromUtf8("fileListDialog"));
        fileListDialog->resize(640, 480);
        verticalLayout_4 = new QVBoxLayout(fileListDialog);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        listTab = new QTabWidget(fileListDialog);
        listTab->setObjectName(QString::fromUtf8("listTab"));
        listTab->setTabShape(QTabWidget::Rounded);
        documentTab = new QWidget();
        documentTab->setObjectName(QString::fromUtf8("documentTab"));
        verticalLayout = new QVBoxLayout(documentTab);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        documentList = new QListWidget(documentTab);
        documentList->setObjectName(QString::fromUtf8("documentList"));

        verticalLayout->addWidget(documentList);

        listTab->addTab(documentTab, QString());
        presentationTab = new QWidget();
        presentationTab->setObjectName(QString::fromUtf8("presentationTab"));
        verticalLayout_2 = new QVBoxLayout(presentationTab);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        presentationList = new QListWidget(presentationTab);
        presentationList->setObjectName(QString::fromUtf8("presentationList"));

        verticalLayout_2->addWidget(presentationList);

        listTab->addTab(presentationTab, QString());
        spreadsheetTab = new QWidget();
        spreadsheetTab->setObjectName(QString::fromUtf8("spreadsheetTab"));
        verticalLayout_3 = new QVBoxLayout(spreadsheetTab);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        spreadsheetList = new QListWidget(spreadsheetTab);
        spreadsheetList->setObjectName(QString::fromUtf8("spreadsheetList"));

        verticalLayout_3->addWidget(spreadsheetList);

        listTab->addTab(spreadsheetTab, QString());
        othersTab = new QWidget();
        othersTab->setObjectName(QString::fromUtf8("othersTab"));
        verticalLayout_5 = new QVBoxLayout(othersTab);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        othersList = new QListWidget(othersTab);
        othersList->setObjectName(QString::fromUtf8("othersList"));

        verticalLayout_5->addWidget(othersList);

        listTab->addTab(othersTab, QString());

        verticalLayout_4->addWidget(listTab);

        downloadProgressBar = new QProgressBar(fileListDialog);
        downloadProgressBar->setObjectName(QString::fromUtf8("downloadProgressBar"));
        downloadProgressBar->setValue(0);
        downloadProgressBar->setTextVisible(false);

        verticalLayout_4->addWidget(downloadProgressBar);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        uploadButton = new QPushButton(fileListDialog);
        uploadButton->setObjectName(QString::fromUtf8("uploadButton"));

        horizontalLayout->addWidget(uploadButton);

        refreshButton = new QPushButton(fileListDialog);
        refreshButton->setObjectName(QString::fromUtf8("refreshButton"));

        horizontalLayout->addWidget(refreshButton);

        downloadButton = new QPushButton(fileListDialog);
        downloadButton->setObjectName(QString::fromUtf8("downloadButton"));

        horizontalLayout->addWidget(downloadButton);


        verticalLayout_4->addLayout(horizontalLayout);


        retranslateUi(fileListDialog);

        listTab->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(fileListDialog);
    } // setupUi

    void retranslateUi(QDialog *fileListDialog)
    {
        fileListDialog->setWindowTitle(QApplication::translate("fileListDialog", "FileList", 0, QApplication::UnicodeUTF8));
        listTab->setTabText(listTab->indexOf(documentTab), QApplication::translate("fileListDialog", "Documents", 0, QApplication::UnicodeUTF8));
        listTab->setTabText(listTab->indexOf(presentationTab), QApplication::translate("fileListDialog", "Presentations", 0, QApplication::UnicodeUTF8));
        listTab->setTabText(listTab->indexOf(spreadsheetTab), QApplication::translate("fileListDialog", "Spreadsheets", 0, QApplication::UnicodeUTF8));
        listTab->setTabText(listTab->indexOf(othersTab), QApplication::translate("fileListDialog", "Others", 0, QApplication::UnicodeUTF8));
        uploadButton->setText(QApplication::translate("fileListDialog", "&Upload", 0, QApplication::UnicodeUTF8));
        refreshButton->setText(QApplication::translate("fileListDialog", "&Refresh List", 0, QApplication::UnicodeUTF8));
        downloadButton->setText(QApplication::translate("fileListDialog", "&Download", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class fileListDialog: public Ui_fileListDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILELISTDIALOG_H
