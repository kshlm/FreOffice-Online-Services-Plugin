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

#include "googleuploaddialog.h"
#include "ui_uploaddialog.h"

#include "googledocumentservice.h"

#include <QFileDialog>
#include <QMaemo5InformationBox>

googleUploadDialog::googleUploadDialog(GoogleDocumentService *service, QWidget *parent):
        QDialog(parent),
        ui(new Ui::uploadDialog)
{
    this->service = service;
    ui->setupUi(this);
    ui->descriptionBox->setVisible(false);
    ui->tagsEdit->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);

    connect(service, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(uploadProgressSlot(qint64,qint64)));
    connect(ui->fileSelectButton, SIGNAL(clicked()), this, SLOT(showFileDialog()));
    connect(ui->uploadButton, SIGNAL(clicked()), this, SLOT(uploadButtonClickedSlot()));
}

googleUploadDialog::~googleUploadDialog()
{
    disconnect(service, SIGNAL(uploadDone(bool)), this, SLOT(uploadDoneSlot(bool)));
    delete ui;
}

void googleUploadDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch(e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void googleUploadDialog::uploadProgressSlot(qint64 bytesSent, qint64 bytesTotal)
{
    int value = (bytesSent * 100) / bytesTotal;
    ui->uploadProgress->setValue(value);
}

void googleUploadDialog::showFileDialog()
{
    QString filter = "Supported Files (*.odt *.doc *.ppt *.xls)";
    QString filename = QFileDialog::getOpenFileName(this,QString("Select File"),tr(""),filter, &filter);
    ui->fileSelectEdit->setText(filename);
}

void googleUploadDialog::uploadButtonClickedSlot()
{
    if(ui->fileSelectEdit->text() == "" || ui->titleEdit->text() == "")
    {
        QMaemo5InformationBox::information(this,"Please enter both filename and title");
        return;
    }
    else
    {
        ui->fileSelectButton->setEnabled(false);
        ui->titleEdit->setEnabled(false);
        ui->uploadButton->setEnabled(false);
        service->uploadDocument(&ui->fileSelectEdit->text(), &ui->titleEdit->text());
        connect(service, SIGNAL(uploadDone(bool)), this, SLOT(uploadDoneSlot(bool)));
    }
}

void googleUploadDialog::uploadDoneSlot(bool status)
{
    if(!status) {
        QMaemo5InformationBox::information(this,"\nUpload failed\n", QMaemo5InformationBox::NoTimeout);
    }
    else {
        QMaemo5InformationBox::information(this, "Upload completed");
    }
    ui->doneButton->setEnabled(true);
}
