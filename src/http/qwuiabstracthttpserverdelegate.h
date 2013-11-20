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

#ifndef QWUIABSTRACTHTTPSERVERWORKINGTHREAD_H
#define QWUIABSTRACTHTTPSERVERWORKINGTHREAD_H

#include <QtCore/QThread>
#include <QtNetwork/QHttpRequestHeader>
#include <QtWui/QwuiGlobal>

class QIODevice;
class QHttpResponseHeader;
class QLocale;
class QTimer;
class QwuiAbstractResource;
class QwuiAbstractResourceProvider;
class QwuiMessageResource;
class QwuiResourceProviderServer;

/**
 * \brief This class represents wraps the handling of an HTTP request.
 * A delegate is created by the QwuiAbstractHttpServer for each incomming connection and the processing of the
 * HTTP request takes place in this delegate.
 */
class QTWUI_EXPORT QwuiAbstractHttpServerDelegate : public QThread
{
    Q_OBJECT

public:
    QwuiAbstractHttpServerDelegate(QwuiResourceProviderServer* providerServer = NULL);
    virtual ~QwuiAbstractHttpServerDelegate();

protected:
    QIODevice* device() const;
    virtual QIODevice* createDevice() = 0;
    virtual void deleteDevice(QIODevice* device) = 0;
    virtual QHttpRequestHeader readHttpRequestHeader() = 0;
    virtual QString readHttpRequestContent() = 0;
    virtual void writeHttpResponseHeader(const QHttpResponseHeader& responseHeader) = 0;
    virtual void run();
    virtual void handleRequest(const QHttpRequestHeader& header);
    virtual void handleHeadRequest(const QHttpRequestHeader& header);

    void setSessionId(QHttpHeader& header, const QString& sessionId) const;
    QString sessionId(const QHttpHeader& header) const;

protected slots:
    virtual void doRun();

private:
    QIODevice* m_device;
    QwuiResourceProviderServer* m_providerServer;
    QLocale* m_en_USLocale;
    QwuiAbstractResourceProvider* m_provider;
    QwuiMessageResource* m_notFoundResource;
    QwuiAbstractResource* m_resource;
    QTimer* m_timer;

    friend class QwuiAbstractHttpServer;
};

#endif // QWUIABSTRACTHTTPSERVERWORKINGTHREAD_H
