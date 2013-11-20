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

#ifndef QWUILAYOUTITEM_H
#define QWUILAYOUTITEM_H

#include <QtCore/QString>
#include <QtWui/QwuiGlobal>

class QwuiWebget;
class QwuiParameters;

class QTWUI_EXPORT QwuiLayoutItem
{
public:
    enum ItemType {
        WebgetItem,
        SpacerItem,
        LayoutItem
    };
public:
    QwuiLayoutItem();
    virtual ~QwuiLayoutItem();
    virtual ItemType itemType() const = 0;
    virtual void render() = 0;
};

class QwuiWebgetItem : public QwuiLayoutItem
{
public:
    QwuiWebgetItem(QwuiWebget* w);
    virtual ~QwuiWebgetItem();
    QwuiWebget* webget() const;
    virtual ItemType itemType() const;
    virtual void render();

private:
    QwuiWebget* m_webget;
};

class QwuiSpacerItem : public QwuiLayoutItem
{
public:
    QwuiSpacerItem();
    virtual ~QwuiSpacerItem();
    virtual ItemType itemType() const;
    virtual void render();
};

#endif // QWUILAYOUTITEM_H
