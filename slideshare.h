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

#ifndef SLIDESHARE_H
#define SLIDESHARE_H

#include <QObject>
#include <QtCore>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkCookieJar>


struct SlideShareDocument;

class SlideShare : public QObject
{
    Q_OBJECT

public:
    SlideShare(QObject *parent = 0);
    SlideShare(QString *username, QString *password, QObject *parent = 0 );
    SlideShare(QString *username, QString *password, QString *apiKey, QString *secretKey, QObject *parent);
    ~SlideShare();

    void login();
    void upload();
    void download(QString *durl);
    void listDocuments();
    void searchByTags(QString *tag);

    void setApikey(QString *apiKey);
    void setsecretKey(QString *secretKey);

    void setUsername(QString *username);
    void setPassword(QString *password);

    void setSlideTitle(QString *title);
    void setDescription(QString *description);
    void setTags(QString *tags);
    void setFormat(QString *format);

    void setSourceFile(QString *filename);
    void setSaveFileName(QString *saveFileName);

    QList<SlideShareDocument> textDocList;
    QList<SlideShareDocument> presentationList;
    QList<SlideShareDocument> spreadsheetList;

private:
    QString *apiKey;
    QString *secretKey;
    QString *username;
    QString *password;

    QString *sourceFilename;
    QString *saveFileName;

    SlideShareDocument *doc;

    bool loginStatus;

    QNetworkAccessManager manager;
    QNetworkCookieJar cookieJar;
    QNetworkReply *reply;

    void getThumbnailSmall();
    void getThumbnailBig();


private slots:
    void afterLogin();
    void parseList();
    void saveFile();

signals:
    void downloadProgress(qint64 bytesSent, qint64 bytesTotal);
    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
    void loginDone(bool);
    void uploadDone();
    void listDone();
    void downloadDone();

};

#endif // SLIDESHARE_H
