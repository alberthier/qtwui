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

#include <QtWui/QwuiHttpServerDelegate>
#include <QtNetwork/QTcpSocket>
#include <QtCore/QTextStream>

// Http request limitations in case of buggy Http clients
// Http request header is limited to 2000 lines
#define QWUI_MAX_HEADER_LINES 2000
// Http request header lines are limited to 8kb per line.
#define QWUI_MAX_HEADER_LINES_LENGTH 8192

QwuiHttpServerDelegate::QwuiHttpServerDelegate(QwuiResourceProviderServer* providerServer, int socketDescriptor) :
    QwuiAbstractHttpServerDelegate(providerServer),
    m_socketDescriptor(socketDescriptor),
    m_requestContentLength(0)
{
}

QwuiHttpServerDelegate::~QwuiHttpServerDelegate()
{
}

QIODevice* QwuiHttpServerDelegate::createDevice()
{
    QTcpSocket* socket = new QTcpSocket();
    if (!socket->setSocketDescriptor(m_socketDescriptor)) {
        delete socket;
        return NULL;
    }
    m_requestContentLength = 0;
    return socket;
}

void QwuiHttpServerDelegate::deleteDevice(QIODevice* device)
{
    //qobject_cast<QTcpSocket*>(device)->waitForDisconnected(-1);
    delete device;
    m_requestContentLength = 0;
}


QHttpRequestHeader QwuiHttpServerDelegate::readHttpRequestHeader()
{
    QTextStream stream(device());
    QString headerStr;
    QString current = device()->readLine(QWUI_MAX_HEADER_LINES_LENGTH);
    int nbLines = 0;
    while (!current.isEmpty() && nbLines <= QWUI_MAX_HEADER_LINES) {
        headerStr += current;
        current = device()->readLine(QWUI_MAX_HEADER_LINES_LENGTH);
    }

    QHttpRequestHeader header(headerStr);
    m_requestContentLength = header.contentLength();

    return header;
}

QString QwuiHttpServerDelegate::readHttpRequestContent()
{
    return QString(device()->read(m_requestContentLength));
}

void QwuiHttpServerDelegate::writeHttpResponseHeader(const QHttpResponseHeader& responseHeader)
{
    QTextStream stream(device());
    stream << responseHeader.toString();
}
