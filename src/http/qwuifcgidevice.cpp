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

#include <QtWui/QwuiFcgiDevice>
//#include <fcgi_stdio.h>

QwuiFcgiDevice::QwuiFcgiDevice(QObject* parent) :
    QIODevice(parent)
{
}

QwuiFcgiDevice::~QwuiFcgiDevice()
{
}

// QIODevice::eof == false -> stream is never eof
// QIODevice::bytesAvailable == feof(stdin)
// QIODevice::bytesToWrite == O;

qint64 QwuiFcgiDevice::readData(char* data, qint64 maxSize)
{
    Q_UNUSED(data);
    Q_UNUSED(maxSize);
//    return (quint64) fread(data, sizeof(char), maxSize, stdout);
    return 0;
}

qint64 QwuiFcgiDevice::writeData(const char * data, qint64 maxSize)
{
    Q_UNUSED(data);
    Q_UNUSED(maxSize);
//    return (quint64) fwrite(data, sizeof(char), maxSize, stdout);
    return 0;
}
