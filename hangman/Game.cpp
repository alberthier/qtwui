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

#include "Game.h"

Game::Game(QObject* parent) :
    QObject(parent),
    m_errors(0),
    m_maxErrors(10)
{
}

Game::~Game()
{
}

void Game::newGame()
{
    m_errors = 0;
    if (!m_wordsList.isEmpty()) {
        int i = qrand() % m_wordsList.count();
        m_current = m_wordsList[i];
    } else {
        m_current = QString::null;
    }
    m_usedCharacters = QString::null;
    m_foundWord = QString::null;
    for (int i = 0; i < m_current.count(); ++i) {
        m_foundWord += '_';
    }
}

int Game::errorCount() const
{
    return m_errors;
}

void Game::setMaxErrorCount(int max)
{
    m_maxErrors = max;
}

int Game::maxErrorCount() const
{
    return m_maxErrors;
}

bool Game::play(QChar c)
{
    bool ok = false;
    if (!m_usedCharacters.contains(c) && m_errors < m_maxErrors) {
        m_usedCharacters += c;
        for (int i = 0; i < m_current.count(); ++i) {
            if (m_current[i] == c) {
                ok = true;
                m_foundWord[i] = c;
                if (m_foundWord == m_current) {
                    emit victory();
                }
            }
        }
        if (!ok) {
            ++m_errors;
        }
        if (m_errors == m_maxErrors) {
            emit defeat();
        }
    }
    return ok;
}

void Game::setWordsList(const QStringList wl)
{
    m_wordsList.clear();
    foreach (const QString& w, wl) {
        m_wordsList.append(w.toUpper());
    }
}

QStringList Game::wordsList() const
{
    return m_wordsList;
}

QString Game::usedCharacters() const
{
    return m_usedCharacters;
}

QString Game::foundWord() const
{
    return m_foundWord;
}

bool Game::isFinished()
{
    return m_errors >= m_maxErrors || m_foundWord == m_current;
}

bool Game::hasWon()
{
    return m_foundWord == m_current;
}
