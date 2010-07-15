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

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDateTime>
#include <QCryptographicHash>
#include <QHash>
#include <QDebug>
#include <QByteArray>
#include <QList>
#include <QPair>
#include <QFile>
#include <QFileInfo>
#include <QDomDocument>
#include <QNetworkProxy>

#include "slideshare.h"
#include "slideshareDocument.h"
#include "mimetypes.h"

SlideShare::SlideShare(QObject *parent):QObject(parent)
{
    manager.setCookieJar(&this->cookieJar);
    doc = new SlideShareDocument;
}

SlideShare::SlideShare(QString *username, QString *password, QObject *parent):QObject(parent)
{
    this->username = username;
    this->password = password;
    SlideShare();
}
SlideShare::SlideShare(QString *username, QString *password, QString *apiKey, QString *secretKey, QObject *parent):QObject(parent)
{
    this->apiKey = apiKey;
    this->secretKey = secretKey;
    SlideShare(username, password);
}

SlideShare::~SlideShare()
{
}

void SlideShare::setUsername(QString *username)
{
    this->username = username;
}

void SlideShare::setPassword(QString *password)
{
    this->password = password;
}

void SlideShare::setApikey(QString *apiKey)
{
    this->apiKey = apiKey;
}

void SlideShare::setsecretKey(QString *secretKey)
{
    this->secretKey = secretKey;
}

void SlideShare::setSlideTitle(QString *title)
{
    doc->title = *title;
}

void SlideShare::setDescription(QString *description)
{
    doc->description = *description;
}

void SlideShare::setTags(QString *tags)
{
    doc->tags = *tags;
}

void SlideShare::setFormat(QString *format)
{
    doc->format = *format;
}

void SlideShare::setSourceFile(QString *filename)
{
    this->sourceFilename = filename;
}

void SlideShare::setSaveFileName(QString *saveFileName)
{
    this->saveFileName = saveFileName;
}


void SlideShare::login()
{
    QUrl *login = new QUrl(QString("http://www.slideshare.net/login"));
    QByteArray data;
    data.append(QString("user_login=").append(username).toUtf8());
    data.append(QString("&user_password=").append(password).toUtf8());

    QNetworkRequest request;
    request.setUrl(*login);

    reply = manager.post(request, data);
    connect(reply,SIGNAL(finished()), this, SLOT(afterLogin()));
}


void SlideShare::afterLogin()
{
    if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 302)
    {
        if(QString("http://www.slideshare.net/").append(username) == reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toString())
            emit loginDone(true);
    }
    else
        emit loginDone(false);
}

void SlideShare::download(QString *durl)
{
    QUrl *dload = new QUrl(*durl) ;
    QNetworkRequest request;
    request.setUrl(*dload);

    QList<QNetworkCookie> list = cookieJar.cookiesForUrl(QUrl("http://www.slideshare.net/"));

    foreach(QNetworkCookie c, list)
    {
        if(c.name() == "_cookie_id")
        {
            request.setHeader(QNetworkRequest::CookieHeader, QVariant::fromValue(list));
        }
    }

    reply = manager.get(request);
    connect(reply,SIGNAL(finished()),this,SLOT(saveFile()));

}
void SlideShare::saveFile()
{
    if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 302)
    {
        reply = manager.get(QNetworkRequest(reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl()));
        connect(reply,SIGNAL(downloadProgress(qint64,qint64)), this, SIGNAL(downloadProgress(qint64,qint64)));
        connect(reply,SIGNAL(finished()), this, SLOT(saveFile()));
        return;
    }

    QFile file(*saveFileName);
    file.open(QFile::WriteOnly);

    file.write(reply->readAll());
    file.close();


    emit downloadDone();
}

