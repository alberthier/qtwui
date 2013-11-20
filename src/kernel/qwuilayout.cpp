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

#include <QtWui/QwuiLayout>
#include <QtWui/QwuiWebget>

QwuiLayout::QwuiLayout(QwuiWebget* parent, Unit unit) :
    QObject(parent),
    m_enabled(true),
    m_spacing(4),
    m_unit(unit)
{
    if (parent != NULL) {
        parent->setLayout(this);
    }
}

QwuiLayout::QwuiLayout(Unit unit) :
    m_enabled(true),
    m_spacing(4),
    m_unit(unit)
{
}

QwuiLayout::~QwuiLayout()
{
}

QwuiWebget* QwuiLayout::parentWebget() const
{
    QwuiWebget* w = qobject_cast<QwuiWebget*>(parent());
    if (w != NULL) {
        return w;
    }
    QwuiLayout* l = qobject_cast<QwuiLayout*>(parent());
    if (l != NULL) {
        return l->parentWebget();
    }
    return NULL;
}

void QwuiLayout::removeWebget(QwuiWebget* w)
{
    int i = indexOf(w);
    if (i != -1) {
        removeItem(itemAt(i));
    }
}

bool QwuiLayout::isEnabled() const
{
    return m_enabled;
}

void QwuiLayout::setEnabled(bool enable)
{
    m_enabled = enable;
}

void QwuiLayout::setSpacing(int s)
{
    m_spacing = s;
}

int QwuiLayout::spacing() const
{
    return m_spacing;
}

QwuiLayoutItem::ItemType QwuiLayout::itemType() const
{
    return LayoutItem;
}


QwuiLayout::Unit QwuiLayout::unit() const
{
    return m_unit;
}

void QwuiLayout::setUnit(QwuiLayout::Unit u)
{
    m_unit = u;
}

QString QwuiLayout::unitToString() const
{
    switch (m_unit) {
        case Em:
            return "em";
            break;
        case Pixel:
            return "px";
            break;
        case RelativeStrength:
            return "%";
            break;
    }
    return QString::null;
}

