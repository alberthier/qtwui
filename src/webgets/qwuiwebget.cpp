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

#include <QtWui/QwuiWebget>
#include <QtCore/QTextStream>
#include <QtCore/QIODevice>
#include <QtCore/QEvent>
#include <QtWui/QwuiApplication>
#include <QtWui/QwuiLayout>
#include <QtWui/QwuiTag>

QwuiWebget::QwuiWebget(QwuiWebget* parent, const QString& webName) :
    QObject(parent),
    m_webApp(NULL),
    m_layout(NULL)
{
    if (parent != NULL) {
        parent->update();
    }
    setWebName(webName);
    addStyleSheet("qwuiwebget.css");
}

QwuiWebget::~QwuiWebget()
{
    QwuiWebget* p = qobject_cast<QwuiWebget*>(parent());
    if (p != NULL) {
        if (p->layout() != NULL) {
            p->layout()->removeWebget(this);
        }
    }
}

void QwuiWebget::setWebName(const QString& webName)
{
    m_webName = webName;
}

QString QwuiWebget::webName() const
{
    if (m_webName.isEmpty()) {
        return objectName();
    }
    return m_webName;
}

QString QwuiWebget::webPath() const
{
    QwuiWebget* w = qobject_cast<QwuiWebget*>(parent());
    if (w != NULL) {
        return w->webPath() + "." + webName();
    }
    return webName();
}

void QwuiWebget::setWebId(const QString& webId)
{
    m_webId = webId;
}

QString QwuiWebget::webId() const
{
    if (m_webId.isEmpty()) {
        return webPath(); // Compute SHA1 of webPath available in Qt 4.3
    }
    return m_webId;
}

void QwuiWebget::setWebClass(const QString& webClass)
{
    m_webClass = webClass;
}

QString QwuiWebget::webClass() const
{
    if (m_webClass.isEmpty()) {
        return metaObject()->className();
    }
    return m_webClass;
}

QString QwuiWebget::invoke(const QString& call)
{
    int sep = call.indexOf('.');
    if (sep == -1) {
        sep = call.length();
    }
    QString thisPath = call.mid(0, sep);
    QString nextPath = call.mid(sep + 1);
    QString mimeType;

    if (thisPath == webName()) {
        if (nextPath.isEmpty()) {
            render(mimeType);
            return mimeType;
        } else {
            QListIterator<QObject*> it(children());
            QwuiWebget* w = NULL;

            while (it.hasNext()) {
                w = qobject_cast<QwuiWebget*>(it.next());
                if (w != NULL) {
                    mimeType = w->invoke(nextPath);
                    if (!mimeType.isNull()) {
                        return mimeType;
                    }
                }
            }
            if (QMetaObject::invokeMethod(this, nextPath.toAscii(), QArgument<QString>("QString&", mimeType))) {
                return mimeType;
            }
        }
    }

    return QString::null;
}

void QwuiWebget::addStyleSheet(const QString& css)
{
    m_cssFiles.insert(css);
}

void QwuiWebget::addJavaScript(const QString& js)
{
    m_jsFiles.insert(js);
}

QSet<QString> QwuiWebget::styleSheets() const
{
    QSet<QString> res = m_cssFiles;

    QListIterator<QObject*> it(children());
    QwuiWebget* w = NULL;
    while (it.hasNext()) {
        w = qobject_cast<QwuiWebget*>(it.next());
        if (w != NULL) {
            res.unite(w->styleSheets());
        }
    }
    return res;
}

QSet<QString> QwuiWebget::javascriptFiles() const
{
    QSet<QString> res = m_jsFiles;

    QListIterator<QObject*> it(children());
    QwuiWebget* w = NULL;
    while (it.hasNext()) {
        w = qobject_cast<QwuiWebget*>(it.next());
        if (w != NULL) {
            res.unite(w->javascriptFiles());
        }
    }
    return res;
}

QwuiApplication* QwuiWebget::webApp() const
{
    if (m_webApp != NULL) {
        return m_webApp;
    }
    for(QObject* o = parent(); o != NULL; o = o->parent()) {
        const_cast<QwuiWebget*>(this)->m_webApp = qobject_cast<QwuiApplication*>(o);
        if (m_webApp != NULL) {
            return m_webApp;
        }
    }
    return NULL;
}

void QwuiWebget::setLayout(QwuiLayout* l)
{
    delete m_layout;
    m_layout = l;
    if (m_layout != NULL) {
        m_layout->setParent(this);
    }
}

QwuiLayout* QwuiWebget::layout() const
{
    return m_layout;
}

QIODevice* QwuiWebget::device() const
{
    return webApp()->device();
}

void QwuiWebget::setStyleItem(const QString& item, const QString& value)
{
    m_styleItems[item] = value;
}

QString QwuiWebget::styleItem(const QString& item) const
{
    QHash<QString, QString>::ConstIterator it = m_styleItems.find(item);
    if (it == m_styleItems.end()) {
        return QString::null;
    }
    return it.value();
}

