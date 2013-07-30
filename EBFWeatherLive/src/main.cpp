/**
 * @file main.cpp
 * @author Xiaodong Zhang
 * @version 1.0
 *
 * This file contains the main() entry method for the whole application.
 *
 */

#include <bb/cascades/Application>
#include <QLocale>
#include <QTranslator>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <Qt/qdeclarativedebug.h>
#include <QtDeclarative/QtDeclarative>
#include "WeatherDataMgr.hpp"

using namespace bb::cascades;
using namespace ebf;

/**Entry method of the whole application*/
Q_DECL_EXPORT int main(int argc, char **argv)
{
	//create the application
    Application app(argc, argv);

    //Create scene document from main.qml asset, the parent is set
    //to ensure the document gets destroyed properly at shut down.
    QmlDocument *mainQml = QmlDocument::create("asset:///main.qml").parent(&app);

    //Create root object for the UI
    AbstractPane *root = mainQml->createRootObject<AbstractPane>();

    //Set created root object as the application scene
    app.setScene(root);

    WeatherDataMgr weatherDataMgr(&app, root);
    //Expose weatherDataMgr object to qml page, so that this qml page can access the  weatherDataMgr object
    mainQml->setContextProperty("weatherDataMgr", &weatherDataMgr);

    // Enter the application main event loop.
    return Application::exec();
}
