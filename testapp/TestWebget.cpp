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

#include "TestWebget.h"
#include <QtCore/QTextStream>
#include <QtCore/QIODevice>
#include <QtGui/QImage>
#include <QtWui/QwuiApplication>
#include <QtWui/QwuiHBoxLayout>
#include <QtWui/QwuiVBoxLayout>
#include <QtWui/QwuiGridLayout>
#include <QtWui/QwuiStackedLayout>
#include <QtWui/QwuiLabel>
#include <QtWui/QwuiStackedWebget>
#include <QtWui/QwuiScrollArea>

TestWebget::TestWebget(QwuiWebget* parent, const QString& webName) :
    QwuiWebget(parent, webName),
    m_items(0),
    m_nb(0)
{
    qDebug("YYYYYYYYEEEEEEEEEHHHHHHHHHHHHHHAAAAAAAAAAAAHHHHH !!!!");

    //QwuiLabel* l1 = new QwuiLabel(this, "l1");
    //l1->setText("Label 1");
    QwuiLabel* l2 = new QwuiLabel(this, "l2");
    l2->setText("- Label 2 -");
    l2->setTextColor(QColor(0, 0, 200));
    l2->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    l2->setBorderStyle(Qt::DashedStyle);
    l2->setBorderColor(QColor(0, 200, 50));
    l2->setBorderWidth(10);
    QwuiLabel* l21 = new QwuiLabel(this, "l2");
    l21->setText("yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo yoyo Label 21  yoyo ");
    QwuiLabel* l3 = new QwuiLabel(this, "l3");
    l3->setText("Label 3");
    l3->setBackgroundColor(QColor(200, 0, 10));
    l3->setBorderStyle(Qt::DashedStyle);
    l3->setBorderColor(QColor(0, 200, 50));
    l3->setBorderWidth(10);
    l3->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    QwuiLabel* l31 = new QwuiLabel(this, "l31");
    l31->setText("Label 31 <a href=\"mylink\">Click Me</a> toto");
    l31->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    QwuiLabel* l4 = new QwuiLabel(this, "l4");
    QImage img(100, 100, QImage::Format_RGB32);
    img.fill(qRgb(189, 149, 39));
    l4->setImage(img);
    QwuiLabel* l5 = new QwuiLabel(this, "l5");
    l5->setImageFile("bin/coin.jpg");
    QwuiLabel* link = new QwuiLabel(this, "link");

    link->setText("<a href=\"link\">Test</a> and <a href=\"swap\">swap it !!</a>");
    m_stack = new QwuiStackedWebget(this, "stack");
    QwuiScrollArea* scrollArea = new QwuiScrollArea(this, "scroll");
    scrollArea->setWebget(l21);
    m_stack->addWebget(scrollArea);
    m_stack->addWebget(l2);

    QwuiGridLayout* l = new QwuiGridLayout(this);
    QwuiHBoxLayout* hbox = new QwuiHBoxLayout();
    //l->insertWebget(l1, 0, 0);
    //l->insertWebget(l2, 0, 1);
    l->insertItem(hbox, 1, 0);
    l->insertWebget(l4, 1, 1);
    l->insertWebget(l5, 2, 0);
    //l->insertWebget(link, 2, 1);

    l->insertWebget(link, 0, 0, 1, 2);
    l->insertWebget(m_stack, 2, 1);

    hbox->addWebget(l3, 1);
    hbox->addWebget(l31, 9);

    connect(l31, SIGNAL(clicked(const QString&)), this, SLOT(linkClicked()));
    connect(link, SIGNAL(clicked(const QString&)), this, SLOT(link2Clicked(const QString&)));
    m_label1 = l31;
    m_label2 = l3;

#if 0
    QwuiLink* link = new QwuiLink(this, "link", "Test", this, Qt::AjaxInsertionReplace);
    connect(link, SIGNAL(clicked(QString&, const QwuiParameters&, QIODevice*)), this, SLOT(linkClicked(QString&, const QwuiParameters&, QIODevice*)));
    if (webName == "test1") {
        /*QwuiHBoxLayout* hbox = new QwuiHBoxLayout(this);
        hbox->addWebget(new TestWebget(this, "test2"), 1);
        QwuiVBoxLayout* vbox = new QwuiVBoxLayout(QwuiLayout::Em);
        hbox->addLayout(vbox, 2);
        vbox->addWebget(new TestWebget(this, "test3"), 30);
        vbox->addWebget(new TestWebget(this, "test4"));*/

        l->insertWebget(new TestWebget(this, "test2"), 0, 0, 1, 2);
        //l->insertWebget(new TestWebget(this, "test3"), 0, 1);
        l->insertWebget(new TestWebget(this, "test4"), 1, 0);
        l->insertWebget(new TestWebget(this, "test5"), 1, 1);
    }
#endif //0
}

TestWebget::~TestWebget()
{
    qDebug("AAAAAAAAAAAAAAAAAAAARRRRRGGGGGGGGGGGG !!!!");
}

void TestWebget::coucou(QString& mimeType)
{
    mimeType = "text/plain";
    QString s("Hello World from %1 method !");
    s = s.arg(webPath());
    device()->write(s.toAscii(), s.length());
}

void TestWebget::empty(QString& mimeType)
{
    mimeType = "text/html";
}

void TestWebget::ajaxcall(QString& mimeType)
{
    mimeType = "text/html";
    qDebug("AJAX Call !!!");
    QString s1("<ul class=\"testajax\">");
    QString s2("<li>Item %1</li>");
    QString s3("</ul>");

    device()->write(s2.arg(++m_items).toAscii(), s2.length());
    //dev->write(s1.toAscii(), s1.length());
    /*++m_items;
    for (int i = 0; i < m_items; ++i) {
        dev->write(s2.toAscii(), s2.length());
    }*/
    //dev->write(s3.toAscii(), s3.length());
}

void TestWebget::linkClicked()
{
    m_label1->setText(QString("%1 call #%2").arg(webApp()->sessionId()).arg(m_nb));
    m_label2->setText(QString("Haha %1 call #%2").arg(webApp()->sessionId()).arg(m_nb));
    ++m_nb;
    /*
    QwuiParameters parameters = webApp()->parameters();
    mimeType = "text/plain";
    QTextStream stream(device());
    stream << "coucou " << m_items << " " << webApp()->sessionId() << " " << parameters["toto"] << " " << parameters["toto2"] << "<br />";
    m_items = m_items + 1;
    */
}

void TestWebget::link2Clicked(const QString& link)
{
    qDebug(link.toAscii());
    if (link == "link") {
        m_label1->setText("Yeeeeehhhaaaahh !!!!");
    } else if (link == "swap") {
        int i = m_stack->currentIndex();
        i = (i == 1) ? 0 : 1;
        m_stack->setCurrentIndex(i);
    }
}
