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

#ifndef QWUIAPPLICATION_H
#define QWUIAPPLICATION_H

#include <QtCore/QObject>
#include <QtCore/QSet>
#include <QtWui/QwuiAbstractResourceProvider>
#include <QtWui/QwuiParameters>
#include <QtWui/QwuiGlobal>

class QIODevice;
class QHttpRequestHeader;
class QwuiWebget;
class QwuiFileResourceProvider;

/**
 * \brief The main class used for all web application sessions.
 * This class has to be created by the web main method and represents the session application.
 * For an example, see QwuiApplicationFactory
 */
class QTWUI_EXPORT QwuiApplication : public QwuiAbstractResourceProvider
{
    Q_OBJECT

public:
    QwuiApplication(const QString& sessionId = QString::null);
    virtual ~QwuiApplication();

    /**
     * This methid is called by the web server and generates the HTML code for the web pages.
     * @param header HTTP header
     * @param postContent HTTP post content.
     * @return The resource corresponding to the HTTP request.
     */
    QwuiAbstractResource* provide(const QHttpRequestHeader& header, const QString& postContent);

    /**
     * @param w the main webget for the web application.
     */
    void setMainWebget(QwuiWebget* w);

    /**
     * @param javascriptDir the directory containing the javascript files.
     */
    void setJavascriptDir(const QString& javascriptDir);

    /**
     * @return the directory containing the javascript files.
     */
    QString javascriptDir() const;


    /**
     * @param styleSheetsDir the directory containing the CSS files.
     */
    void setStyleSheetsDir(const QString& styleSheetsDir);

    /**
     * @return the directory containing the CSS files.
     */
    QString styleSheetDir() const;

    /**
     * @return the URL parameters.
     */
    QwuiParameters parameters() const;

    /**
     * @return device used to send the data to the client.
     */
    QIODevice* device();

    /**
     * @param webget that the client must update dynamically with AJAX.
     */
    void addWebgetToUpdate(const QwuiWebget* webget);

private:
    QwuiWebget* m_mainWebget;
    QwuiFileResourceProvider* m_fileProvider;
    QIODevice* m_device;
    QString m_javascriptDir;
    QString m_styleSheetsDir;
    QwuiParameters m_parameters;
    QSet<const QwuiWebget*> m_webgetsToUpdate;
};

#endif // QWUIAPPLICATION_H
