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

#include <QtGui>
#include <QX11Info>

#include <QMaemo5InformationBox>
#include <X11/Xlib.h>
#include <X11/Xatom.h>

LoginWindow::LoginWindow(QWidget *parent)
        : QDialog(parent),
          m_authDialog(new Ui_Dialog)
{
    m_authDialog->setupUi(this);

    QStringList onlineServices;
    onlineServices << "Google Documents";
    // Add services here
    onlineServices << "Slide Share";
    m_authDialog->comboBox->addItems(onlineServices);

    connect(m_authDialog->loginButton, SIGNAL(clicked()), this, SLOT(loginService()));
    connect(m_authDialog->comboBox, SIGNAL(activated(int)), this, SLOT(serviceSelected(int)));

    m_authDialog->userEdit->setFocus();
    show();
//    exec();
}

void LoginWindow::loginService()
{
    if("" == m_authDialog->userEdit->text() || "" == m_authDialog->passwordEdit->text()) {
        QMaemo5InformationBox::information(this, "Enter both username and password", QMaemo5InformationBox::DefaultTimeout);
        return;
    }
    disableWidgets();	
    if (0 == m_authDialog->comboBox->currentIndex()) {
        gdoc = new GoogleDocumentService();
        setShowProgressIndicator(true);
        gdoc->clientLogin(m_authDialog->userEdit->text(), m_authDialog->passwordEdit->text());
        connect(gdoc, SIGNAL(userAuthenticated(bool)), this, SLOT(authenticated(bool)));
    }
    if (1 == m_authDialog->comboBox->currentIndex())
    {
        service = new SlideShare(this);
        service->setApikey(new QString("KhSMYyiF"));
        service->setsecretKey(new QString("HDXhAC5g"));
        service->setUsername(new QString(m_authDialog->userEdit->text()));
        service->setPassword(new QString(m_authDialog->passwordEdit->text()));
        service->login();
        setShowProgressIndicator(true);
        connect(service,SIGNAL(loginDone(bool)), this, SLOT(slideShareLoginDoneSlot(bool)));
    }
}

void LoginWindow::serviceSelected(int index)
{
    if (index == 0) {
        m_authDialog->userEdit->setText("@gmail.com");
        m_authDialog->passwordEdit->clear();
    } else if (index == 1) {
        m_authDialog->userEdit->clear();
        m_authDialog->passwordEdit->clear();
    }
    m_authDialog->userEdit->setFocus();
}

void LoginWindow::authenticated(bool success)
{
    if (success) {
        googleListDialog *ld = new googleListDialog(gdoc, this);
        this->accept();;
        ld->show();
    }
    else {
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
{if(loginStatus == false)
    {
        QMaemo5InformationBox::information(this,"<p>Login Failed.</p><p>Check your username and password</p> ", QMaemo5InformationBox::NoTimeout);
        enableWidgets();
    }
    else
    {
        slideshareListDialog * fi = new slideshareListDialog(service, this);
        this->accept();
        fi->show();
    }
}

void LoginWindow::enableWidgets()
{
    setShowProgressIndicator(false);
    m_authDialog->loginButton->setEnabled(true);
    m_authDialog->userEdit->setEnabled(true);
    m_authDialog->passwordEdit->setEnabled(true);
    m_authDialog->comboBox->setEnabled(true);
}

void LoginWindow::disableWidgets()
{
    m_authDialog->loginButton->setEnabled(false);
    m_authDialog->userEdit->setEnabled(false);
    m_authDialog->passwordEdit->setEnabled(false);
    m_authDialog->comboBox->setEnabled(false);
}
