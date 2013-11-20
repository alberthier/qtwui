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

#ifndef QWUIGRIDLAYOUT_H
#define QWUIGRIDLAYOUT_H

#include <QtWui/QwuiLayout>
#include <QtCore/QList>
#include <QtCore/QPair>
#include <QtWui/QwuiGlobal>

/**
 * \brief A grid layout.
 * This layout can be used to organise child widgets in a table.
 */
class QTWUI_EXPORT QwuiGridLayout : public QwuiLayout
{
    Q_OBJECT
public:
    QwuiGridLayout(QwuiWebget* parent, Unit unit = RelativeStrength);
    QwuiGridLayout(Unit unit = RelativeStrength);
    virtual ~QwuiGridLayout();
    virtual LayoutType type() const;
    virtual void insertItem(QwuiLayoutItem* item, int row, int column, int rowSpan = 1, int columnSpan = 1);
    void insertWebget(QwuiWebget* w, int row, int column, int rowSpan = 1, int columnSpan = 1);
    void insertStretch(int row, int column, int rowSpan = 1, int columnSpan = 1);
    virtual void removeItem(QwuiLayoutItem* item);
    void setRowSize(int row, int size);
    int rowSize(int row);
    void setColumnSize(int column, int size);
    int columnSize(int column);
    int rowCount() const;
    int columnCount() const;
    virtual int count() const;
    virtual int indexOf(QwuiWebget* w) const;
    QPair<int, int> coordsOf(QwuiLayoutItem* item) const;
    virtual bool contains(QwuiWebget* w) const;
    virtual QwuiLayoutItem* itemAt(int index) const;
    virtual QwuiLayoutItem* takeAt(int index);
    virtual void render();

private:
    void expandTo(int rows, int columns);
    void reduce();

private:
    class Item
    {
    public:
        Item() :
            m_item(NULL),
            m_rowSpan(0),
            m_columnSpan(0)
        {
        }
        ~Item()
        {
            delete m_item;
        }
        QwuiLayoutItem* m_item;
        int m_rowSpan;
        int m_columnSpan;
    };
    typedef QList<Item> ItemList;
    typedef QList<ItemList> ItemMatrix;
    ItemMatrix m_items;
    QList<int> m_rowSizes;
    QList<int> m_columnSizes;
    int m_count;
};

#endif // QWUIGRIDLAYOUT_H
