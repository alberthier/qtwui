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

#include <QtCore/QCoreApplication>
#include <QtCore/QTextStream>
#include <QtWui/QwuiApplication>
#include <QtWui/QwuiMainWebget>
#include <QtWui/QwuiApplicationServer>
#include <QtWui/QwuiAbstractHttpServer>
#include "HangMan.h"

void printUsage()
{
    QTextStream out(stdout);
    out << "Usage : hangman [options]\n";
    out << "Options :\n";
    out << "          -p --port : listening port\n";
}

QwuiApplication* webMain(const QString& sessionId, const QStringList& args)
{
    Q_UNUSED(args);

    QwuiApplication* webApp = new QwuiApplication(sessionId);
    webApp->setJavascriptDir("javascript");
    webApp->setStyleSheetsDir("stylesheets");
    QwuiMainWebget* mw = new QwuiMainWebget(NULL, "mw");
    mw->setTitle("QtWui Test");
    new HangMan(mw, "hangman");
    webApp->setMainWebget(mw);

    return webApp;
}

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    QwuiApplicationServer webAppServer(webMain);
    webAppServer.httpServer()->setRequestProcessingType(QwuiAbstractHttpServer::QueuedProcessing);

    QString option = QCoreApplication::arguments().at(1);
    if ((option == "-p") || (option == "--port")) {
        bool ok;
        quint16 port = QString(argv[2]).toInt(&ok);
        if (ok) {
            webAppServer.setBuiltInServerPort(port);
        } else {
            printUsage();
            return -1;
        }
    } else {
        printUsage();
        return -1;
    }
    webAppServer.exec();
    return app.exec();
}
