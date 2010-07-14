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

#ifndef GOOGLEUPLOADDIALOG_H
#define GOOGLEUPLOADDIALOG_H

#include <QDialog>

class GoogleDocumentService;
namespace Ui {
    class uploadDialog;
}

class googleUploadDialog : public QDialog
{
    Q_OBJECT
public:
    googleUploadDialog(GoogleDocumentService *service, QWidget *parent = 0);
    ~googleUploadDialog();

protected:
    void changeEvent(QEvent *);

private:
    Ui::uploadDialog *ui;
    GoogleDocumentService *service;

private slots:
    void uploadProgressSlot(qint64 bytesSent, qint64 bytesTotal);
    void showFileDialog();
    void uploadButtonClickedSlot();
    void uploadDoneSlot(bool);
};

#endif // GOOGLEUPLOADDIALOG_H