void QwuiWebget::setBorderWidth(int w)
{
    setStyleItem("border-width", QString::number(w));
}

int QwuiWebget::borderWidth() const
{
    QString s = styleItem("border-width");
    bool ok = false;
    int w = s.toInt(&ok);
    if (!ok) {
        return 0;
    }
    return w;
}

void QwuiWebget::setBorderColor(const QColor& c)
{
    setStyleItem("border-color", c.name());
}

QColor QwuiWebget::borderColor() const
{
    return styleItem("border-width");
}

void QwuiWebget::setBackgroundColor(const QColor& c)
{
    setStyleItem("background-color", c.name());
}

QColor QwuiWebget::backgroundColor() const
{
    return styleItem("background-color");
}

void QwuiWebget::setBorderStyle(Qt::QwuiBorderStyle s)
{
    switch (s) {
        case Qt::NoneStyle:
            setStyleItem("border-style", "none");
            break;
        case Qt::HiddenStyle:
            setStyleItem("border-style", "hidden");
            break;
        case Qt::DottedStyle:
            setStyleItem("border-style", "dotted");
            break;
        case Qt::DashedStyle:
            setStyleItem("border-style", "dashed");
            break;
        case Qt::SolidStyle:
            setStyleItem("border-style", "solid");
            break;
        case Qt::DoubleStyle:
            setStyleItem("border-style", "double");
            break;
        case Qt::GrooveStyle:
            setStyleItem("border-style", "groove");
            break;
        case Qt::RidgeStyle:
            setStyleItem("border-style", "ridge");
            break;
        case Qt::InsetStyle:
            setStyleItem("border-style", "inset");
            break;
        case Qt::OutsetStyle:
            setStyleItem("border-style", "outset");
            break;
        default:
            setStyleItem("border-style", "none");
            break;
    }
}

Qt::QwuiBorderStyle QwuiWebget::borderStyle() const
{
    QString s = styleItem("border-style");
    if (s == "none") {
        return Qt::NoneStyle;
    } else if (s == "hidden") {
        return Qt::HiddenStyle;
    } else if (s == "dotted") {
        return Qt::DottedStyle;
    } else if (s == "dashed") {
        return Qt::DashedStyle;
    } else if (s == "solid") {
        return Qt::SolidStyle;
    } else if (s == "double") {
        return Qt::DoubleStyle;
    } else if (s == "groove") {
        return Qt::GrooveStyle;
    } else if (s == "ridge") {
        return Qt::RidgeStyle;
    } else if (s == "inset") {
        return Qt::InsetStyle;
    } else if (s == "outset") {
        return Qt::OutsetStyle;
    }
    return Qt::NoneStyle;
}

void QwuiWebget::setTextColor(const QColor& c)
{
    setStyleItem("color", c.name());
}

QColor QwuiWebget::textColor() const
{
    return styleItem("color");
}

void QwuiWebget::setAlignment(const Qt::Alignment a)
{
    switch (a) {
        case Qt::AlignLeft:
            setStyleItem("text-align", "left");
            break;
        case Qt::AlignRight:
            setStyleItem("text-align", "right");
            break;
        case Qt::AlignHCenter:
            setStyleItem("text-align", "center");
            break;
        case Qt::AlignJustify:
            setStyleItem("text-align", "justify");
            break;
    }
}

Qt::Alignment QwuiWebget::alignment() const
{
    QString s = styleItem("text-align");
    if (s == "left") {
        return Qt::AlignLeft;
    } else if (s == "right") {
        return Qt::AlignRight;
    } else if (s == "center") {
        return Qt::AlignHCenter;
    } else if (s == "justify") {
        return Qt::AlignJustify;
    }
    return Qt::AlignLeft;
}


void QwuiWebget::update()
{
    QwuiApplication* a = webApp();
    if (a != NULL) {
        a->addWebgetToUpdate(this);
    }
}

void QwuiWebget::render(QString& mimeType)
{
    mimeType = "text/html";
    render();
}

void QwuiWebget::render()
{
    QwuiTag tag(this, "div");
}

void QwuiWebget::renderContent()
{
    QIODevice* dev = device();
    if (dev == NULL) {
        return;
    }
    QTextStream stream(dev);
    QListIterator<QObject*> it(children());
    QwuiWebget* w;

    if (m_layout != NULL) {
        m_layout->render();
        stream.flush();
    }
    while (it.hasNext()) {
        w = qobject_cast<QwuiWebget*>(it.next());
        if (w != NULL && (m_layout == NULL || !m_layout->contains(w))) {
            w->render();
            stream.flush();
        }
    }
}

bool QwuiWebget::event(QEvent* e)
{
    if (e->type() == QEvent::ParentChange) {
        QwuiWebget* w = qobject_cast<QwuiWebget*>(parent());
        if (w != NULL) {
            w->update();
        }
    }
    return QObject::event(e);
}

void QwuiWebget::setWebApp(QwuiApplication* app)
{
    m_webApp = app;
}
