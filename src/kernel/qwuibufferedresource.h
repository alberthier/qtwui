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

#ifndef QWUIBUFFEREDRESSOURCE_H
#define QWUIBUFFEREDRESSOURCE_H

#include <QtWui/QwuiAbstractResource>
#include <QtCore/QByteArray>
#include <QtWui/QwuiGlobal>

/**
 * \brief A resource that wraps a simple byte array.
 * This class makes it possible to send a buffer of data to the client.
 */
class QTWUI_EXPORT QwuiBufferedResource : public QwuiAbstractResource
{
public:
    /**
     * @param path path identifying the buffer content.
     * @param mimeType MIME-type of the buffer content.
     * @param source buffer data.
     */
    QwuiBufferedResource(const QString& path, const QString& mimeType, const QByteArray& source);
    virtual ~QwuiBufferedResource();

    virtual QString mimeType() const;
    virtual qint64 length() const;
    virtual void sendToDevice(QIODevice* dev) const;

private:
    QString m_mimeType;
    QByteArray m_source;
};

#endif // QWUIBUFFEREDRESSOURCE_H
