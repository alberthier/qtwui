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

#ifndef QWUIBOXLAYOUT_H
#define QWUIBOXLAYOUT_H

#include <QtWui/QwuiLayout>
#include <QtCore/QList>
#include <QtCore/QPair>
#include <QtWui/QwuiGlobal>

/**
 * \brief Box layout used to lay out widgets horizontally or vertically.
 * This is the base class used for QwuiHBoxLayout and QwuiVBoxLayout
 */
class QTWUI_EXPORT QwuiBoxLayout : public QwuiLayout
{
    Q_OBJECT
public:
    QwuiBoxLayout(QwuiWebget* parent, Unit unit = RelativeStrength);
    QwuiBoxLayout(Unit unit = RelativeStrength);
    virtual ~QwuiBoxLayout();
    virtual void addItem(QwuiLayoutItem* item, int size = 1);
    void addWebget(QwuiWebget* w, int size = 1);
    void addLayout(QwuiLayout* l, int size = 1);
    void addStretch(int size = 1);
    virtual void insertItem(int index, QwuiLayoutItem* item, int size = 1);
    void insertWebget(int index, QwuiWebget* w, int size = 1);
    void insertLayout(int index, QwuiLayout* l, int size = 1);
    void insertStretch(int index, int size = 1);
    virtual void removeItem(QwuiLayoutItem* item);
    virtual int count() const;
    virtual int indexOf(QwuiWebget* w) const;
    virtual bool contains(QwuiWebget* w) const;
    virtual QwuiLayoutItem* itemAt(int index) const;
    virtual QwuiLayoutItem* takeAt(int index);
    void itemSize(int index, int size);

protected:
    QPair<QwuiLayoutItem*, int> boxItemAt(int index) const;

private:
    typedef QList<QPair<QwuiLayoutItem*, int> > ItemList;
    ItemList m_items;
};

/**
 * \brief Layout used to dispose webgets horizontally
 */
class QTWUI_EXPORT QwuiHBoxLayout : public QwuiBoxLayout
{
    Q_OBJECT
public:
    QwuiHBoxLayout(QwuiWebget* parent, Unit unit = RelativeStrength);
    QwuiHBoxLayout(Unit unit = RelativeStrength);
    virtual ~QwuiHBoxLayout();
    virtual LayoutType type() const;
    virtual void render();
};

/**
 * \brief Layout used to dispose webgets vertically.
 */
class QTWUI_EXPORT QwuiVBoxLayout : public QwuiBoxLayout
{
    Q_OBJECT
public:
    QwuiVBoxLayout(QwuiWebget* parent, Unit unit = RelativeStrength);
    QwuiVBoxLayout(Unit unit = RelativeStrength);
    virtual ~QwuiVBoxLayout();
    virtual LayoutType type() const;
    virtual void render();
};

#endif // QWUIBOXLAYOUT_H
