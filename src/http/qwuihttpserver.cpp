/**************************************************************************
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

#include <QtWui/QwuiHttpServer>
#include <QtWui/QwuiTcpServer>
#include <QtWui/QwuiHttpServerDelegate>

QwuiHttpServer::QwuiHttpServer(QObject* parent) :
    QwuiAbstractHttpServer(parent),
    m_server(NULL),
    m_port(80)
{
    m_server = new QwuiTcpServer(this);
    connect(m_server, SIGNAL(newConnection(int)), this, SLOT(incommingConnection(int)));
}

QwuiHttpServer::~QwuiHttpServer()
{
    delete m_server;
}

void QwuiHttpServer::setPort(quint16 port)
{
    m_port = port;
}

quint16 QwuiHttpServer::port() const
{
    return m_port;
}

bool QwuiHttpServer::start()
{
    if (!m_server->listen(QHostAddress::Any, m_port)) {
        m_lastError = QString("Unable to start server on port %1").arg(m_port);
        return false;
    }
    m_lastError = QString::null;
    return true;
}

QString QwuiHttpServer::error() const
{
    return m_lastError;
}

void QwuiHttpServer::incommingConnection(int socketDescriptor)
{
    process(new QwuiHttpServerDelegate(resourceProviderServer(), socketDescriptor));
}
