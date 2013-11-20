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

#ifndef QWUIWEBGET_H
#define QWUIWEBGET_H

#include <QtCore/QObject>
#include <QtWui/QwuiGlobal>
#include <QtCore/QString>
#include <QtCore/QHash>
#include <QtCore/QSet>
#include <QtGui/QColor>
#include <QtWui/QwuiGlobal>

class QIODevice;
class QTextStream;
class QwuiApplication;
class QwuiLayout;

/**
 * @brief The base class for all webgets.
 */
class QTWUI_EXPORT QwuiWebget : public QObject
{
    Q_OBJECT

public:
    /**
     * @param parent the parent webget.
     * @param webName the name used to indentify this webget in an URL. This is mandatory.
     */
    QwuiWebget(QwuiWebget* parent = NULL, const QString& webName = QString::null);
    virtual ~QwuiWebget();

    /**
     * The web name is used to indentify this webget in an URL. This is mandatory.
     * @param webName the new web name.
     */
    void setWebName(const QString& webName);

    /**
     * @return the web name.
     */
    QString webName() const;

    /**
     * Concatenes the web name of this webget and with its parents names.
     * @return The path part of the URL identifying this webget.
     */
    QString webPath() const;

    void setWebId(const QString& webId);
    QString webId() const;
    void setWebClass(const QString& webClass);
    QString webClass() const;
    virtual QString invoke(const QString& call);
    void addStyleSheet(const QString& css);
    void addJavaScript(const QString& js);
    QSet<QString> styleSheets() const;
    QSet<QString> javascriptFiles() const;
    QwuiApplication* webApp() const;
    void setLayout(QwuiLayout* l);
    QwuiLayout* layout() const;
    QIODevice* device() const;
    void setStyleItem(const QString& item, const QString& value);
    QString styleItem(const QString& item) const;
    void setBorderWidth(int w);
    int borderWidth() const;
    void setBorderColor(const QColor& c);
    QColor borderColor() const;
    void setBackgroundColor(const QColor& c);
    QColor backgroundColor() const;
    void setBorderStyle(Qt::QwuiBorderStyle s);
    Qt::QwuiBorderStyle borderStyle() const;
    void setTextColor(const QColor& c);
    QColor textColor() const;
    void setAlignment(const Qt::Alignment a);
    Qt::Alignment alignment() const;
    void update();

public slots:
    void render(QString& mimeType);

protected:
    virtual void render();
    virtual void renderContent();
    virtual bool event(QEvent* e);

private:
    void setWebApp(QwuiApplication* app);

private:
    QString m_webName;
    QString m_webId;
    QString m_webClass;
    QwuiApplication* m_webApp;
    QSet<QString> m_jsFiles;
    QSet<QString> m_cssFiles;
    QwuiLayout* m_layout;
    QHash<QString, QString> m_styleItems;
    Qt::Alignment m_align;

    friend class QwuiApplication;
    friend class QwuiLayout;
    friend class QwuiWebgetItem;
    friend class QwuiTag;
};

#endif // QWUIWEBGET_H
