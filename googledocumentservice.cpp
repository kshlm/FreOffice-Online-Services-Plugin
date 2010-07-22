/*
 *  Copyright (c) 2010 Mani Chandrasekar <maninc@gmail.com>
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

#include <QtGui>
#include <QtNetwork>
#include <QMessageBox>

#include "googledocumentservice.h"
#include "googledocumentlist.h"
#include "googledocument.h"
#include "googlecontenthandler.h"
#include "mimetypes.h"
const QString GoogleDocumentService::GOOGLE_DOCUMENT_URL = "docs.google.com";
const QString GoogleDocumentService::GOOGLE_SPREADSHEET_URL = "spreadsheets.google.com";

GoogleDocumentService::GoogleDocumentService()
        : newInformation(true)
          ,waitingForDoc(false)
          , uploadingDoc(false)
          , loggedin(false)
          , haveDocAuthToken(false)
{
    saveFileName = 0;
    connect(&networkManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(handleNetworkData(QNetworkReply*)));
    gHandler = new GoogleContentHandler();
    xmlReader.setContentHandler(gHandler);
}

void GoogleDocumentService::clientLogin(const QString & username, const QString & password)
{
    QByteArray data;
    data.append(QString("Email="+username+"&Passwd="+password).toUtf8());

    if(!haveDocAuthToken) {
        data.append(QString("&service=writely&source=KOfficev2").toUtf8());
        this->username = username;
        this->password = password;
    }
    else {
        data.append(QString("&service=wise&source=KOfficev2").toUtf8());
    }
    QNetworkRequest req(QUrl("https://www.google.com/accounts/ClientLogin"));
    req.setRawHeader("Host", "www.google.com");
    req.setRawHeader("GData-Version", "3.0");
    req.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    req.setHeader(QNetworkRequest::ContentLengthHeader, data.length());

    networkManager.post(req, data);
}

void GoogleDocumentService::listDocuments()
{
    qDebug() << ">>>>>>>>>>>>>> List Documents" ;
    authToken = docAuthToken;
    QNetworkRequest requestHeader(QUrl("https://docs.google.com/feeds/default/private/full"));
    requestHeader.setRawHeader("Host", "docs.google.com");
    requestHeader.setRawHeader("User-Agent", "KOffice");
    requestHeader.setRawHeader("GData-Version", "3.0");
    requestHeader.setRawHeader("Content-Type", "application/atom+xml");
    requestHeader.setRawHeader("Authorization", authToken.toUtf8());

    networkManager.get(requestHeader);
}

void GoogleDocumentService::handleNetworkData(QNetworkReply *networkReply)
{
    QUrl url = networkReply->url();
    bool ok = false;
    if (!networkReply->error()) {
        if (!loggedin) {
            QByteArray m_data = networkReply->readAll();
            QString text(m_data.data());
            text = text.right(text.length()-text.indexOf("Auth=")-5);
            authToken = QString("GoogleLogin auth=")+text.left(text.indexOf("\n"));
            if (authToken.length() > 20) {
                if(!haveDocAuthToken) {
                    docAuthToken = authToken;
                    haveDocAuthToken = true;
                    clientLogin(this->username, this->password);
                    return;
                }
                spreadAuthToken = authToken;
                authToken = "";
                loggedin = true;
                qDebug() << ">>>>>>>>>>>>>> Login success" ;
                emit userAuthenticated(loggedin);
            }
            else {
                qDebug() << ">>>>>>>>>>>>>> Login failed" ;
                emit userAuthenticated(false);
            }
        }
        else if (waitingForDoc) {
            QByteArray data = networkReply->readAll();
            QFile file(*saveFileName);
            file.open(QIODevice::WriteOnly);
            file.write(data);
            file.close();
            qDebug() << ">>>>>>>>>>>>>> Received Document!!!!! " << file.fileName();
            waitingForDoc = false;
            emit downloadDone(true);
        }
        else if (uploadingDoc) {
            uploadingDoc = false;
            qDebug() << ">>>>>>>>>>>>>> Upload done" ;
            emit uploadDone(true);
        }
        else {
            qDebug() << ">>>>>>>>>>>>>> Received List" ;
            gHandler = new GoogleContentHandler();
            xmlReader.setContentHandler(gHandler);
            QByteArray data = networkReply->readAll();
            xmlInput.setData(data);
            ok = xmlReader.parse(&xmlInput, true);
            prepareLists();
        }
    }
    else {
        qDebug() << networkReply->readAll();
        if(!loggedin)
            emit userAuthenticated(false);
        else if (waitingForDoc) {
            emit downloadDone(false);
            waitingForDoc = false;
        }
        else if (uploadingDoc) {
            emit uploadDone(false);
            uploadingDoc = false;
        }
        else
            emit listDone(false);
    }
    networkReply->deleteLater();
}

void GoogleDocumentService::prepareLists()
{
    presentationList.clear();
    documentList.clear();
    spreadsheetList.clear();
    othersList.clear();
    QList<GoogleDocument *> gList = gHandler->documentList()->entries();
    foreach(GoogleDocument *i, gList) {
        if("presentation" == i->documentType())
            presentationList.append(i);
        else if("spreadsheet" == i->documentType())
            spreadsheetList.append(i);
        else if("document" == i->documentType())
            documentList.append(i);
        else
            othersList.append(i);
    }
    qDebug() << ">>>>>>>>>>>>>> Lists Done" ;
    emit listDone(true);
}


void GoogleDocumentService::downloadDocument(GoogleDocument *doc, QString *saveFileName)
{
    this->saveFileName = saveFileName;
    authToken = docAuthToken;
    QString url = doc->documentUrl();
    QString type = doc->documentType();
    qDebug() << type << "=" << url;
    url.replace("docId", "docID", Qt::CaseInsensitive);
    QString exportFormat = "";

    if (QString::compare(type, "spreadsheet") == 0 ) {
        exportFormat = "&exportFormat=ods&format=ods";
        authToken = spreadAuthToken;
    }
    else if (QString::compare(type, "presentation") == 0 )
        exportFormat = "&exportFormat=ppt&format=ppt";
    else if (QString::compare(type, "document") == 0)
        exportFormat = "&exportFormat=odt&format=odt";

    QUrl documentUrl(url + exportFormat);

    QNetworkRequest requestHeader(documentUrl);
    requestHeader.setRawHeader("User-Agent", "KOffice");
    requestHeader.setRawHeader("GData-Version", "3.0");
    requestHeader.setRawHeader("Authorization", authToken.toUtf8());

    QNetworkReply *reply = networkManager.get(requestHeader);
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SIGNAL(downloadProgress(qint64,qint64)));
    waitingForDoc = true;
    qDebug() << ">>>>>>>>>>>>>> Downloading file" ;
}

void GoogleDocumentService::uploadDocument(QString *filename, QString *title)
{
    authToken = docAuthToken;
    QFile file(*filename);
    file.open(QFile::ReadOnly);
    QByteArray data = file.readAll();
    file.close();
    QUrl url;
    url.setUrl("https://docs.google.com/feeds/default/private/full");

    QNetworkRequest requestHeader(url);
    requestHeader.setRawHeader("User-Agent", "KOffice");
    requestHeader.setRawHeader("GData-Version", "3.0");
    requestHeader.setRawHeader("Authorization", authToken.toUtf8());
    requestHeader.setRawHeader("Content-Type", MimeTypes::getMimeType(QFileInfo(*filename).suffix()).toUtf8());
    requestHeader.setRawHeader("Content-Length", QString::number(data.length()).toUtf8());
    requestHeader.setRawHeader("Slug", QUrl::toPercentEncoding(*title));

    QNetworkReply *reply = networkManager.post(requestHeader, data);
    connect(reply, SIGNAL(uploadProgress(qint64, qint64)), this, SIGNAL(uploadProgress(qint64,qint64)));
    uploadingDoc = true;
    qDebug() << ">>>>>>>>>>>>>> Uploading file" ;
}

