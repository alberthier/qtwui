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

#include <QtWui/QwuiMessageResource>
#include <QtCore/QTextStream>

QwuiMessageResource::QwuiMessageResource(const QString& path) :
    QwuiAbstractResource(path)
{
}

QwuiMessageResource::~QwuiMessageResource()
{
}

QString QwuiMessageResource::mimeType() const
{
    return "text/html";
}

qint64 QwuiMessageResource::length() const
{
    return message().length();
}

void QwuiMessageResource::sendToDevice(QIODevice* dev) const
{
    QTextStream stream(dev);
    stream << message();
}

void QwuiMessageResource::setMessage(const QString& message)
{
    m_message = message;
}

QString QwuiMessageResource::message() const
{
    return m_message;
}
