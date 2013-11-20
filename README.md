# QtWui: Web User Interface for Qt

## What is QtWui

QtWui is a module for Qt that enables you to write web applications just like you where writing a standard desktop GUI application with QtGui. It comes with a simple web server that runs the application. In the future it will also be possible to use an external web server that supports FastCGI.

## General principle

The idea behind QtWui is that each connected user opens a new session on the server and this session is like a standard application process on a desktop computer. Each sessin has a lifetime that can be configured. If no user action occurs before the end of the session lifetime, it is destroyed.

## Internal machinery

![Schema](https://raw.github.com/alberthier/qtwui/master/schema-qtwui.png)

The web server works with an application server (QwuiApplicationServer) that is in charge of creating applications instances for each new client (web browser).

When a client (web browser) connects to the server, a new application instance is created and a session ID is affected to it. All further communication between the client and the server use this session ID, refering always the same application instance within the server.

Each application instance is independant of the others. Modifying the widgets won't affect the other application instances.

You can chose between two different ways of handling client requests:

Queued: client requests are put in a FIFO and threated sequentially
Threaded: client requests are threated simultaneously within a thread. A thread is created, the application instance corresponding to the client session ID is moved to this thread and than all the computation and communication takes place in this thread. Once finished. the application goes back to the application server pool and the thread is destroyed.
If the application cannot provide any html code for the given URL, the request is forwarded to a file resource provider who will check if a file on the disk corresponds to the request and than will transmit it.

QtWui makes use of the AJAX technology to communicate between the client and the server. All the client AJAX machinery is provided by Prototype Javascript Framework (http://www.prototypejs.org/).

## Web widgets

QtWui doesn't provide many web widgets (webgets) for the moment:

* A base widget (QwuiWebget) that can be used to compose complex UIs.
* A main window (QwuiMainWindow) that is used as the main container for the web application. It also initialises the CSS and javascript used by contained web widgets.
* A label (QwuiLabel) that is similar to QLabel.
* A scroll area (QwuiScrollArea)
* A stacked webget (QwuiStackedWebget)
* A set of layouts to organise your webgets (QwuiHBoxLayout, QwuiVBoxLayout, QwuiStackedLayout and QwuiGridLayout). They are similar to their friends in QtGui.

## Example

Here is the traditionnal "Hello World" example:

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

## Installing

QtWui can be built like a standard Qt program: with qmake and make. The sources come with a simple demo: a hangman game. It is built with the QtWui sources. Go to the folder where you uncompressed the source archive and follow the these steps:

### On unices:

    qmake
    make
    ./run_hangman.sh

### On windows with the msvc compiler

    qmake
    nmake
    run_hangman.bat

The run_hangman script starts the server on the port 8888. edit the script to change the port. Then start a web browser and go to the http://localhost:8888 page to try the game.

## Future

There are many feature missing in QtWui to make it a usable web application framework. The main missing things are:

* Add form widgets (buttons, checkboxes, line edits, etc...)
* Add missing webgets like progress bars, splitters, menus, dock widgets, etc...
* Add support for external web servers (Apache, Lighttpd, IIS, etc...)
* And much more !

## Contact

Main developer: Eric ALBER (eric DOT alber AT gmail DOT com)

Help is welcome!
