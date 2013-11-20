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

#ifndef QWUITCPSERVER_H
#define QWUITCPSERVER_H

#include <QtNetwork/QTcpServer>
#include <QtWui/QwuiGlobal>

/**
 * \brief A simple subclass of QTcpServer.
 * This class provides only a signal newConnection(int) with the incoming connection socket descriptor as parameter.
 */
class QTWUI_EXPORT QwuiTcpServer : public QTcpServer
{
    Q_OBJECT

public:
    QwuiTcpServer(QObject* parent = NULL);
    virtual ~QwuiTcpServer();

signals:
    void newConnection(int socketDescriptor);

protected:
    virtual void incomingConnection(int socketDescriptor);
};

#endif // QWUITCPSERVER_H
