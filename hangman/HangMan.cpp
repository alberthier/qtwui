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

#include "HangMan.h"
#include <QtCore/QCoreApplication>
#include <QtWui/QwuiBoxLayout>
#include <QtWui/QwuiLabel>
#include <QtGui/QPainter>
#include "Game.h"

HangMan::HangMan(QwuiWebget* parent, const QString& webName) :
    QwuiWebget(parent, webName),
    m_title(NULL),
    m_word(NULL),
    m_image(NULL),
    m_letterBox(NULL),
    m_game(NULL),
    m_errorsImage(300, 300, QImage::Format_ARGB32)
{
    m_game = new Game(this);
    QStringList wl;
    wl << "wizard" << "computer" << "science" << "navigation" << "holidays"
        << "synonym" << "alphabet" << "lesson" << "improvisation" << "maintainer"
        << "platinum" << "compilation" << "linking" << "source" << "imagination" << "history";
    m_game->setWordsList(wl);

    QwuiBoxLayout* l = new QwuiVBoxLayout(this);

    m_title = new QwuiLabel(this, "m_title");
    m_word = new QwuiLabel(this, "m_word");
    m_image = new QwuiLabel(this, "m_image");
    m_letterBox = new QwuiLabel(this, "m_letterBox");
    connect(m_letterBox, SIGNAL(clicked(const QString&)), this, SLOT(letterClicked(const QString&)));
    connect(m_title, SIGNAL(clicked(const QString&)), this, SLOT(newGame(const QString&)));

    l->addWebget(m_title, 1);
    l->addWebget(m_word, 1);
    l->addWebget(m_image, 5);
    l->addWebget(m_letterBox, 2);

    m_title->setText("<h1>Hangman</h1><br /><h4><a href=\"new_game\">New Game</a> <a href=\"kill_server\">Kill server</a></h4>");
    m_title->setAlignment(Qt::AlignHCenter);
    m_word->setAlignment(Qt::AlignHCenter);
    m_image->setAlignment(Qt::AlignHCenter);
    m_letterBox->setAlignment(Qt::AlignHCenter);
    newGame("new_game");
}

HangMan::~HangMan()
{
}

void HangMan::updateImage(int steps)
{
    QPainter painter(&m_errorsImage);
    painter.setPen(QPen(QColor(20, 20, 20), 8));
    if (steps == 1) {
        painter.drawLine(30, 270, 180, 270);
    }
    if (steps == 2) {
        painter.drawLine(105, 270, 105, 50);
    }
    if (steps == 3) {
        painter.drawLine(30, 50, 250, 50);
    }
    if (steps == 4) {
        painter.drawLine(220, 50, 220, 80);
    }
    if (steps == 5) {
        painter.drawArc(205, 80, 30, 30, 0, 5760);
    }
    if (steps == 6) {
        painter.drawLine(220, 110, 220, 200);
    }
    if (steps == 7) {
        painter.drawLine(220, 130, 175, 150);
    }
    if (steps == 8) {
        painter.drawLine(220, 130, 265, 150);
    }
    if (steps == 9) {
        painter.drawLine(220, 200, 165, 245);
    }
    if (steps == 10) {
        painter.drawLine(220, 200, 275, 245);
    }
}

void HangMan::updateCharacters(const QString& usedCharacters)
{
    QString charLinks("<h1>");
    for (char c = 'A'; c <= 'Z'; ++c) {
        if (!usedCharacters.contains(c)) {
            charLinks += QString("<a href=\"letter_") + QChar(c) + QString("\">") + QChar(c) + QString("</a> ");
        } else {
            charLinks += QChar(c) + QString(" ");
        }
    }
    charLinks += "</h1>";
    m_letterBox->setText(charLinks);
}

void HangMan::letterClicked(const QString& link)
{
    if (!link.isEmpty()) {
        m_game->play(link[link.length() - 1]);
        if (m_game->isFinished()) {
            if (m_game->hasWon()) {
                m_letterBox->setText("<h1>Victory !</h1>");
            } else {
                m_letterBox->setText("<h1>Defeat !</h1>");
            }
        } else {
            updateCharacters(m_game->usedCharacters());
        }
        updateImage(m_game->errorCount());
        m_image->setImage(m_errorsImage);
        QString foundWord(m_game->foundWord());
        QString displayedWord;
        for (int i = 0; i < foundWord.length(); ++i) {
            displayedWord += foundWord[i] + " ";
        }
        m_word->setText(QString("<h2>%1</h2>").arg(displayedWord));
    }
}

void HangMan::newGame(const QString& link)
{
    if (link == "new_game") {
        m_game->newGame();
        updateCharacters();
        m_errorsImage.fill(0x00ffffff);
        m_image->setImage(m_errorsImage);
        QString foundWord(m_game->foundWord());
        QString displayedWord;
        for (int i = 0; i < foundWord.length(); ++i) {
            displayedWord += foundWord[i] + " ";
        }
        m_word->setText(QString("<h2>%1</h2>").arg(displayedWord));
    } else if (link == "kill_server") {
        QCoreApplication::instance()->quit();
    }
}
