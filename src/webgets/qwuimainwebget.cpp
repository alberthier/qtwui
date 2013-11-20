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

#include <QtWui/QwuiMainWebget>
#include <QtCore/QTextStream>
#include <QtWui/QwuiApplication>

QwuiMainWebget::QwuiMainWebget(QwuiWebget* parent, const QString& webName) :
    QwuiWebget(parent, webName)
{
    addStyleSheet("qwuimainwebget.css");
}

QwuiMainWebget::~QwuiMainWebget()
{
}

void QwuiMainWebget::setTitle(const QString& title)
{
    m_title = title;
}

QString QwuiMainWebget::title() const
{
    return m_title;
}

void QwuiMainWebget::render()
{
    if (device() == NULL) {
        return;
    }
    QTextStream stream(device());

    QString jsDir(".");
    QString cssDir(".");
    QwuiApplication* app = webApp();
    if (app != NULL) {
        jsDir = app->javascriptDir();
        cssDir = app->styleSheetDir();
    }
    stream << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n"
            << "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
            << "<head>\n"
            << "<meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\" />\n"
            << "<meta http-equiv=\"Cache-Control\" content=\"no-cache, must-revalidate\">\n"
            << "<meta http-equiv=\"Pragma\" content=\"no-cache\">\n"
            << "<meta http-equiv=\"Expires\" content=\"0\">\n"
            << "<title>" << title() << "</title>\n"
            << "<link href=\"" << cssDir << "/qtwui.css\" rel=\"stylesheet\" type=\"text/css\" />\n";
    foreach (const QString& css, styleSheets()) {
        stream << "<link href=\"" << cssDir << "/" << css << "\" rel=\"stylesheet\" type=\"text/css\" />\n";
    }

    stream << "<script src=\"" << jsDir << "/prototype.js\" type=\"text/javascript\"></script>\n";
    stream << "<script src=\"" << jsDir << "/qtwui.js\" type=\"text/javascript\"></script>\n";
    foreach (const QString& js, javascriptFiles()) {
        stream << "<script src=\"" << jsDir << "/" << js << "\" type=\"text/javascript\"></script>\n";
    }

    stream << "</head>\n<body class=\"" << webClass() << "\" id=\"" << webId() << "\">\n";
    stream.flush();

    renderContent();

    stream << "</body>\n</html>\n";
    stream.flush();
}
