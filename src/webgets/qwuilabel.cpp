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

#include <QtWui/QwuiLabel>
#include <QtGui/QImage>
#include <QtWui/QwuiTag>
#include <QtWui/QwuiApplication>
#include <QtCore/QDateTime>

QwuiLabel::QwuiLabel(QwuiWebget* parent, const QString& webName) :
    QwuiWebget(parent, webName),
    m_imageType(PngImage),
    m_image(NULL),
    m_imageClickable(false)
{
    addStyleSheet("qwuilabel.css");
}

QwuiLabel::~QwuiLabel()
{
    delete m_image;
}

QString QwuiLabel::text() const
{
    return m_text;
}

QString QwuiLabel::imageFile() const
{
    return m_imageFile;
}

const QImage* QwuiLabel::image() const
{
    return m_image;
}

QwuiLabel::ImageType QwuiLabel::imageType() const
{
    return m_imageType;
}

void QwuiLabel::setImageType(ImageType p)
{
    m_imageType = p;
}

void QwuiLabel::clear()
{
    delete m_image;
    m_image = NULL;
    m_text = QString::null;
    m_imageFile = QString::null;
    update();
}

void QwuiLabel::setNum(int num)
{
    clear();
    m_text = QString::number(num);
    update();
}

void QwuiLabel::setNum(double num)
{
    clear();
    m_text = QString::number(num);
    update();
}

void QwuiLabel::setImageFile(const QString& f, bool clickable)
{
    clear();
    m_imageFile = f;
    m_imageClickable = clickable;
    update();
}

void QwuiLabel::setImage(const QImage& p, bool clickable)
{
    clear();
    m_image = new QImage(p);
    m_imageClickable = clickable;
    update();
}

void QwuiLabel::setText(const QString& t)
{
    clear();
    m_text = t;
    update();
}

void QwuiLabel::image(QString& mimeType)
{
    QIODevice* dev = device();
    if (dev == NULL) {
        return;
    }
    if (m_image != NULL) {
        switch (m_imageType) {
            case JpegImage:
                m_image->save(dev, "JPG");
                mimeType = "image/jpeg";
                break;
            case PngImage:
                m_image->save(dev, "PNG");
                mimeType = "image/png";
                break;
        }
    }
}

void QwuiLabel::handleClick(QString& mimeType)
{
    Q_UNUSED(mimeType);

    QString link = webApp()->parameters()["href"];
    emit clicked(link);
}

void QwuiLabel::render()
{
    if (m_image != NULL) {
        if (m_imageClickable) {
            QwuiTag aTag(this, "a");
            aTag.setAttribute("href", "javascript:qwui_label_emit('" + webPath() + "')");
            QwuiTag* imgTag = new QwuiTag(&aTag, "img");
            imgTag->setAttribute("src", QString("?call=") + webPath() + ".image&cb=" + QString::number(QDateTime::currentDateTime().toTime_t()));
            imgTag->setAttribute("width", QString::number(m_image->width()) + "px");
            imgTag->setAttribute("height", QString::number(m_image->height()) +  "px");
        } else {
            QwuiTag imgTag(this, "img");
            imgTag.setAttribute("src", QString("?call=") + webPath() + ".image&cb=" + QString::number(QDateTime::currentDateTime().toTime_t()));
            imgTag.setAttribute("width", QString::number(m_image->width()) + "px");
            imgTag.setAttribute("height", QString::number(m_image->height()) +  "px");
        }
    } else if (!m_imageFile.isEmpty()) {
        if (m_imageClickable) {
            QwuiTag aTag(this, "a");
            aTag.setAttribute("href", "javascript:qwui_label_emit('" + webPath() + "')");
            QwuiTag* imgTag = new QwuiTag(&aTag, "img");
            imgTag->setAttribute("src", m_imageFile);
        } else {
            QwuiTag imgTag(this, "img");
            imgTag.setAttribute("src", m_imageFile);
        }
    } else {
        QString t = m_text;
        t.replace(QRegExp("<[aA]\\s+[hH][rR][eE][fF]=\"([^\"]*)\"\\s*>"), "<a href=\"javascript:qwui_label_emit('" + webPath() + "','\\1')\">");
        QwuiTag tag(this, "div");
        tag.setText(t);
    }
}
