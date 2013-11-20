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

#ifndef QWUIPARAMETERS_H
#define QWUIPARAMETERS_H

#include <QtCore/QHash>
#include <QtCore/QString>
#include <QtXml/QDomDocument>
#include <QtWui/QwuiGlobal>

class QHttpRequestHeader;

/**
 * \brief Parameters received from the client by the web server.
 */
class QTWUI_EXPORT QwuiParameters
{
public:
    QwuiParameters();
    virtual ~QwuiParameters();

    /**
     * Initializes the instance.
     * @param header HTTP request header
     * @param postContent HTTP post content.
     */
    void init(const QHttpRequestHeader& header, const QString& postContent = QString::null);

    /**
     * Clears the instance.
     */
    void clear();

    /**
     * @param key parameter name
     * @return the value corresponding to \a key or QString::null
     */
    QString operator[](const QString& key) const;

    /**
     * @param key parameter name
     * @return true if the URL had a parameter named \a key
     */
    bool contains(const QString& key) const;

    /**
     * @param key parameter name.
     * @return the value corresponding to the GET parameter \a key or QString::null
     */
    QString get(const QString& key) const;

    /**
     * @param key parameter name.
     * @return the value corresponding to the POST parameter \a key or QString::null
     */
    QString post(const QString& key) const;

    /**
     * @return XML data corresponding to the content of this instance
     */
    QDomElement xmlElement() const;

    /**
     * @return the content of the POST data.
     */
    QString postContent() const;

private:
    QHash<QString, QString> m_getParameters;
    QHash<QString, QString> m_postParameters;
    QDomDocument m_xmlDoc;
    QString m_postContent;
};

#endif // QWUIPARAMETERS_H
