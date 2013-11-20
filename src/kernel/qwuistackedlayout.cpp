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

#include <QtWui/QwuiStackedLayout>
#include <QtWui/QwuiWebget>

QwuiStackedLayout::QwuiStackedLayout(QwuiWebget* parent) :
    QwuiLayout(parent),
    m_currentIndex(-1)
{
    connect(this, SIGNAL(currentChanged(int)), this, SLOT(updateParentWebget()));
}

QwuiStackedLayout::QwuiStackedLayout() :
    QwuiLayout(NULL),
    m_currentIndex(-1)
{
    connect(this, SIGNAL(currentChanged(int)), this, SLOT(updateParentWebget()));
}

QwuiStackedLayout::~QwuiStackedLayout()
{
    while (!m_items.isEmpty()) {
        delete m_items.takeFirst();
    }
}

QwuiLayout::LayoutType QwuiStackedLayout::type() const
{
    return QwuiLayout::StackedLayout;
}

int QwuiStackedLayout::addWebget(QwuiWebget* w)
{
    return insertWebget(m_items.count(), w);
}

int QwuiStackedLayout::insertWebget(int index, QwuiWebget* w)
{
    return insertItem(index, new QwuiWebgetItem(w));
}

int QwuiStackedLayout::addItem(QwuiLayoutItem* item)
{
    return insertItem(m_items.count(), item);
}

int QwuiStackedLayout::insertItem(int index, QwuiLayoutItem* item)
{
    if (index < 0) {
        index = 0;
    } else if (index > m_items.count()) {
        index = m_items.count();
    }
    m_items.insert(index, item);
    if (m_currentIndex == -1) {
        m_currentIndex = 0;
        emit currentChanged(m_currentIndex);
    }
    return index;
}

void QwuiStackedLayout::removeItem(QwuiLayoutItem* item)
{
    int index = m_items.indexOf(item);
    if (index != -1) {
        m_items.removeAt(index);
        if (m_currentIndex == index && m_currentIndex != 0) {
            --m_currentIndex;
        }
        if (m_items.isEmpty()) {
            m_currentIndex = -1;
            emit currentChanged(m_currentIndex);
        }
        emit itemRemoved(index);
    }
}

int QwuiStackedLayout::count() const
{
    return m_items.count();
}

int QwuiStackedLayout::indexOf(QwuiWebget* w) const
{
    int i = 0;
    QList<QwuiLayoutItem*>::ConstIterator it = m_items.begin();
    QList<QwuiLayoutItem*>::ConstIterator itEnd = m_items.end();
    for (; it != itEnd; ++it) {
        if ((*it)->itemType() == QwuiLayoutItem::WebgetItem) {
            if (static_cast<QwuiWebgetItem*>(*it)->webget() == w) {
                return i;
            }
        }
        ++i;
    }
    return -1;
}

bool QwuiStackedLayout::contains(QwuiWebget* w) const
{
    return indexOf(w) != -1;
}

QwuiLayoutItem* QwuiStackedLayout::itemAt(int index) const
{
    if ((index < 0) || (index >= m_items.count())) {
        return NULL;
    }
    return m_items[index];
}

QwuiLayoutItem* QwuiStackedLayout::takeAt(int index)
{
    QwuiLayoutItem* item = itemAt(index);
    removeItem(item);
    return item;
}

int QwuiStackedLayout::currentIndex() const
{
    return m_currentIndex;
}

QwuiLayoutItem* QwuiStackedLayout::currentItem() const
{
    if (m_currentIndex != -1) {
        return m_items[m_currentIndex];
    }
    return NULL;
}

void QwuiStackedLayout::render()
{
    if (m_currentIndex != -1) {
        m_items[m_currentIndex]->render();
    }
}

void QwuiStackedLayout::setCurrentIndex(int index)
{
    if (index < 0) {
        index = 0;
    } else if (index >= m_items.count()) {
        index = m_items.count() - 1;
    }
    m_currentIndex = index;
    emit currentChanged(m_currentIndex);
}

void QwuiStackedLayout::setCurrentItem(QwuiLayoutItem* item)
{
    int index = m_items.indexOf(item);
    if (index != -1) {
        m_currentIndex = index;
        emit currentChanged(m_currentIndex);
    }
}

void QwuiStackedLayout::updateParentWebget()
{
    QwuiWebget* w = parentWebget();
    if (w != NULL) {
        w->update();
    }
}
