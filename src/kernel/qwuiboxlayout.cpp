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

#include <QtWui/QwuiBoxLayout>
#include <QtCore/QIODevice>
#include <QtCore/QTextStream>
#include <QtWui/QwuiWebget>

QwuiBoxLayout::QwuiBoxLayout(QwuiWebget* parent, Unit unit) :
    QwuiLayout(parent, unit)
{
}

QwuiBoxLayout::QwuiBoxLayout(Unit unit) :
    QwuiLayout(unit)
{
}

QwuiBoxLayout::~QwuiBoxLayout()
{
    while (!m_items.isEmpty()) {
        delete m_items.takeFirst().first;
    }
}

void QwuiBoxLayout::addItem(QwuiLayoutItem* item, int size)
{
    insertItem(m_items.count(), item, size);
}

void QwuiBoxLayout::addWebget(QwuiWebget* w, int size)
{
    insertWebget(m_items.count(), w, size);
}

void QwuiBoxLayout::addLayout(QwuiLayout* l, int size)
{
    insertLayout(m_items.count(), l, size);
}

void QwuiBoxLayout::addStretch(int size)
{
    insertStretch(m_items.count(), size);
}

void QwuiBoxLayout::insertItem(int index, QwuiLayoutItem* item, int size)
{
    if (item->itemType() == QwuiLayoutItem::LayoutItem) {
        static_cast<QwuiLayout*>(item)->setParent(this);
    }
    if (size < 1) {
        size = 1;
    }
    m_items.insert(index, qMakePair(item, size));
}

void QwuiBoxLayout::insertWebget(int index, QwuiWebget* w, int size)
{
    insertItem(index, new QwuiWebgetItem(w), size);
}

void QwuiBoxLayout::insertLayout(int index, QwuiLayout* l, int size)
{
    insertItem(index, l, size);
}

void QwuiBoxLayout::insertStretch(int index, int size)
{
    insertItem(index, new QwuiSpacerItem(), size);
}

void QwuiBoxLayout::removeItem(QwuiLayoutItem* item)
{
    ItemList::Iterator it = m_items.begin();
    ItemList::Iterator itEnd = m_items.end();
    for (; it != itEnd; ++it) {
        if (it->first == item) {
            m_items.erase(it);
            break;
        }
    }
}

int QwuiBoxLayout::count() const
{
    return m_items.count();
}

int QwuiBoxLayout::indexOf(QwuiWebget* w) const
{
    int index = 0;
    ItemList::ConstIterator it = m_items.begin();
    ItemList::ConstIterator itEnd = m_items.end();
    for (; it != itEnd; ++it) {
        if (it->first->itemType() == QwuiLayoutItem::WebgetItem) {
            if (static_cast<QwuiWebgetItem*>(it->first)->webget() == w) {
                return index;
            }
            ++index;
        }
    }
    return -1;
}

bool QwuiBoxLayout::contains(QwuiWebget* w) const
{
    ItemList::ConstIterator it = m_items.begin();
    ItemList::ConstIterator itEnd = m_items.end();
    for (; it != itEnd; ++it) {
        switch (it->first->itemType()) {
            case QwuiLayoutItem::WebgetItem:
                if (static_cast<QwuiWebgetItem*>(it->first)->webget() == w) {
                    return true;
                }
                break;
            case QwuiLayoutItem::LayoutItem:
                if (static_cast<QwuiLayout*>(it->first)->contains(w)) {
                    return true;
                }
                break;
            case QwuiLayoutItem::SpacerItem:
                break;
            default:
                break;
        }
    }
    return false;
}

QwuiLayoutItem* QwuiBoxLayout::itemAt(int index) const
{
    if (index >= 0 && index < m_items.count()) {
        return m_items[index].first;
    }
    return NULL;
}

QwuiLayoutItem* QwuiBoxLayout::takeAt(int index)
{
    QwuiLayoutItem* item = NULL;
    if (index >= 0 && index < m_items.count()) {
        item = m_items[index].first;
        m_items.removeAt(index);
    }
    return item;
}

