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

#include <QtWui/QwuiTag>
#include <QtCore/QTextStream>
#include <QtWui/QwuiWebget>
#include <QtWui/QwuiLayout>

QwuiTag::QwuiTag(QwuiWebget* w, const QString& tag) :
    m_tag(tag),
    m_webget(w)
{
}

QwuiTag::QwuiTag(QwuiTag* parent, const QString& tag) :
    m_tag(tag),
    m_webget(NULL)
{
    if (parent != NULL) {
        parent->m_children.append(this);
    }
}

QwuiTag::~QwuiTag()
{
    if (m_webget != NULL) {
        QTextStream stream(m_webget->device());
        generate(&stream);
    }
}

void QwuiTag::setAttribute(const QString& name, const QString& value)
{
    m_attributes[name] = value;
}

QString QwuiTag::attribute(const QString& name) const
{
    QHash<QString, QString>::ConstIterator it = m_attributes.find(name);
    if (it == m_attributes.end()) {
        return QString::null;
    }
    return it.value();
}

void QwuiTag::setText(const QString& text)
{
    m_text = text;
}

QString QwuiTag::text() const
{
    return m_text;
}

void QwuiTag::generate(QTextStream* stream)
{
    QHash<QString, QString> attributes(m_attributes);

    attributes["class"] = m_webget->webClass();
    attributes["id"] = m_webget->webId();
    QString& style = attributes["style"];
    if (!style.isEmpty() && style[style.size() - 1] != ';') {
        style += ";";
    }
    QHash<QString, QString>::ConstIterator it = m_webget->m_styleItems.begin();
    QHash<QString, QString>::ConstIterator itEnd = m_webget->m_styleItems.end();
    for (; it != itEnd; ++it) {
        style += it.key() + ":" + it.value() + ";";
    }
    *stream << QString("<") + m_tag;
    it = attributes.begin();
    itEnd = attributes.end();
    for (; it != itEnd; ++it) {
        if (!it.value().isEmpty()) {
            *stream << QString(" ") + it.key() + "=\"" + it.value() + "\"";
        }
    }
    if (m_webget != NULL || !m_children.isEmpty() || !m_text.isNull()) {
        *stream << ">\n";

        if (m_webget != NULL) {
            stream->flush();
            m_webget->renderContent();
        }
        while (!m_children.isEmpty()) {
            QwuiTag* tag = m_children.takeFirst();
            tag->generate(stream);
            tag->m_webget = NULL;
            delete tag;
        }
        if (!m_text.isNull()) {
            *stream << m_text;
        }
        *stream << "</" + m_tag + ">\n";
    } else {
        *stream << " />\n";
    }
    stream->flush();
}
