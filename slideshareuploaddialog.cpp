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

#include "slideshareuploaddialog.h"
#include "ui_uploaddialog.h"

#include "slideshare.h"

#include <QFileDialog>
#include <QMessageBox>

slideshareUploadDialog::slideshareUploadDialog(SlideShare *service, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::uploadDialog)
{
    this->service = service;
    ui->setupUi(this);
    connect(service, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(uploadProgressSlot(qint64,qint64)));
    connect(ui->fileSelectButton, SIGNAL(clicked()), this, SLOT(showFileDialog()));
    connect(ui->uploadButton, SIGNAL(clicked()), this, SLOT(uploadButtonClickedSlot()));
    connect(service, SIGNAL(uploadDone()), this, SLOT(uploadDoneSlot()));
}

slideshareUploadDialog::~slideshareUploadDialog()
{
    delete ui;
}

void slideshareUploadDialog::changeEvent(QEvent *e)
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


void slideshareUploadDialog::uploadProgressSlot(qint64 sent, qint64 total)
{
    qint64 value = (sent * 100 / total) ;
    ui->uploadProgress->setValue(value);
}

void slideshareUploadDialog::showFileDialog()
{
    QString filter = "Supported Files (odt doc odp ppt ods xls)(*.odt *.doc *.odp *.ppt *.ods *.xls);; Documents (odt doc)(*.odt *.doc);; Presentations (odp ppt)(*.odp *.ppt) ;; Spreadsheets(ods xls)(*.ods *.xls)";
    QString filename = QFileDialog::getOpenFileName(this,QString("Select File"),tr(""),filter);
    ui->fileSelectEdit->setText(filename);
}

void slideshareUploadDialog::uploadButtonClickedSlot()
{
    if(ui->fileSelectEdit->text() == "" || ui->titleEdit->text() == "")
    {
        QMessageBox::information(this,"Incomplete parameters","Please enter atleast filename and title");
        return;
    }
    else
    {
        ui->fileSelectButton->setEnabled(false);
        ui->titleEdit->setEnabled(false);
        ui->descriptionBox->setEnabled(false);
        ui->tagsEdit->setEnabled(false);
        ui->uploadButton->setEnabled(false);
        ui->uploadLabel->setText(tr("Uploading file..."));
        service->setSourceFile(&ui->fileSelectEdit->text());
        service->setSlideTitle(&ui->titleEdit->text());
        service->setDescription(&ui->descriptionBox->text());
        service->setTags(&ui->tagsEdit->text());
        service->setFormat(new QString(QFileInfo(ui->fileSelectEdit->text()).suffix()));
        service->upload();
    }
}

void slideshareUploadDialog::uploadDoneSlot()
{
    ui->uploadLabel->setText(tr("Upload done. It will take some time before the file appears in the list. Please be patient."));
    ui->doneButton->setEnabled(true);
}
