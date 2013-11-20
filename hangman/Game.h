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

#ifndef GAME_H
#define GAME_H

#include <QtCore/QObject>
#include <QtCore/QStringList>

class Game : public QObject
{
    Q_OBJECT
public:
    Game(QObject* parent = NULL);
    virtual ~Game();

    void newGame();
    int errorCount() const;
    void setMaxErrorCount(int max);
    int maxErrorCount() const;
    bool play(QChar c);
    void setWordsList(const QStringList wl);
    QStringList wordsList() const;
    QString usedCharacters() const;
    QString foundWord() const;
    bool isFinished();
    bool hasWon();

signals:
    void victory();
    void defeat();

private:
    QStringList m_wordsList;
    QString m_current;
    int m_errors;
    int m_maxErrors;
    QString m_usedCharacters;
    QString m_foundWord;
};

#endif // GAME_H
