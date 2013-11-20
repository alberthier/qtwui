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
#ifndef QWUIAPPLICATIONSERVER_H
#define QWUIAPPLICATIONSERVER_H

#include <QtWui/QwuiResourceProviderServer>
#include <QtWui/QwuiApplicationCreator>
#include <QtWui/QwuiGlobal>

/**
 * \brief Application server.
 * The application server uses internally an HTTP server and an application factory to provide
 * application instances on demand.
 */
class QTWUI_EXPORT QwuiApplicationServer : public QwuiResourceProviderServer
{
    Q_OBJECT

public:
    /**
     * @param creatorFunction creator function to use to create new application instances.
     * @param parent parent object.
     */
    QwuiApplicationServer(QwuiApplicationCreator creatorFunction, QObject* parent = NULL);
    virtual ~QwuiApplicationServer();

    /**
     * @param port port to use for the built-in HTTP server.
     */
    void setBuiltInServerPort(quint16 port);

    /**
     * Starts the application server.
     */
    void exec();

private slots:
    void initialize();
};

#endif // QWUIAPPLICATIONSERVER_H
