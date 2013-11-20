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

#ifndef HANGMAN_H
#define HANGMAN_H

#include <QtWui/QwuiWebget>
#include <QtGui/QImage>

class QwuiLabel;
class Game;

class HangMan : public QwuiWebget
{
    Q_OBJECT
public:
    HangMan(QwuiWebget* parent = NULL, const QString& webName = QString::null);
    virtual ~HangMan();

private:
    void updateImage(int steps);
    void updateCharacters(const QString& usedLetters = QString::null);

private slots:
    void letterClicked(const QString& link);
    void newGame(const QString& link);

private:
    QwuiLabel* m_title;
    QwuiLabel* m_word;
    QwuiLabel* m_image;
    QwuiLabel* m_letterBox;
    Game* m_game;
    QImage m_errorsImage;
};

#endif // HANGMAN_H
