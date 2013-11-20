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

#ifndef QWUILABEL_H
#define QWUILABEL_H

#include <QtWui/QwuiWebget>
#include <QtWui/QwuiGlobal>

class QImage;

/**
 * @brief A label webget.
 * A label can be used to display text, an image and links.
 * if you put
 * @code
 * <a href="test">Test</a>
 * @endcode
 * as text, the signal clicked() will be emited with "test" as parameter.
 */
class QTWUI_EXPORT QwuiLabel : public QwuiWebget
{
    Q_OBJECT

public:
    enum ImageType {
        JpegImage,
        PngImage
    };

public:
    QwuiLabel(QwuiWebget* parent = NULL, const QString& webName = QString::null);
    virtual ~QwuiLabel();

    QString text() const;
    QString imageFile() const;
    const QImage* image() const;
    ImageType imageType() const;
    void setImageType(ImageType p);

public slots:
    void clear();
    void setNum(int num);
    void setNum(double num);
    void setImageFile(const QString& f, bool clickable = false);
    void setImage(const QImage& p, bool clickable = false);
    void setText(const QString& t);

protected:
    virtual void render();

private slots:
    void image(QString& mimeType);
    void handleClick(QString& mimeType);

signals:
    void clicked(const QString& link);

private:
    QString m_text;
    QString m_imageFile;
    ImageType m_imageType;
    QImage* m_image;
    bool m_imageClickable;
};

#endif // QWUILABEL_H
