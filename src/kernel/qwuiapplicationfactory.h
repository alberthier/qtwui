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

#ifndef QWUIAPPLICATIONFACTORY_H
#define QWUIAPPLICATIONFACTORY_H

#include <QtWui/QwuiAbstractResourceProviderFactory>
#include <QtCore/QStringList>
#include <QtWui/QwuiApplicationCreator>
#include <QtWui/QwuiGlobal>

/**
 * \brief Application factory.
 * This class uses a creator function to create new applications instances.
 * The creator function corresponds to the traditionnal main() function for a web application.
 * @code
//
// the traditionnal main function only starts the application server.
//
int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    QwuiApplicationServer webAppServer(webMain);
    webAppServer.setBuiltInServerPort(8888);
    webAppServer.exec();
    return app.exec();
}

//
// This is the main function executed by the application server for each new session.
//
QwuiApplication* webMain(const QString& sessionId, const QStringList& args)
{
    Q_UNUSED(args);

    QwuiApplication* webApp = new QwuiApplication(sessionId);
    QwuiMainWebget* mw = new QwuiMainWebget(NULL, "mw");
    mw->setTitle("QtWui Test");
    QwuiLabel* helloWorld = new QwuiLabel(mw, "helloWorld");
    webApp->setMainWebget(helloWorld);
    helloWorld->setText("Hello World !");
    return webApp;
}
 * @endcode
 */
class QTWUI_EXPORT QwuiApplicationFactory : public QwuiAbstractResourceProviderFactory
{
public:
    /**
     * @param creatorFunction creator function corresponding to the main() function for a web application.
     * @param args command line arguments.
     */
    QwuiApplicationFactory(QwuiApplicationCreator creatorFunction, const QStringList& args);
    virtual ~QwuiApplicationFactory();

    /**
     * @param sessionId Session identifier to use for the new application.
     * @return a new QwuiApplication instance.
     */
    virtual QwuiAbstractResourceProvider* create(const QString& sessionId) const;

private:
    QwuiApplicationCreator m_creatorFunction;
    QStringList m_args;
};

#endif // QWUIAPPLICATIONFACTORY_H
