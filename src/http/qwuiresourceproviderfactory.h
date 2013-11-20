R/***************************************************************************
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

#ifndef QWUIRESSOURCEPROVIDERFACTORY_H
#define QWUIRESSOURCEPROVIDERFACTORY_H

#include <QtWui/QwuiAbstractResourceProviderFactory>
#include <QtWui/QwuiGlobal>

/**
 * \brief A helper class used to instanciate factories for resource providers.
 * Example:
 * \code
 * QwuiResourceProviderFactory<MyspecificProvider> factory;
 * QwuiAbstractResourceProvider* provider = factory.create("sessionId");
 * \endcode
 */
template <typename T>
class QTWUI_EXPORT QwuiResourceProviderFactory : public QwuiAbstractResourceProviderFactory
{
public:
    QwuiResourceProviderFactory();
    virtual ~QwuiResourceProviderFactory();

    virtual QwuiAbstractResourceProvider* create(const QString& sessionId) const;
};

template <typename T>
QwuiResourceProviderFactory<T>::QwuiResourceProviderFactory() :
    QwuiAbstractResourceProviderFactory()
{
}

template <typename T>
QwuiResourceProviderFactory<T>::~QwuiResourceProviderFactory()
{
}

template <typename T>
QwuiAbstractResourceProvider* QwuiResourceProviderFactory<T>::create(const QString& sessionId) const
{
    return new T(sessionId);
}

#endif // QWUIRESSOURCEPROVIDERFACTORY_H
