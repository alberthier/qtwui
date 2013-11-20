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

#ifndef QWUIFILERESSOURCEPROVIDER_H
#define QWUIFILERESSOURCEPROVIDER_H

#include <QtWui/QwuiAbstractResourceProvider>
#include <QtCore/QString>
#include <QtWui/QwuiGlobal>

/**
 * \brief A resource provider that provides file resources.
 * When provide() is called, the resource provider looks for a file that corresponds to the path
 * given in the header relatively to the rootDirectory().
 */
class QTWUI_EXPORT QwuiFileResourceProvider : public QwuiAbstractResourceProvider
{
    Q_OBJECT

public:
    QwuiFileResourceProvider(const QString& sessionId = QString::null);
    virtual ~QwuiFileResourceProvider();

    /**
     * @param path path of the file resources root directory.
     */
    void setRootDirectory(const QString& path);

    /**
     * @return path of the file resources root directory.
     */
    QString rootDirectory() const;

    QwuiAbstractResource* provide(const QHttpRequestHeader& header, const QString& postContent);

private:
    QString m_rootDir;
};

#endif // QWUIFILERESSOURCEPROVIDER_H
