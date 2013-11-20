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

#include <QtWui/QwuiFileResourceProvider>
#include <QtNetwork/QHttpRequestHeader>
#include <QtWui/QwuiFileResource>

QwuiFileResourceProvider::QwuiFileResourceProvider(const QString& sessionId) :
    QwuiAbstractResourceProvider(sessionId),
    m_rootDir(".")
{
}

QwuiFileResourceProvider::~QwuiFileResourceProvider()
{
}

QwuiAbstractResource* QwuiFileResourceProvider::provide(const QHttpRequestHeader& header, const QString& postContent)
{
    Q_UNUSED(postContent);

    return new QwuiFileResource(m_rootDir + header.path());
}

void QwuiFileResourceProvider::setRootDirectory(const QString& path)
{
    m_rootDir = path;
}

QString QwuiFileResourceProvider::rootDirectory() const
{
    return m_rootDir;
}