void SlideShare::upload()
{
    QDateTime *time = new QDateTime();
    QString ts;
    ts.setNum(time->toTime_t());

    QByteArray data = this->secretKey->toAscii();
    data += ts;

    QFile *file = new QFile(*this->sourceFilename,this);
    file->open(QFile::ReadOnly);

    QByteArray fileData ;
    fileData = file->readAll();

    QByteArray postData;
    postData.append("--BOUNDARY\r\n");
    postData.append("Content-Disposition: form-data; name=\"slideshow_srcfile\"; filename=\"");
    postData.append(file->fileName().toUtf8());
    postData.append("\"\r\n");
    postData.append("Content-Type: " + MimeTypes::getMimeType(doc->format));
    postData.append("\r\n\r\n");
    postData.append(fileData);
    postData.append("\r\n--BOUNDARY\r\n");


    QList<QPair<QString, QString> > params;
    params.append(qMakePair(QString("api_key"),*this->apiKey));
    params.append(qMakePair(QString("ts"),ts));
    params.append(qMakePair(QString("hash"),QString(QCryptographicHash::hash(data, QCryptographicHash::Sha1).toHex())));
    params.append(qMakePair(QString("username"),*this->username));
    params.append(qMakePair(QString("password"),*this->password));
    params.append(qMakePair(QString("slideshow_title"),doc->title));
    if (doc->description != "")
        params.append(qMakePair(QString("slideshow_description"), doc->description ));
    if(doc->tags != "")
        params.append(qMakePair(QString("slideshow_tags"), doc->tags));

    QUrl url("http://www.slideshare.net/api/2/upload_slideshow", QUrl::TolerantMode);
    url.setQueryItems(params);
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data; boundary=BOUNDARY");
    request.setHeader(QNetworkRequest::ContentLengthHeader, postData.length());


    QNetworkReply *reply = manager.post(request, postData);
    connect(reply, SIGNAL(uploadProgress(qint64,qint64)), this, SIGNAL(uploadProgress(qint64,qint64)));
    connect(reply, SIGNAL(finished()), this, SIGNAL(uploadDone()));
}

void SlideShare::listDocuments()
{
    QDateTime *time = new QDateTime(QDateTime::currentDateTime());
    QString ts;
    ts.setNum(time->toTime_t());

    QByteArray data = this->secretKey->toAscii();
    data += ts;

    QList<QPair<QString, QString> > params;
    params.append(qMakePair(QString("api_key"),*this->apiKey));
    params.append(qMakePair(QString("ts"),ts));
    params.append(qMakePair(QString("hash"),QString(QCryptographicHash::hash(data, QCryptographicHash::Sha1).toHex())));
    params.append(qMakePair(QString("username"),*this->username));
    params.append(qMakePair(QString("password"),*this->password));
    params.append(qMakePair(QString("username_for"),*this->username));


    QUrl url("http://www.slideshare.net/api/2/get_slideshows_by_user");
    url.setQueryItems(params);


    QNetworkRequest request;
    request.setUrl(url);

    reply = manager.get(request);
    connect(reply,SIGNAL(finished()), this, SLOT(parseList()));
}
void SlideShare::parseList()
{
    QDomDocument doc;
    QByteArray data = reply->readAll();
    doc.setContent(data);

    QDomElement root = doc.documentElement();
    QDomElement child = root.firstChildElement("Slideshow");

    textDocList.clear();
    presentationList.clear();
    spreadsheetList.clear();

    while(!child.isNull())
    {
        SlideShareDocument *p = new SlideShareDocument;
        p->title = child.firstChildElement("Title").text();
        p->url = child.firstChildElement("URL").text();
        p->format = child.firstChildElement("Format").text();
        p->slideID = child.firstChildElement("ID").text();
        p->thumbnailBig = child.firstChildElement("ThumbnailUrl").text();
        p->thumbnailSmall = child.firstChildElement("ThumbnailSmallURL").text();
        p->downloadUrl = p->url.append("/download");
        QString download = child.firstChildElement("Download").text();
        qDebug() << p->title << p->format ;
        if(download == "1")
        {
            if (p->format == "odt" || p->format == "doc")
                this->textDocList.append(*p);
            if (p->format == "odp" || p->format == "ppt")
                this->presentationList.append(*p);
            if (p->format == "ods" || p->format == "xls")
                this->spreadsheetList.append(*p);
        }

        child = child.nextSiblingElement("Slideshow");
    }
    emit listDone();
}

