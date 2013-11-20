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

#ifndef QWUIABSTRACTRESSOURCEPROVIDER_H
#define QWUIABSTRACTRESSOURCEPROVIDER_H

#include <QtCore/QObject>
#include <QtCore/QDateTime>
#include <QtWui/QwuiGlobal>

class QHttpRequestHeader;
class QwuiAbstractResource;

/**
 * \brief A resource provider is a class that builds a QwuiAbstractResource for a given HTTP request.
 * This class represents an HTTP session and provides only the session management informations to subclasses.
 * Subclasses must implement the provide() method to return a QwuiAbstractResource corresponding to the
 * given HTTP request.
 */
class QTWUI_EXPORT QwuiAbstractResourceProvider : public QObject
{
    Q_OBJECT

public:
    /**
     * @param sessionId session ID for this resource provider.
     */
    QwuiAbstractResourceProvider(const QString& sessionId = QString::null);
    virtual ~QwuiAbstractResourceProvider();

    /**
     * Subclasses must implement this method and return a QwuiAbstractResource object corresponding to the HTTP request.
     * @param header HTTP request header
     * @param postContent HTTP post content.
     * @return a QwuiAbstractResource object corresponding to the HTTP request.
     */
    virtual QwuiAbstractResource* provide(const QHttpRequestHeader& header, const QString& postContent) = 0;

    /**
     * @return the current session identifier.
     */
    QString sessionId() const;

    /**
     * @return true if the session must be kept between HTTP requests of the same object, false otherwise.
     */
    bool keepSessions() const;

    /**
     * @param keep true if the session must be kept between HTTP requests of the same object, false otherwise.
     */
    void setKeepSessions(bool keep);

    /**
     * @return the session time-out date.
     */
    QDateTime sessionTimeoutDate() const;

    /**
     * Resets the session time-out date.
     */
    void resetSessionTimeoutDate();

    /**
     * @return true if the session timed out, false otherwise.
     */
    bool isSessionTimedOut() const;

    /**
     * @return session lifetime in seconds.
     */
    int sessionLifeTime() const;

    /**
     * @param secs session lifetime in seconds.
     */
    void setSessionLifeTime(int secs);

private:
    bool m_keepSessions;
    QDateTime m_sessionTimeoutDate;
    int m_sessionLifeTime;
    QString m_sessionId;
};

#endif // QWUIABSTRACTRESSOURCEPROVIDER_H
