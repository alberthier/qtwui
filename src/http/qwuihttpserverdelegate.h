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

#ifndef QWUIHTTPSERVERWORKINGTHREAD_H
#define QWUIHTTPSERVERWORKINGTHREAD_H

#include <QtWui/QwuiAbstractHttpServerDelegate>
#include <QtWui/QwuiGlobal>

/**
 * \brief Concrete imlementation of the HTTP server delegate.
 * This class handles uses a socket descriptor and uses it to transmit the requested resources.
 */
class QTWUI_EXPORT QwuiHttpServerDelegate : public QwuiAbstractHttpServerDelegate
{
    Q_OBJECT

public:
    QwuiHttpServerDelegate(QwuiResourceProviderServer* providerServer = NULL, int socketDescriptor = 0);
    virtual ~QwuiHttpServerDelegate();

protected:
    virtual QIODevice* createDevice();
    virtual void deleteDevice(QIODevice* device);
    virtual QHttpRequestHeader readHttpRequestHeader();
    virtual QString readHttpRequestContent();
    virtual void writeHttpResponseHeader(const QHttpResponseHeader& responseHeader);

private:
    int m_socketDescriptor;
    uint m_requestContentLength;
};

#endif // QWUIHTTPSERVERWORKINGTHREAD_H
