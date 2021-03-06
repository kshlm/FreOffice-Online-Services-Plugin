/*
 * This file is part of Maemo 5 Office UI for KOffice
 *
 * Copyright (C) 2010 Manikandaprasad N C <maninc@gmail.com>.
 *
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 */

#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>

#include "ui_authenticationdialog.h"

class SlideShare;
class GoogleDocumentService;
class encryptSupport;
class QSettings;
class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
    void setShowProgressIndicator(bool visible);
    void setOpenDoc(const QString &);

private slots:
    void loginService();
    void serviceSelected(int index);
    void authenticated(bool success);
    void slideShareLoginDoneSlot(bool loginStatus);

private:
    Ui_Dialog *m_authDialog;
    encryptSupport *cipher;
    GoogleDocumentService *gdoc;
    SlideShare *service;
    QSettings *settings;
    QString openDocPath;
    void enableWidgets();
    void disableWidgets();
    void saveDetails(QString &key);
    void fillDetails();
};

#endif // LOGINWINDOW_H
