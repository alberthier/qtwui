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

#ifndef QWUIABSTRACTRESSOURCE_H
#define QWUIABSTRACTRESSOURCE_H

#include <QtCore/QString>
#include <QtWui/QwuiGlobal>

class QIODevice;

/**
 * \brief This class represents a resource that can be served by the web server.
 * A resource can be any type of information that can be served by a web server. Examples: an image file, a text file, some code generating HTML, etc...
 * A resource is identified by its MIME-type and this class provides the resource length, its path and is able
 * to send the resource to an QIODevice.
 */
class QTWUI_EXPORT QwuiAbstractResource
{
public:
    /**
     * @param path path of the resource.
     */
    QwuiAbstractResource(const QString& path = QString::null);
    virtual ~QwuiAbstractResource();

    /**
     * Subclasses must provide the MIME type of the resource like "text/html" or "image/jpeg".
     * @return the MIME type of the resource.
     */
    virtual QString mimeType() const = 0;

    /**
     * @return the length of the resource in bytes.
     */
    virtual qint64 length() const = 0;

    /**
     * @return the path identifying the resource. This is added to the URL by the HTTP server.
     */
    virtual QString path() const;


    /**
     * @return true if the resource exists, false otherwise.
     */
    virtual bool exists() const;

    /**
     * Writes the resource to \a dev
     * @param dev IO device to write to.
     */
    virtual void sendToDevice(QIODevice* dev) const = 0;

private:
    QString m_path;
};

#endif // QWUIABSTRACTRESSOURCE_H
