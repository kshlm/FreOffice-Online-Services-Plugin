/*
 *  Copyright (c) 2010 Kaushal M <kshlmster@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "googlelistdialog.h"
#include "ui_filelistdialog.h"

#include "googledocument.h"
#include "googleuploaddialog.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopServices>

googleListDialog::googleListDialog(GoogleDocumentService *service, QWidget *parent):
        QDialog(parent),
        ui(new Ui::fileListDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Google Docs");
    this->service = service;
    ui->listTab->setCurrentIndex(0);
    ui->downloadProgressBar->setVisible(false);

    connect(ui->downloadButton, SIGNAL(clicked()), this, SLOT(downloadButtonClickedSlot()));
    connect(ui->uploadButton, SIGNAL(clicked()), this, SLOT(uploadButtonClickedSlot()));
    connect(ui->refreshButton, SIGNAL(clicked()), this, SLOT(refreshList()));
    connect(service, SIGNAL(listDone(bool)), this, SLOT(fillList(bool)));
    connect(service, SIGNAL(downloadDone(bool)), this, SLOT(downloadDoneSlot(bool)));
    connect(service, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(updateProgressBar(qint64,qint64)));
    refreshList();
}

void googleListDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void googleListDialog::refreshList()
{
    ui->listTab->setEnabled(false);
    ui->downloadButton->setEnabled(false);
    ui->uploadButton->setEnabled(false);
    ui->refreshButton->setEnabled(false);
    ui->downloadProgressBar->setMinimum(0);
    ui->downloadProgressBar->setMaximum(0);
    ui->downloadProgressBar->setVisible(true);
    service->listDocuments();
}

void googleListDialog::fillList(bool status)
{
    if(status) {
        ui->documentList->clear();
        ui->presentationList->clear();
        ui->spreadsheetList->clear();
        ui->othersList->clear();

        QList<GoogleDocument *> list;

        list = service->documentList;
        foreach(GoogleDocument *i, list) {
            ui->documentList->addItem(i->title());
        }

        list = service->presentationList;
        foreach(GoogleDocument *i, list) {
            ui->presentationList->addItem(i->title());
        }

        list = service->spreadsheetList;
        foreach(GoogleDocument *i, list) {
            ui->spreadsheetList->addItem(i->title());
        }

        list = service->othersList;
        foreach(GoogleDocument *i, list) {
            ui->othersList->addItem(i->title());
        }
    }
    else {
        QMessageBox::information(this, tr("Error"), tr("An error occured while fetching document list"));
    }
    ui->downloadProgressBar->setMaximum(100);
    ui->downloadProgressBar->setVisible(false);
    ui->listTab->setEnabled(true);
    ui->downloadButton->setEnabled(true);
    ui->uploadButton->setEnabled(true);
    ui->refreshButton->setEnabled(true);
}

void googleListDialog::downloadButtonClickedSlot()
{
    QList<GoogleDocument *> list;
    QListWidget *tmp = 0;
    switch(ui->listTab->currentIndex()) {
    case 0:
        tmp = ui->documentList;
        list = service->documentList;
        break;
    case 1:
        tmp = ui->presentationList;
        list = service->presentationList;
        break;
    case 2:
        tmp = ui->spreadsheetList;
        list = service->spreadsheetList;
        break;
    case 3:
        tmp = ui->othersList;
        list = service->othersList;
    }

    if(-1 == tmp->currentRow()) {
        QMessageBox::information(this, QString("No selection"), QString("Please select a file from the list"));
        return;
    }
    GoogleDocument *doc = list[tmp->currentRow()];
    QString format = "";
    if("presentation" == doc->documentType()) {
        format = ".ppt";
    }
    else if("document" == doc->documentType()) {
        format = ".odt";
    }
    else if("spreadsheet" == doc->documentType()) {
        format = ".ods";
    }
    QString filename = QFileDialog::getSaveFileName(this,"Save File",QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation) + "/" + doc->title() + format, "(*" + format + ")");
    if("" == filename)
        return;
    service->downloadDocument(doc, new QString(filename));
    ui->listTab->setEnabled(false);
    ui->uploadButton->setEnabled(false);
    ui->downloadButton->setEnabled(false);
    ui->refreshButton->setEnabled(false);
    ui->downloadProgressBar->setVisible(true);
}

void googleListDialog::uploadButtonClickedSlot()
{
    googleUploadDialog *ud = new googleUploadDialog(service, this);
    ud->show();
    connect(ud, SIGNAL(accepted()), this, SLOT(refreshList()));
}

void googleListDialog::downloadDoneSlot(bool status)
{
    ui->downloadProgressBar->setVisible(false);
    ui->downloadProgressBar->setValue(0);
    ui->listTab->setEnabled(true);
    ui->downloadButton->setEnabled(true);
    ui->refreshButton->setEnabled(true);
    ui->uploadButton->setEnabled(true);
    if(status)
        QMessageBox::information(this, "Download done", "The file has finished downloading");
    else
        QMessageBox::information(this, tr("Error"), tr("An error occured while downloading the document"));
}

void googleListDialog::updateProgressBar(qint64 bytesDone, qint64 bytesTotal)
{
    int value = (bytesDone * 100) / bytesTotal;
    ui->downloadProgressBar->setValue(value);
}
