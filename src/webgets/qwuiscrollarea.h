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

#ifndef QWUISCROLLAREA_H
#define QWUISCROLLAREA_H

#include <QtWui/QwuiWebget>
#include <QtWui/QwuiGlobal>

/**
 * @brief A simple scroll area webget.
 */
class QTWUI_EXPORT QwuiScrollArea : public QwuiWebget
{
    Q_OBJECT
public:
    QwuiScrollArea(QwuiWebget* parent = NULL, const QString& webName = QString::null);
    virtual ~QwuiScrollArea();
    void setWebget(QwuiWebget* w);
    QwuiWebget* takeWebget();
    QwuiWebget* webget() const;

protected:
    virtual void renderContent();

private:
    QwuiWebget* m_webget;
};

#endif // QWUISCROLLAREA_H
