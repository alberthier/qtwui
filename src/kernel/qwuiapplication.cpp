/***************************************************************************
 *   Copyright (C) 2007 by Eric ALBER                                      *
 *   eric.alber@gmail.com                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <QtWui/QwuiApplication>
#include <QtCore/QCoreApplication>
#include <QtCore/QTextStream>
#include <QtCore/QBuffer>
#include <QtCore/QByteArray>
#include <QtCore/QUrl>
#include <QtNetwork/QHttpRequestHeader>
#include <QtWui/QwuiFileResourceProvider>
#include <QtWui/QwuiWebget>
#include <QtWui/QwuiBufferedResource>

QwuiApplication::QwuiApplication(const QString& sessionId) :
    QwuiAbstractResourceProvider(sessionId),
    m_mainWebget(NULL),
    m_device(NULL),
    m_javascriptDir("javascript"),
    m_styleSheetsDir("stylesheets")
{
    m_fileProvider = new QwuiFileResourceProvider();
    setKeepSessions(true);
}

QwuiApplication::~QwuiApplication()
{
    delete m_mainWebget;
    delete m_fileProvider;
}

QwuiAbstractResource* QwuiApplication::provide(const QHttpRequestHeader& header, const QString& postContent)
{
    QUrl url(header.path());

    if (m_mainWebget != NULL && (header.path().mid(1).isEmpty() || url.path().mid(1).isEmpty() || QCoreApplication::applicationFilePath().endsWith(url.path()))) {
        QByteArray data;
        QBuffer buffer(&data);
        buffer.open(QIODevice::WriteOnly);

        m_parameters.init(header, postContent);

        QString call = url.queryItemValue("call");
        if (call.isEmpty()) {
            call = m_mainWebget->webName() + ".render";
        }

        m_device = &buffer;
        m_webgetsToUpdate.clear();
        QString mimeType = m_mainWebget->invoke(call);
        if (!m_webgetsToUpdate.isEmpty()) {
            data.clear();
            QTextStream stream(&buffer);
            QSet<const QwuiWebget*>::ConstIterator it = m_webgetsToUpdate.begin();
            QSet<const QwuiWebget*>::ConstIterator itEnd = m_webgetsToUpdate.end();
            for (;it != itEnd; ++it) {
                stream << "new Qwui.Replacer('" + (*it)->webId() + "','?call=" + (*it)->webPath() + ".render');";
            }
            mimeType = "text/ecmascript";
            m_webgetsToUpdate.clear();
        }
        m_device = NULL;

        m_parameters.clear();

        if (mimeType != QString::null) {
            return new QwuiBufferedResource(header.path(), mimeType, data);
        }
    }
    return m_fileProvider->provide(header, postContent);
}

void QwuiApplication::setMainWebget(QwuiWebget* w)
{
    delete m_mainWebget;
    m_mainWebget = w;
    m_mainWebget->setParent(this);
    m_mainWebget->setWebApp(this);
}

void QwuiApplication::setJavascriptDir(const QString& javascriptDir)
{
    m_javascriptDir = javascriptDir;
}

QString QwuiApplication::javascriptDir() const
{
    return m_javascriptDir;
}

void QwuiApplication::setStyleSheetsDir(const QString& styleSheetsDir)
{
    m_styleSheetsDir = styleSheetsDir;
}

QString QwuiApplication::styleSheetDir() const
{
    return m_styleSheetsDir;
}

QwuiParameters QwuiApplication::parameters() const
{
    return m_parameters;
}

QIODevice* QwuiApplication::device()
{
    return m_device;
}

void QwuiApplication::addWebgetToUpdate(const QwuiWebget* webget)
{
    m_webgetsToUpdate.insert(webget);
}
