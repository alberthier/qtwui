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

#include <QtWui/QwuiStackedWebget>
#include <QtWui/QwuiStackedLayout>

QwuiStackedWebget::QwuiStackedWebget(QwuiWebget* parent, const QString& webName) :
    QwuiWebget(parent, webName)
{
    QwuiStackedLayout* l = new QwuiStackedLayout(this);
    connect(l, SIGNAL(currentChanged(int)), this, SIGNAL(currentChanged(int)));
    connect(l, SIGNAL(itemRemoved(int)), this, SIGNAL(widgetRemoved(int)));
}

QwuiStackedWebget::~QwuiStackedWebget()
{
}

int QwuiStackedWebget::addWebget(QwuiWebget* w)
{
    w->setParent(this);
    return qobject_cast<QwuiStackedLayout*>(layout())->addWebget(w);
}

int QwuiStackedWebget::count() const
{
    return qobject_cast<QwuiStackedLayout*>(layout())->count();
}

int QwuiStackedWebget::currentIndex() const
{
    return qobject_cast<QwuiStackedLayout*>(layout())->currentIndex();
}

QwuiWebget* QwuiStackedWebget::currentWebget() const
{
    QwuiLayoutItem* item = qobject_cast<QwuiStackedLayout*>(layout())->currentItem();
    if (item != NULL) {
        return static_cast<QwuiWebgetItem*>(item)->webget();
    }
    return NULL;
}

int QwuiStackedWebget::indexOf(QwuiWebget* w) const
{
    return qobject_cast<QwuiStackedLayout*>(layout())->indexOf(w);
}

int QwuiStackedWebget::insertWebget(int index, QwuiWebget* w)
{
    return qobject_cast<QwuiStackedLayout*>(layout())->insertWebget(index, w);
}

void QwuiStackedWebget::removeWebget(QwuiWebget* w)
{
    QwuiStackedLayout* l = qobject_cast<QwuiStackedLayout*>(layout());
    l->removeItem(l->itemAt(l->indexOf(w)));
}

QwuiWebget* QwuiStackedWebget::webget(int index) const
{
    QwuiLayoutItem* item = qobject_cast<QwuiStackedLayout*>(layout())->itemAt(index);
    if (item != NULL) {
        return static_cast<QwuiWebgetItem*>(item)->webget();
    }
    return NULL;
}

void QwuiStackedWebget::setCurrentIndex(int index)
{
    qobject_cast<QwuiStackedLayout*>(layout())->setCurrentIndex(index);
}

void QwuiStackedWebget::setCurrentWebget(QwuiWebget* w)
{
    QwuiStackedLayout* l = qobject_cast<QwuiStackedLayout*>(layout());
    int index = l->indexOf(w);
    if (index != -1) {
        l->setCurrentIndex(index);
    }
}
