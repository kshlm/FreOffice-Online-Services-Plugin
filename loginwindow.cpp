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

#include "loginwindow.h"
#include "googledocumentservice.h"
#include "googlelistdialog.h"
#include "slideshare.h"
#include "slidesharelistdialog.h"
#include "encryptsupport.h"

#include <QtGui>
#include <QX11Info>
#include <QSettings>

#include <QMaemo5InformationBox>
#include <X11/Xlib.h>
#include <X11/Xatom.h>

LoginWindow::LoginWindow(QWidget *parent)
    : QDialog(parent),
      m_authDialog(new Ui_Dialog),
      settings(new QSettings("freoffice", "online-services-plugin", this)),
      cipher(new encryptSupport(this))
{
    m_authDialog->setupUi(this);

    QStringList onlineServices;
    onlineServices << "Google Documents";
    // Add services here
    onlineServices << "Slide Share";
    m_authDialog->comboBox->addItems(onlineServices);

    connect(m_authDialog->loginButton, SIGNAL(clicked()), this, SLOT(loginService()));
    connect(m_authDialog->comboBox, SIGNAL(activated(int)), this, SLOT(serviceSelected(int)));
    fillDetails();
    m_authDialog->userEdit->setInputMethodHints(Qt::ImhNoAutoUppercase);
    m_authDialog->userEdit->setFocus();
    show();
}

LoginWindow::~LoginWindow()
{
    settings->sync();
}

void LoginWindow::setOpenDoc(const QString & openDocPath)
{
    this->openDocPath = openDocPath;
}

void LoginWindow::loginService()
{
    if("" == m_authDialog->userEdit->text() || "" == m_authDialog->passwordEdit->text()) {
        QMaemo5InformationBox::information(this, "Enter both username and password", QMaemo5InformationBox::DefaultTimeout);
        return;
    }
    disableWidgets();
    if(0 == m_authDialog->comboBox->currentIndex()) {
        gdoc = new GoogleDocumentService();
        setShowProgressIndicator(true);
        gdoc->clientLogin(m_authDialog->userEdit->text(), m_authDialog->passwordEdit->text());
        connect(gdoc, SIGNAL(userAuthenticated(bool)), this, SLOT(authenticated(bool)));
    }
    if(1 == m_authDialog->comboBox->currentIndex()) {
        service = new SlideShare(this);
        service->setApikey(new QString("KhSMYyiF"));
        service->setsecretKey(new QString("HDXhAC5g"));
        service->setUsername(new QString(m_authDialog->userEdit->text()));
        service->setPassword(new QString(m_authDialog->passwordEdit->text()));
        service->login();
        setShowProgressIndicator(true);
        connect(service, SIGNAL(loginDone(bool)), this, SLOT(slideShareLoginDoneSlot(bool)));
    }
}

void LoginWindow::serviceSelected(int index)
{
    if(index == 0) {
        m_authDialog->userEdit->setText("@gmail.com");
        m_authDialog->passwordEdit->clear();
    } else if(index == 1) {
        m_authDialog->userEdit->clear();
        m_authDialog->passwordEdit->clear();
    }
    fillDetails();
    m_authDialog->userEdit->setFocus();
}

void LoginWindow::authenticated(bool success)
{
    if(success) {
        QString key("user/gdocs");
        saveDetails(key);
        googleListDialog *ld = new googleListDialog(gdoc, this);
        ld->setOpenDoc(openDocPath);
        this->accept();;
        ld->show();
    } else {
        QMaemo5InformationBox::information(this, ("<p>Login Failed</p><p>Check your username & password</p>"), QMaemo5InformationBox::NoTimeout);
        enableWidgets();
    }
}

void LoginWindow::setShowProgressIndicator(bool visible)
{
    unsigned long val = visible ? 1 : 0;
    Atom atom = XInternAtom(QX11Info::display(),
                            "_HILDON_WM_WINDOW_PROGRESS_INDICATOR", False);
    XChangeProperty(QX11Info::display(), winId(), atom, XA_INTEGER,
                    32, PropModeReplace,
                    (unsigned char *) &val, 1);
}

void LoginWindow::slideShareLoginDoneSlot(bool loginStatus)
{
    if(loginStatus == false) {
        QMaemo5InformationBox::information(this, "<p>Login Failed.</p><p>Check your username and password</p> ", QMaemo5InformationBox::NoTimeout);
        enableWidgets();
    } else {
        QString key("user/slideshare");
        saveDetails(key);
        slideshareListDialog * ld = new slideshareListDialog(service, this);
        ld->setOpenDoc(openDocPath);
        this->accept();
        ld->show();
    }
}

void LoginWindow::enableWidgets()
{
    setShowProgressIndicator(false);
    m_authDialog->loginButton->setEnabled(true);
    m_authDialog->userEdit->setEnabled(true);
    m_authDialog->passwordEdit->setEnabled(true);
    m_authDialog->comboBox->setEnabled(true);
    m_authDialog->saveCheckBox->setEnabled(true);
}

void LoginWindow::disableWidgets()
{
    m_authDialog->loginButton->setEnabled(false);
    m_authDialog->userEdit->setEnabled(false);
    m_authDialog->passwordEdit->setEnabled(false);
    m_authDialog->comboBox->setEnabled(false);
    m_authDialog->saveCheckBox->setEnabled(false);
}

void LoginWindow::saveDetails(QString &key)
{
    if(Qt::Checked == m_authDialog->saveCheckBox->checkState()) {
        QVariantMap m;
        QString username = m_authDialog->userEdit->text();
        QString password = m_authDialog->passwordEdit->text();
        m.insert("username", username);
        m.insert("password", cipher->encrypt(password));
        settings->setValue(key, m);
    } else {
        settings->remove(key);
    }
}

void LoginWindow::fillDetails()
{
    QString key = "";
    if(0 == m_authDialog->comboBox->currentIndex())
        key = "user/gdocs";
    else if(1 == m_authDialog->comboBox->currentIndex())
        key = "user/slideshare";
    else
        return;
    if(settings->contains(key)) {
        QVariantMap m = settings->value(key).value<QVariantMap>();
        QString username = m.value("username").toString();
        QString password = m.value("password").toString();
        qDebug() << password;
        m_authDialog->userEdit->setText(username);
        m_authDialog->passwordEdit->setText(cipher->decrypt(password));
        m_authDialog->saveCheckBox->setCheckState(Qt::Checked);
    } else
        m_authDialog->saveCheckBox->setCheckState(Qt::Unchecked);
    return;
}
