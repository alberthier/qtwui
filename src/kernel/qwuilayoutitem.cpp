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

#include <QtWui/QwuiLayoutItem>
#include <QtWui/QwuiWebget>

QwuiLayoutItem::QwuiLayoutItem()
{
}

QwuiLayoutItem::~QwuiLayoutItem()
{
}

QwuiWebgetItem::QwuiWebgetItem(QwuiWebget* w) :
    QwuiLayoutItem(),
    m_webget(w)
{
}

QwuiWebgetItem::~QwuiWebgetItem()
{
}

QwuiWebget* QwuiWebgetItem::webget() const
{
    return m_webget;
}

QwuiLayoutItem::ItemType QwuiWebgetItem::itemType() const
{
    return WebgetItem;
}

void QwuiWebgetItem::render()
{
    m_webget->render();
}

QwuiSpacerItem::QwuiSpacerItem() :
    QwuiLayoutItem()
{
}

QwuiSpacerItem::~QwuiSpacerItem()
{
}

QwuiLayoutItem::ItemType QwuiSpacerItem::itemType() const
{
    return SpacerItem;
}

void QwuiSpacerItem::render()
{
}
