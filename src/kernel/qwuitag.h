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

#ifndef QWUITAG_H
#define QWUITAG_H

#include <QtCore/QHash>
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtWui/QwuiGlobal>

class QwuiWebget;
class QTextStream;

/**
 * \brief A helper class used to generate HTML tags.
 */
class QTWUI_EXPORT QwuiTag
{
public:
    QwuiTag(QwuiWebget* w, const QString& tag);
    QwuiTag(QwuiTag* parent, const QString& tag);
    virtual ~QwuiTag();

    void setAttribute(const QString& name, const QString& value);
    QString attribute(const QString& name) const;

    void setText(const QString& text);
    QString text() const;

private:
    void generate(QTextStream* stream);

private:
    QString m_tag;
    QwuiWebget* m_webget;
    bool m_emptyTag;
    QString m_text;
    QHash<QString, QString> m_attributes;
    QList<QwuiTag*> m_children;
};

#endif // QWUITAG_H
