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

#ifndef QWUIHTTPSERVER_H
#define QWUIHTTPSERVER_H

#include <QtWui/QwuiAbstractHttpServer>
#include <QtWui/QwuiGlobal>

class QwuiTcpServer;

/**
 * \brief The concrete HTTP server.
 * Instances of this class listen on a given port and let than an QwuiHttpServerDelegate handle the incomming requests.
 */
class QTWUI_EXPORT QwuiHttpServer : public QwuiAbstractHttpServer
{
    Q_OBJECT

public:
    QwuiHttpServer(QObject* parent = NULL);
    virtual ~QwuiHttpServer();

    void setPort(quint16 port);
    quint16 port() const;

    virtual bool start();
    virtual QString error() const;

private slots:
    void incommingConnection(int socketDescriptor);

private:
    QwuiTcpServer* m_server;
    QString m_lastError;
    quint16 m_port;
};

#endif // QWUIHTTPSERVER_H
