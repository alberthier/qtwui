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

#ifndef QWUILAYOUT_H
#define QWUILAYOUT_H

#include <QtCore/QObject>
#include <QtWui/QwuiLayoutItem>
#include <QtWui/QwuiGlobal>

class QwuiParameters;
class QIODevice;

/**
 * \brief Base class for all layouts.
 * A layout is used to organise child webgets within a parent webget.
 */
class QTWUI_EXPORT QwuiLayout : public QObject, public QwuiLayoutItem
{
    Q_OBJECT
public:
    enum LayoutType {
        HBoxLayout,
        VBoxLayout,
        GridLayout,
        StackedLayout
    };
    enum Unit {
        Em,
        Pixel,
        RelativeStrength
    };

public:
    QwuiLayout(QwuiWebget* parent, Unit unit = RelativeStrength);
    QwuiLayout(Unit unit = RelativeStrength);
    virtual ~QwuiLayout();
    QwuiWebget* parentWebget() const;
    virtual LayoutType type() const = 0;
    virtual void removeItem(QwuiLayoutItem* item) = 0;
    void removeWebget(QwuiWebget* w);
    virtual int count() const = 0;
    virtual int indexOf(QwuiWebget* w) const = 0;
    virtual bool contains(QwuiWebget* w) const = 0;
    virtual QwuiLayoutItem* itemAt(int index) const = 0;
    virtual QwuiLayoutItem* takeAt(int index) = 0;
    bool isEnabled() const;
    void setEnabled(bool enable);
    void setSpacing(int s);
    int spacing() const;
    ItemType itemType() const;
    virtual void render() = 0;
    Unit unit() const;
    void setUnit(Unit u);
    QString unitToString() const;

private:
    bool m_enabled;
    int m_spacing;
    Unit m_unit;

    friend class QwuiWebget;
};

#endif // QWUILAYOUT_H
