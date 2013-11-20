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

#ifndef QWUIABSTRACTHTTPSERVER_H
#define QWUIABSTRACTHTTPSERVER_H

#include <QtCore/QObject>
#include <QtWui/QwuiGlobal>

class QwuiResourceProviderServer;
class QwuiAbstractHttpServerDelegate;

/**
 * \brief Base class for the implementation of an HTTP server.
 * An HTTP server needs a resource provider server that will provide the resources depending on the mime type.
 * There are two operating modes for a server: Queuing the requests and treating them sequentially or using a
 * different thread for each connection.
 */
class QTWUI_EXPORT QwuiAbstractHttpServer : public QObject
{
    Q_OBJECT

public:
    enum RequestProcessingType {
        QueuedProcessing,
        ThreadedProcessing
    };

public:
    QwuiAbstractHttpServer(QObject* parent = NULL);
    virtual ~QwuiAbstractHttpServer();

    void setResourceProviderServer(QwuiResourceProviderServer* server);
    QwuiResourceProviderServer* resourceProviderServer() const;
    void setRequestProcessingType(RequestProcessingType t);
    RequestProcessingType requestProcessingType() const;

    /**
     * Implement this method to implement the server start.
     * @return true if the initialization succeeded, false otherwise.
     */
    virtual bool start() = 0;

    /**
     * @return the error string describing a failed initialization.
     */
    virtual QString error() const;

protected:
    /**
     * @param delegate a delegate representing an incomming connection.
     */
    void process(QwuiAbstractHttpServerDelegate* delegate);

private:
    QwuiResourceProviderServer* m_server;
    RequestProcessingType m_type;
};

#endif // QWUIABSTRACTHTTPSERVER_H
