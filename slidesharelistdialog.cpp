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

#include "slidesharelistdialog.h"
#include "ui_filelistdialog.h"

#include "slideshareuploaddialog.h"
#include "slideshareDocument.h"

#include <QFileDialog>
#include <QDesktopServices>
#include <QListWidgetItem>
#include <QMenu>
#include <QMouseEvent>
#include <QMaemo5InformationBox>

slideshareListDialog::slideshareListDialog(SlideShare *s, QWidget *parent):
    QDialog(parent),
    ui(new Ui::fileListDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("SlideShare");
    ui->downloadProgressBar->setVisible(false);
    this->service = s;
    ui->listTab->setCurrentIndex(1);
    ui->listTab->removeTab(3);
    connect(ui->uploadButton, SIGNAL(clicked()), this, SLOT(uploadButtonClickedSlot()));
    connect(ui->downloadButton, SIGNAL(clicked()), this, SLOT(downloadButtonClickedSlot()));
    connect(ui->refreshButton, SIGNAL(clicked()), this, SLOT(refreshList()));
    connect(service, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(updateProgressBar(qint64, qint64)));
    connect(service, SIGNAL(downloadDone()), this, SLOT(downloadDoneSlot()));
    connect(service, SIGNAL(listDone()), this, SLOT(fillList()));

    refreshList();
}

slideshareListDialog::~slideshareListDialog()
{
    delete ui;
}

void slideshareListDialog::refreshList()
{
    ui->downloadProgressBar->setMaximum(0);
    ui->downloadProgressBar->setVisible(true);
    ui->listTab->setEnabled(false);
    ui->downloadButton->setEnabled(false);
    ui->uploadButton->setEnabled(false);
    ui->refreshButton->setEnabled(false);
    service->listDocuments();
}

void slideshareListDialog::changeEvent(QEvent *e)
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

void slideshareListDialog::downloadButtonClickedSlot()
{
    QListWidget *tmp;
    QList<SlideShareDocument> list;
    if(0 == ui->listTab->currentIndex()) {
        tmp = ui->documentList;
        list = service->textDocList;
    }
    if(1 == ui->listTab->currentIndex()) {
        tmp = ui->presentationList;
        list = service->presentationList;
    }
    if(2 == ui->listTab->currentIndex()) {
        tmp = ui->spreadsheetList;
        list = service->spreadsheetList;
    }

    if(tmp->currentRow() == -1) {
        QMaemo5InformationBox::information(this, "Select a file from the list to download", QMaemo5InformationBox::DefaultTimeout);
        return;
    }

    SlideShareDocument p = list[tmp->currentRow()];
    QString durl = p.downloadUrl;

    QString saveFileName = QFileDialog::getSaveFileName(this, "Save file", QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation).append("/").append(p.title).append(".").append(p.format), QString("(*.").append(p.format).append(")"));
    qDebug() << saveFileName << endl;
    if("" == saveFileName) {
        return;
    }
    service->setSaveFileName(new QString(saveFileName));

    service->download(&durl);
    ui->listTab->setEnabled(false);
    ui->downloadButton->setEnabled(false);
    ui->uploadButton->setEnabled(false);
    ui->refreshButton->setEnabled(false);
    ui->downloadProgressBar->setVisible(true);
}

void slideshareListDialog::uploadButtonClickedSlot()
{
    slideshareUploadDialog *ud = new slideshareUploadDialog(service, this);
    if("" != openDocPath) {
        ud->setOpenDoc(openDocPath);
    }
    ud->show();
    connect(ud, SIGNAL(accepted()), this, SLOT(refreshList()));
}

void slideshareListDialog::fillList()
{
    ui->documentList->clear();
    ui->presentationList->clear();
    ui->spreadsheetList->clear();

    QList<SlideShareDocument>  list;
    QList<SlideShareDocument>::iterator i;

    list = service->textDocList;
    for(i = list.begin(); i != list.end(); ++i) {
        SlideShareDocument j = *i;
        QListWidgetItem *k = new QListWidgetItem(j.title);
        ui->documentList->addItem(k);
    }

    list = service->presentationList;
    for(i = list.begin(); i != list.end(); ++i) {
        SlideShareDocument j = *i;
        QListWidgetItem *k = new QListWidgetItem(j.title);
        ui->presentationList->addItem(k);
    }

    list = service->spreadsheetList;
    for(i = list.begin(); i != list.end(); ++i) {
        SlideShareDocument j = *i;
        QListWidgetItem *k = new QListWidgetItem(j.title);
        ui->spreadsheetList->addItem(k);
    }
    ui->downloadProgressBar->setMaximum(100);
    ui->downloadProgressBar->setVisible(false);
    ui->listTab->setEnabled(true);
    ui->downloadButton->setEnabled(true);
    ui->uploadButton->setEnabled(true);
    ui->refreshButton->setEnabled(true);
}

void slideshareListDialog::updateProgressBar(qint64 done, qint64 total)
{
    int value = (done * 100 / total);
    ui->downloadProgressBar->setValue((int)value);
}

void slideshareListDialog::downloadDoneSlot()
{
    ui->downloadProgressBar->setVisible(false);
    ui->downloadProgressBar->setValue(0);
    ui->listTab->setEnabled(true);
    ui->downloadButton->setEnabled(true);
    ui->refreshButton->setEnabled(true);
    ui->uploadButton->setEnabled(true);
    QMaemo5InformationBox::information(this, "The file has finished downloading", QMaemo5InformationBox::DefaultTimeout);
}

void slideshareListDialog::setOpenDoc(const QString & openDocPath)
{
    this->openDocPath = openDocPath;
}

bool slideshareListDialog::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::ContextMenu) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        QMenu *menu = new QMenu(this);
        menu->addAction(new QAction("CLICK", this));
        menu->exec(mouseEvent->globalPos());
        return false;
    }
    return true;
}

