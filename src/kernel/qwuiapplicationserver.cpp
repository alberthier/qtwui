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

#include <QtWui/QwuiApplicationServer>
#include <QtCore/QTimer>
#include <QtCore/QCoreApplication>
#include <QtWui/QwuiHttpServer>
#include <QtWui/QwuiApplicationFactory>

QwuiApplicationServer::QwuiApplicationServer(QwuiApplicationCreator creatorFunction, QObject* parent) :
    QwuiResourceProviderServer(parent)
{
    setResourceProviderFactory(new QwuiApplicationFactory(creatorFunction, QCoreApplication::arguments()));
    QwuiHttpServer* server = new QwuiHttpServer(this);
    server->setResourceProviderServer(this);
    setHttpServer(server);
}

QwuiApplicationServer::~QwuiApplicationServer()
{
}

void QwuiApplicationServer::setBuiltInServerPort(quint16 port)
{
    qobject_cast<QwuiHttpServer*>(httpServer())->setPort(port);
}

void QwuiApplicationServer::exec()
{
    QTimer::singleShot(0, this, SLOT(initialize()));
}

void QwuiApplicationServer::initialize()
{
    if (!start()) {
        qWarning(qobject_cast<QwuiHttpServer*>(httpServer())->error().toAscii().data());
    }
}