void QwuiBoxLayout::itemSize(int index, int size)
{
    if (index >= 0 && index < m_items.count()) {
        m_items[index].second = size;
    }
}

QPair<QwuiLayoutItem*, int> QwuiBoxLayout::boxItemAt(int index) const
{
    return m_items[index];
}

QwuiHBoxLayout::QwuiHBoxLayout(QwuiWebget* parent, Unit unit) :
    QwuiBoxLayout(parent, unit)
{
}

QwuiHBoxLayout::QwuiHBoxLayout(Unit unit) :
    QwuiBoxLayout(unit)
{
}

QwuiHBoxLayout::~QwuiHBoxLayout()
{
}

QwuiBoxLayout::LayoutType QwuiHBoxLayout::type() const
{
    return HBoxLayout;
}

void QwuiHBoxLayout::render()
{
    if (count() != 0) {
        QwuiWebget* p = parentWebget();
        if (p == NULL) {
            return;
        }
        QIODevice* dev = p->device();

        QTextStream stream(dev);
        stream << "<table class=\"QwuiHBoxLayout\"";
        if (spacing() >= 0) {
            stream << " cellspacing=\"" << spacing() << "\"";
        }
        stream << ">\n";
        stream << "<tr class=\"QwuiHBoxLayout\">\n";
        int max = 0;
        if (unit() == RelativeStrength) {
            for (int i = 0; i < count(); ++i) {
                max += boxItemAt(i).second;
            }
        }
        if (max == 0) {
            max = 1;
        }
        for (int i = 0; i < count(); ++i) {
            QPair<QwuiLayoutItem*, int> boxItem = boxItemAt(i);
            stream << "<td class=\"QwuiHBoxLayout\"";
            QString value;
            if (unit() == RelativeStrength) {
                value = QString::number(((float) boxItem.second / (float) max) * 100.0, 'f', 2);
            } else {
                value = QString::number(boxItem.second);
            }
            stream << " style=\"width:" << value << unitToString() << ";\"";
            stream << ">\n";
            stream.flush();
            boxItem.first->render();
            stream.flush();
            stream << "</td>\n";
        }
        stream << "</tr>\n";
        stream << "</table>\n";
        stream.flush();
    }
}

QwuiVBoxLayout::QwuiVBoxLayout(QwuiWebget* parent, Unit unit) :
        QwuiBoxLayout(parent, unit)
{
}

QwuiVBoxLayout::QwuiVBoxLayout(Unit unit) :
    QwuiBoxLayout(unit)
{
}

QwuiVBoxLayout::~QwuiVBoxLayout()
{
}

QwuiBoxLayout::LayoutType QwuiVBoxLayout::type() const
{
    return VBoxLayout;
}

void QwuiVBoxLayout::render()
{
    if (count() != 0) {
        QwuiWebget* p = parentWebget();
        if (p == NULL) {
            return;
        }
        QIODevice* dev = p->device();

        QTextStream stream(dev);
        stream << "<table class=\"QwuiVBoxLayout\"";
        if (spacing() >= 0) {
            stream << " cellspacing=\"" << spacing() << "\"";
        }
        stream << ">\n";
        int max = 0;
        if (unit() == RelativeStrength) {
            for (int i = 0; i < count(); ++i) {
                max += boxItemAt(i).second;
            }
        }
        if (max == 0) {
            max = 1;
        }
        for (int i = 0; i < count(); ++i) {
            QPair<QwuiLayoutItem*, int> boxItem = boxItemAt(i);
            QString style;
            QString value;
            if (unit() == RelativeStrength) {
                value = QString::number(((float) boxItem.second / (float) max) * 100.0, 'f', 2);
            } else {
                value = QString::number(boxItem.second);
            }
            style = " style=\"height:" + value + unitToString() + ";\"";
            stream << "<tr class=\"QwuiVBoxLayout\"";
            stream << style;
            stream << ">\n<td class=\"QwuiVBoxLayout\"";
            stream << style << ">\n";
            stream.flush();
            boxItem.first->render();
            stream.flush();
            stream << "</td>\n";
            stream << "</tr>\n";
        }
        stream << "</table>\n";
        stream.flush();
    }
}
