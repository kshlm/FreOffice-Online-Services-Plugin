# #####################################################################
# Automatically generated by qmake (2.01a) Sat Jul 10 12:41:16 2010
# #####################################################################
QT += network
QT += xml
QT += maemo5
TEMPLATE = lib
CONFIG += plugin
TARGET = OnlineServicesPlugin
target.path = /usr/lib/freoffice/
INSTALLS += target
DEPENDPATH += .
INCLUDEPATH += . \
    /usr/local/include/office \
    /usr/include/office
LIBS += -lcrypto

# Input
HEADERS += googlecontenthandler.h \
    googledocument.h \
    googledocumentlist.h \
    googledocumentservice.h \
    googlelistdialog.h \
    googleuploaddialog.h \
    loginwindow.h \
    mimetypes.h \
    onlineservicesplugin.h \
    slideshare.h \
    slideshareDocument.h \
    slidesharelistdialog.h \
    slideshareuploaddialog.h \
    encryptsupport.h \
    passphrasedialog.h
FORMS += authenticationdialog.ui \
    filelistdialog.ui \
    uploaddialog.ui
SOURCES += googlecontenthandler.cpp \
    googledocument.cpp \
    googledocumentlist.cpp \
    googledocumentservice.cpp \
    googlelistdialog.cpp \
    googleuploaddialog.cpp \
    loginwindow.cpp \
    mimetypes.cpp \
    onlineservicesplugin.cpp \
    slideshare.cpp \
    slidesharelistdialog.cpp \
    slideshareuploaddialog.cpp \
    encryptsupport.cpp \
    passphrasedialog.cpp
