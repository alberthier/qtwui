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

#include <QtWui/QwuiFileResource>
#include <QtCore/QUrl>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>

#define READ_BUFFER_SIZE 4096

QwuiFileResource::QwuiFileResource(const QString& path) :
    QwuiAbstractResource(path)
{
}

QwuiFileResource::~QwuiFileResource()
{
}

QString QwuiFileResource::mimeType() const
{
    return "";
    //return "application/octet-stream";
}

qint64 QwuiFileResource::length() const
{
    QUrl fileUrl(path());
    QFileInfo fi(fileUrl.path());
    if (fi.exists() && fi.isFile()) {
        return fi.size();
    }
    return -1;
}

void QwuiFileResource::sendToDevice(QIODevice* dev) const
{
    QUrl fileUrl(path());
    if (exists()) {
        QFile file(fileUrl.path());
        if (file.open(QIODevice::ReadOnly)) {
            char data[READ_BUFFER_SIZE];
            qint64 bytesRead = file.read(data, READ_BUFFER_SIZE);
            while (bytesRead != 0) {
                if (!dev->isOpen()) {
                    return;
                }
                if (dev->write(data, bytesRead) != bytesRead) {
                    return;
                }
                bytesRead = file.read(data, READ_BUFFER_SIZE);
            }
        }
    }
}
