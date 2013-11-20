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

#ifndef QWUIRESSOURCEPROVIDERSERVER_H
#define QWUIRESSOURCEPROVIDERSERVER_H

#include <QtCore/QObject>
#include <QtCore/QHash>
#include <QtWui/QwuiGlobal>

class QTimer;
class QReadWriteLock;
class QwuiAbstractResourceProviderFactory;
class QwuiAbstractHttpServer;
class QwuiAbstractResourceProvider;

/**
 * \brief this class holds currently alive sessions and creates new ones on demand.
 * This class is used to hold sessions and manage their lifetimes.
 * A new session can be created with newSession().
 * With takeSession() and releaseSession() you can take the ownership of a session for your specific handling
 * and release it once you are finished.
 *
 */
class QTWUI_EXPORT QwuiResourceProviderServer : public QObject
{
    Q_OBJECT

public:
    QwuiResourceProviderServer(QObject* parent = NULL);
    virtual ~QwuiResourceProviderServer();

    /**
     * @param factory the main resource provider factory.
     */
    void setResourceProviderFactory(QwuiAbstractResourceProviderFactory* factory);

    /**
     * @return the main resource provider factory.
     */
    QwuiAbstractResourceProviderFactory* resourceProviderFactory() const;

    /**
     * @param server the HTTP server
     */
    void setHttpServer(QwuiAbstractHttpServer* server);

    /**
     * @return the HTTP server
     */
    QwuiAbstractHttpServer* httpServer() const;

    /**
     * @param secs the session lifetime in seconds.
     */
    void setDefaultSessionLifeTime(int secs);

    /**
     * The default session lifetime is 30 min.
     * @return the session lifetime in seconds.
     */
    int defaultSessionLifeTime() const;

    virtual QwuiAbstractResourceProvider* takeSession(const QString& sessionId);
    virtual void releaseSession(QwuiAbstractResourceProvider* session);
    virtual QwuiAbstractResourceProvider* newSession();

    virtual bool start();

protected:
    virtual void customEvent(QEvent* event);

private:
    void pullToCurrentThread(QObject* obj);

private slots:
    void cleanupSessions();

private:
    QHash<QString, QwuiAbstractResourceProvider*> m_sessions;
    QwuiAbstractResourceProviderFactory* m_factory;
    QwuiAbstractHttpServer* m_server;
    QTimer* m_sessionCleanupTimer;
    QReadWriteLock* m_lock;
    int m_defaultSessionLifeTime;
};

#endif // QWUIRESSOURCEPROVIDERSERVER_H
