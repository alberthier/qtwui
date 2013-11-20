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

#ifndef QWUISTACKEDLAYOUT_H
#define QWUISTACKEDLAYOUT_H

#include <QtWui/QwuiLayout>
#include <QtCore/QList>
#include <QtWui/QwuiGlobal>

/**
 * \brief A stacked webgets layout.
 * This layout keeps a stack of webgets and displays only one at time.
 */
class QTWUI_EXPORT QwuiStackedLayout : public QwuiLayout
{
    Q_OBJECT

public:
    QwuiStackedLayout(QwuiWebget* parent);
    QwuiStackedLayout();
    virtual ~QwuiStackedLayout();
    virtual LayoutType type() const;
    int addWebget(QwuiWebget* w);
    int insertWebget(int index, QwuiWebget* w);
    int addItem(QwuiLayoutItem* item);
    int insertItem(int index, QwuiLayoutItem* item);
    virtual void removeItem(QwuiLayoutItem* item);
    virtual int count() const;
    virtual int indexOf(QwuiWebget* w) const;
    virtual bool contains(QwuiWebget* w) const;
    virtual QwuiLayoutItem* itemAt(int index) const;
    virtual QwuiLayoutItem* takeAt(int index);
    int currentIndex() const;
    QwuiLayoutItem* currentItem() const;
    virtual void render();

public slots:
    void setCurrentIndex(int index);
    void setCurrentItem(QwuiLayoutItem* item);

signals:
    void currentChanged(int index);
    void itemRemoved(int index);

private slots:
    void updateParentWebget();

private:
    QList<QwuiLayoutItem*> m_items;
    int m_currentIndex;
};

#endif // QWUISTACKEDLAYOUT_H
