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

#ifndef QWUISTACKEDWEBGET_H
#define QWUISTACKEDWEBGET_H

#include <QtWui/QwuiWebget>
#include <QtWui/QwuiGlobal>

/**
 * @brief A stacked webget container.
 */
class QTWUI_EXPORT QwuiStackedWebget : public QwuiWebget
{
    Q_OBJECT

public:
    QwuiStackedWebget(QwuiWebget* parent = NULL, const QString& webName = QString::null);
    virtual ~QwuiStackedWebget();

    int addWebget(QwuiWebget* w);
    int count() const;
    int currentIndex() const;
    QwuiWebget* currentWebget() const;
    int indexOf(QwuiWebget* w) const;
    int insertWebget(int index, QwuiWebget* w);
    void removeWebget(QwuiWebget* w);
    QwuiWebget* webget(int index) const;

public slots:
    void setCurrentIndex(int index);
    void setCurrentWebget(QwuiWebget* w);

signals:
    void currentChanged(int index);
    void widgetRemoved(int index);
};

#endif // QWUISTACKEDWEBGET_H
